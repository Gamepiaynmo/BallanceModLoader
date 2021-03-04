#include "BMLMod.h"
#include "ScriptHelper.h"
#include "RegisterBB.h"
#include "ExecuteBB.h"
#include "Gui.h"
#include <map>
#include "minhook/MinHook.h"
#include "ModLoader.h"
#include <ctime>
#include "Commands.h"
#include "Config.h"
#include "Util.h"
#include <locale>
#include <codecvt>

using namespace ScriptHelper;

void BMLMod::OnLoadObject(CKSTRING filename, BOOL isMap, CKSTRING masterName, CK_CLASSID filterClass,
	BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
	XObjectArray* objArray, CKObject* masterObj) {
	if (!strcmp(filename, "3D Entities\\Menu.nmo")) {
		BGui::Gui::InitMaterials();

		GetLogger()->Info("Create Command Gui");
		m_cmdBar = new BGui::Gui();
		m_cmdBar->AddPanel("M_Cmd_Bg", VxColor(0, 0, 0, 110), 0.02f, 0.94f, 0.95f, 0.025f)->SetZOrder(100);
		m_cmdInput = m_cmdBar->AddTextInput("M_Cmd_Text", ExecuteBB::GAMEFONT_03, 0.02f, 0.94f, 0.95f, 0.025f, [this](CKDWORD key) { OnCmdEdit(key); });
		m_cmdInput->SetAlignment(ALIGN_LEFT);
		m_cmdInput->SetTextFlags(TEXT_SCREEN | TEXT_SHOWCARET);
		m_cmdInput->SetZOrder(110);
		m_cmdBar->SetCanBeBlocked(false);
		m_cmdBar->SetVisible(false);

		GetLogger()->Info("Create Console Gui");
		m_msgLog = new BGui::Gui();
		for (int i = 0; i < MSG_MAXSIZE; i++) {
			m_msg[i].m_bg = m_msgLog->AddPanel((std::string("M_Cmd_Log_Bg_") + std::to_string(i + 1)).c_str(),
				VxColor(0, 0, 0, 110), 0.02f, 0.9f - i * 0.025f, 0.95f, 0.025f);
			m_msg[i].m_bg->SetVisible(false);
			m_msg[i].m_bg->SetZOrder(100);
			m_msg[i].m_text = m_msgLog->AddTextLabel((std::string("M_Cmd_Log_Text_") + std::to_string(i + 1)).c_str(),
				"", ExecuteBB::GAMEFONT_03, 0.02f, 0.9f - i * 0.025f, 0.95f, 0.025f);
			m_msg[i].m_text->SetVisible(false);
			m_msg[i].m_text->SetAlignment(ALIGN_LEFT);
			m_msg[i].m_text->SetZOrder(110);
			m_msg[i].timer = 0;
		}

		GetLogger()->Info("Create BML Gui");
		m_ingameBanner = new BGui::Gui();
		m_ingameBanner->AddTextLabel("M_Use_BML", "Ballance Mod Loader " BML_VERSION, ExecuteBB::GAMEFONT_01, 0, 0, 1, 0.03f);
		m_cheat = m_ingameBanner->AddTextLabel("M_Use_Cheat", "Cheat Mode Enabled", ExecuteBB::GAMEFONT_01, 0, 0.85f, 1, 0.05f);
		//m_cheat[1] = m_ingameBanner->AddTextLabel("M_Use_Cheat", "Cheat Mode Enabled", ExecuteBB::GAMEFONT_03A, 0.001f, 0.901f, 1, 0.03f);
		//m_cheat[2] = m_ingameBanner->AddTextLabel("M_Use_Cheat", "Cheat Mode Enabled", ExecuteBB::GAMEFONT_03A, 0.002f, 0.902f, 1, 0.03f);
		m_fps = m_ingameBanner->AddTextLabel("M_Show_Fps", "", ExecuteBB::GAMEFONT_01, 0, 0, 0.2f, 0.03f);
		m_srTitle = m_ingameBanner->AddTextLabel("M_Time_Counter_Title", "SR Timer", ExecuteBB::GAMEFONT_01, 0.03f, 0.8f, 0.2f, 0.03f);
		m_srScore = m_ingameBanner->AddTextLabel("M_Time_Counter", "", ExecuteBB::GAMEFONT_01, 0.05f, 0.83f, 0.2f, 0.03f);
		m_fps->SetAlignment(ALIGN_LEFT);
		m_fps->SetVisible(m_showFPS->GetBoolean());
		m_srTitle->SetAlignment(ALIGN_LEFT);
		m_srTitle->SetVisible(false);
		m_srScore->SetAlignment(ALIGN_LEFT);
		m_srScore->SetVisible(false);
		m_cheat->SetVisible(false);
		m_customMaps = m_ingameBanner->AddRightButton("M_Enter_Custom_Maps", 0.4f, 0.6238f, [this]() {
			m_exitStart->ActivateInput(0);
			m_exitStart->Activate();
			ShowGui(m_mapsGui);
			});

		GetLogger()->Info("Create Mod Options Gui");
		m_modOption = new GuiModOption();
		m_modOption->SetVisible(false);

		m_mapsGui = new GuiCustomMap(this);
		m_level01 = m_bml->Get2dEntityByName("M_Start_But_01");
		CKBehavior* menuMain = m_bml->GetScriptByName("Menu_Start");
		m_exitStart = FindFirstBB(menuMain, "Exit");

		m_smHook = new ScreenModeHook();
	}

	if (!strcmp(filename, "3D Entities\\MenuLevel.nmo")) {
		if (m_unlockRes->GetBoolean()) {
			GetLogger()->Info("Adjust MenuLevel Camera");
			CKCamera* cam = m_bml->GetTargetCameraByName("Cam_MenuLevel");
			CKRenderContext* rc = m_bml->GetRenderContext();
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			m_bml->SetIC(cam);
		}
	}

	if (!strcmp(filename, "3D Entities\\Camera.nmo")) {
		if (m_unlockRes->GetBoolean()) {
			GetLogger()->Info("Adjust Ingame Camera");
			CKCamera* cam = m_bml->GetTargetCameraByName("InGameCam");
			CKRenderContext* rc = m_bml->GetRenderContext();
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			m_bml->SetIC(cam);
		}

		m_camPos = m_bml->Get3dEntityByName("Cam_Pos");
		m_camOrient = m_bml->Get3dEntityByName("Cam_Orient");
		m_camOrientRef = m_bml->Get3dEntityByName("Cam_OrientRef");
		m_camTarget = m_bml->Get3dEntityByName("Cam_Target");
	}
}

void BMLMod::OnLoadScript(CKSTRING filename, CKBehavior* script) {
	if (!strcmp(script->GetName(), "Default Level"))
		OnEditScript_Base_DefaultLevel(script);

	if (!strcmp(script->GetName(), "Event_handler"))
		OnEditScript_Base_EventHandler(script);

	if (!strcmp(script->GetName(), "Menu_Init"))
		OnEditScript_Menu_MenuInit(script);

	if (!strcmp(script->GetName(), "Menu_Options"))
		OnEditScript_Menu_OptionsMenu(script);

	if (!strcmp(script->GetName(), "Gameplay_Ingame"))
		OnEditScript_Gameplay_Ingame(script);

	if (!strcmp(script->GetName(), "Gameplay_Energy"))
		OnEditScript_Gameplay_Energy(script);

	if (!strcmp(script->GetName(), "Gameplay_Events"))
		OnEditScript_Gameplay_Events(script);

	if (!strcmp(script->GetName(), "Levelinit_build"))
		OnEditScript_Levelinit_build(script);

	if (m_fixLifeBall) {
		if (!strcmp(script->GetName(), "P_Extra_Life_Particle_Blob Script")
			|| !strcmp(script->GetName(), "P_Extra_Life_Particle_Fizz Script"))
			OnEditScript_ExtraLife_Fix(script);
	}
}

void BMLMod::OnEditScript_Base_DefaultLevel(CKBehavior* script) {
	if (m_unlockRes->GetBoolean()) {
		GetLogger()->Info("Unlock higher resolutions");
		CKBehavior* sm = FindFirstBB(script, "Screen Modes");

		CKBehavior* rrs[4];
		FindBB(sm, [sm, &rrs](CKBehavior* rr) {
			int v = GetParamValue<int>(rr->GetInputParameter(2)->GetDirectSource());
			switch (v) {
			case 1: rrs[0] = rr; break;
			case 640: rrs[1] = rr; break;
			case 1600: rrs[2] = rr; break;
			case 16: rrs[3] = rr; break;
			}
			return true;
			}, "Remove Row If");

		CKBehavior* it = FindPreviousBB(sm, rrs[0], "Iterator");
		CKBehavior* gc = FindNextBB(sm, rrs[3], "Get Cell");
		DeleteBB(sm, rrs[0]);
		DeleteBB(sm, rrs[3]);
		CreateLink(sm, it, gc, 0, 0);
	}

	if (m_skipAnim->GetBoolean()) {
		GetLogger()->Info("Skip Loading Animation");
		CKBehavior* is = FindFirstBB(script, "Intro Start"),
			* ie = FindFirstBB(script, "Intro Ende");

		CKBehavior* ml = FindFirstBB(script, "Main Loading"),
			* ps = FindFirstBB(script, "Preload Sound");

		FindPreviousLink(script, is)->SetOutBehaviorIO(ml->GetInput(0));
		FindNextLink(script, ps)->SetOutBehaviorIO(FindNextLink(script, ie)->GetOutBehaviorIO());
	}
}

void BMLMod::OnEditScript_Base_EventHandler(CKBehavior* script) {
	CKBehavior* som = FindFirstBB(script, "Switch On Message", false, 2, 11, 11, 0);

	GetLogger()->Info("Insert message Start Menu Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 0, 0)), CreateBB(script, BML_ONPRESTARTMENU_GUID));
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 0, 0)), CreateBB(script, BML_ONPOSTSTARTMENU_GUID));

	GetLogger()->Info("Insert message Exit Game Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 1, 0)), CreateBB(script, BML_ONEXITGAME_GUID));

	GetLogger()->Info("Insert message Load Level Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 2, 0)), CreateBB(script, BML_ONPRELOADLEVEL_GUID));
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 2, 0)), CreateBB(script, BML_ONPOSTLOADLEVEL_GUID));

	GetLogger()->Info("Insert message Start Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 3, 0)), CreateBB(script, BML_ONSTARTLEVEL_GUID));

	GetLogger()->Info("Insert message Reset Level Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 4, 0)), CreateBB(script, BML_ONPRERESETLEVEL_GUID));
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 4, 0)), CreateBB(script, BML_ONPOSTRESETLEVEL_GUID));

	GetLogger()->Info("Insert message Pause Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 5, 0)), CreateBB(script, BML_ONPAUSELEVEL_GUID));

	GetLogger()->Info("Insert message Unpause Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 6, 0)), CreateBB(script, BML_ONUNPAUSELEVEL_GUID));

	CKBehavior* bs = FindNextBB(script, FindFirstBB(script, "DeleteCollisionSurfaces"));

	GetLogger()->Info("Insert message Exit Level Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 7, 0)), CreateBB(script, BML_ONPREEXITLEVEL_GUID));
	InsertBB(script, FindNextLink(script, FindNextBB(script, bs, nullptr, 0, 0)), CreateBB(script, BML_ONPOSTEXITLEVEL_GUID));

	GetLogger()->Info("Insert message Next Level Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 8, 0)), CreateBB(script, BML_ONPRENEXTLEVEL_GUID));
	InsertBB(script, FindNextLink(script, FindNextBB(script, bs, nullptr, 1, 0)), CreateBB(script, BML_ONPOSTNEXTLEVEL_GUID));

	GetLogger()->Info("Insert message Dead Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 9, 0)), CreateBB(script, BML_ONDEAD_GUID));

	CKBehavior* hs = FindFirstBB(script, "Highscore");
	hs->AddOutput("Out");
	FindBB(hs, [hs](CKBehavior* beh) {
		CreateLink(hs, beh, hs->GetOutput(0));
		return true;
		}, "Activate Script");
	GetLogger()->Info("Insert message End Level Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 10, 0)), CreateBB(script, BML_ONPREENDLEVEL_GUID));
	CreateLink(script, hs, CreateBB(script, BML_ONPOSTENDLEVEL_GUID));
}

void BMLMod::OnEditScript_Menu_MenuInit(CKBehavior* script) {
	m_bml->AddTimer(1u, [this]() {
		GetLogger()->Info("Acquire Game Fonts");
		CKBehavior* script = m_bml->GetScriptByName("Menu_Init");
		CKBehavior* fonts = FindFirstBB(script, "Fonts");
		CKBehavior* bbs[7] = { 0 };
		int cnt = 0;
		FindBB(fonts, [&bbs, &cnt](CKBehavior* beh) {
			bbs[cnt++] = beh;
			return true;
			}, "TT CreateFontEx");

		std::map<std::string, ExecuteBB::FontType> fontid;
		fontid["GameFont_01"] = ExecuteBB::GAMEFONT_01;
		fontid["GameFont_02"] = ExecuteBB::GAMEFONT_02;
		fontid["GameFont_03"] = ExecuteBB::GAMEFONT_03;
		fontid["GameFont_03a"] = ExecuteBB::GAMEFONT_03A;
		fontid["GameFont_04"] = ExecuteBB::GAMEFONT_04;
		fontid["GameFont_Credits_Small"] = ExecuteBB::GAMEFONT_CREDITS_SMALL;
		fontid["GameFont_Credits_Big"] = ExecuteBB::GAMEFONT_CREDITS_BIG;

		for (int i = 0; i < 7; i++) {
			int font;
			bbs[i]->GetOutputParameterValue(0, &font);
			ExecuteBB::InitFont(fontid[static_cast<CKSTRING>(bbs[i]->GetInputParameterReadDataPtr(0))], font);
		}
		});
}

void BMLMod::OnEditScript_Menu_OptionsMenu(CKBehavior* script) {
	GetLogger()->Info("Start to insert Mods Button into Options Menu");

	char but_name[] = "M_Options_But_X";
	CK2dEntity* buttons[6] = { 0 };
	CKContext* context = m_bml->GetCKContext();
	buttons[0] = m_bml->Get2dEntityByName("M_Options_Title");
	for (int i = 1; i < 4; i++) {
		but_name[14] = '0' + i;
		buttons[i] = m_bml->Get2dEntityByName(but_name);
	}

	buttons[5] = m_bml->Get2dEntityByName("M_Options_But_Back");
	buttons[4] = static_cast<CK2dEntity*>(context->CopyObject(buttons[1]));
	buttons[4]->SetName("M_Options_But_4");
	for (int i = 0; i < 5; i++) {
		Vx2DVector pos;
		buttons[i]->GetPosition(pos, true);
		pos.y = 0.1f + 0.14f * i;
		buttons[i]->SetPosition(pos, true);
	}

	CKDataArray* array = m_bml->GetArrayByName("Menu_Options_ShowHide");
	array->InsertRow(3);
	array->SetElementObject(3, 0, buttons[4]);
	BOOL show = 1;
	array->SetElementValue(3, 1, &show, sizeof(show));
	m_bml->SetIC(array);

	CKBehavior* graph = FindFirstBB(script, "Options Menu");
	CKBehavior* up_sop = nullptr, * down_sop = nullptr, * up_ps = nullptr, * down_ps = nullptr;
	FindBB(graph, [graph, &up_sop, &down_sop](CKBehavior* beh) {
		CKBehavior* previous = FindPreviousBB(graph, beh);
		CKSTRING name = previous->GetName();
		if (!strcmp(previous->GetName(), "Set 2D Material"))
			up_sop = beh;
		if (!strcmp(previous->GetName(), "Send Message"))
			down_sop = beh;
		return !(up_sop && down_sop);
		}, "Switch On Parameter");
	FindBB(graph, [graph, &up_ps, &down_ps](CKBehavior* beh) {
		CKBehavior* previous = FindNextBB(graph, beh);
		CKSTRING name = previous->GetName();
		if (!strcmp(previous->GetName(), "Keyboard"))
			up_ps = beh;
		if (!strcmp(previous->GetName(), "Send Message"))
			down_ps = beh;
		return !(up_ps && down_ps);
		}, "Parameter Selector");

	CKParameterLocal* pin = CreateParamValue(graph, "Pin 5", CKPGUID_INT, 4);
	up_sop->CreateInputParameter("Pin 5", CKPGUID_INT)->SetDirectSource(pin); up_sop->AddOutput("Out 5");
	down_sop->CreateInputParameter("Pin 5", CKPGUID_INT)->SetDirectSource(pin); down_sop->AddOutput("Out 5");
	up_ps->CreateInputParameter("pIn 4", CKPGUID_INT)->SetDirectSource(pin); up_ps->AddInput("In 4");
	down_ps->CreateInputParameter("pIn 4", CKPGUID_INT)->SetDirectSource(pin); down_ps->AddInput("In 4");

	CKBehavior* text2d = CreateBB(graph, VT_TEXT2D, true);
	CKBehavior* pushbutton = CreateBB(graph, TT_PUSHBUTTON2, true);
	CKBehavior* text2dref = FindFirstBB(graph, "2D Text");
	CKBehavior* nop = FindFirstBB(graph, "Nop");
	CKParameterLocal* entity2d = CreateParamObject(graph, "Button", CKPGUID_2DENTITY, buttons[4]);
	CKParameterLocal* buttonname = CreateParamString(graph, "Text", "Mods");
	int textflags;
	text2dref->GetLocalParameterValue(0, &textflags);
	text2d->SetLocalParameterValue(0, &textflags, sizeof(textflags));

	text2d->GetTargetParameter()->SetDirectSource(entity2d);
	pushbutton->GetTargetParameter()->SetDirectSource(entity2d);
	text2d->GetInputParameter(0)->ShareSourceWith(text2dref->GetInputParameter(0));
	text2d->GetInputParameter(1)->SetDirectSource(buttonname);
	for (int i = 2; i < 6; i++)
		text2d->GetInputParameter(i)->ShareSourceWith(text2dref->GetInputParameter(i));

	FindNextLink(graph, up_sop, nullptr, 4, 0)->SetInBehaviorIO(up_sop->GetOutput(5));
	CreateLink(graph, up_sop, text2d, 4, 0);
	CreateLink(graph, text2d, nop, 0, 0);
	CreateLink(graph, text2d, pushbutton, 0, 0);
	FindPreviousLink(graph, up_ps, nullptr, 1, 3)->SetOutBehaviorIO(up_ps->GetInput(4));
	FindPreviousLink(graph, down_ps, nullptr, 2, 3)->SetOutBehaviorIO(down_ps->GetInput(4));
	CreateLink(graph, pushbutton, up_ps, 1, 3);
	CreateLink(graph, pushbutton, down_ps, 2, 3);
	graph->AddOutput("Button 5 Pressed");
	CreateLink(graph, down_sop, graph->GetOutput(4), 5);
	FindNextLink(script, graph, nullptr, 3, 0)->SetInBehaviorIO(graph->GetOutput(4));

	CKBehavior* modsmenu = CreateBB(script, BML_MODSMENU_GUID);
	CKBehavior* exit = FindFirstBB(script, "Exit", false, 1, 0);
	CreateLink(script, graph, modsmenu, 3, 0);
	CreateLink(script, modsmenu, exit, 0, 0);
	CKBehavior* keyboard = FindFirstBB(graph, "Keyboard");
	FindBB(keyboard, [keyboard](CKBehavior* beh) {
		CKParameter* source = beh->GetInputParameter(0)->GetRealSource();
		if (GetParamValue<CKKEYBOARD>(source) == CKKEY_ESCAPE) {
			CKBehavior* id = FindNextBB(keyboard, beh);
			SetParamValue(id->GetInputParameter(0)->GetRealSource(), 4);
			return false;
		}
		return true;
		}, "Secure Key");

	GetLogger()->Info("Mods Button inserted");
}

void BMLMod::OnEditScript_Gameplay_Ingame(CKBehavior* script) {
	GetLogger()->Info("Insert Ball/Camera Active/Inactive Hook");
	CKBehavior* camonoff = FindFirstBB(script, "CamNav On/Off");
	CKBehavior* ballonoff = FindFirstBB(script, "BallNav On/Off");
	CKMessageManager* mm = m_bml->GetMessageManager();
	CKMessageType camon = mm->AddMessageType("CamNav activate"), camoff = mm->AddMessageType("CamNav deactivate"),
		ballon = mm->AddMessageType("BallNav activate"), balloff = mm->AddMessageType("BallNav deactivate");
	CKBehavior* con, * coff, * bon, * boff;
	FindBB(camonoff, [camonoff, camon, camoff, &con, &coff](CKBehavior* beh) {
		CKMessageType msg = GetParamValue<CKMessageType>(beh->GetInputParameter(0)->GetDirectSource());
		if (msg == camon) con = beh;
		if (msg == camoff) coff = beh;
		return true;
		}, "Wait Message");
	CreateLink(camonoff, con, CreateBB(camonoff, BML_ONCAMNAVACTIVE_GUID), 0, 0);
	CreateLink(camonoff, coff, CreateBB(camonoff, BML_ONCAMNAVINACTIVE_GUID), 0, 0);
	FindBB(ballonoff, [ballonoff, ballon, balloff, &bon, &boff](CKBehavior* beh) {
		CKMessageType msg = GetParamValue<CKMessageType>(beh->GetInputParameter(0)->GetDirectSource());
		if (msg == ballon) bon = beh;
		if (msg == balloff) boff = beh;
		return true;
		}, "Wait Message");
	CreateLink(ballonoff, bon, CreateBB(ballonoff, BML_ONBALLNAVACTIVE_GUID), 0, 0);
	CreateLink(ballonoff, boff, CreateBB(ballonoff, BML_ONBALLNAVINACTIVE_GUID), 0, 0);

	GetLogger()->Info("Debug Ball Force");
	CKBehavior* ballNav = FindFirstBB(script, "Ball Navigation");
	CKBehavior* nop[2] = { 0 };
	FindBB(ballNav, [&nop, ballNav](CKBehavior* beh) {
		if (nop[0]) nop[1] = beh;
		else nop[0] = beh;
		return !nop[1];
		}, "Nop");
	CKBehavior* keyevent[2] = { CreateBB(ballNav, VT_KEYEVENT), CreateBB(ballNav, VT_KEYEVENT) };
	m_ballForce[0] = CreateParamValue(ballNav, "Up", CKPGUID_KEY, CKKEYBOARD(0));
	m_ballForce[1] = CreateParamValue(ballNav, "Down", CKPGUID_KEY, CKKEYBOARD(0));
	CKBehavior* phyforce[2] = { CreateBB(ballNav, TT_SETPHYSICSFORCE, true), CreateBB(ballNav, TT_SETPHYSICSFORCE, true) };
	CKBehavior* op = FindFirstBB(ballNav, "Op");
	CKParameter* mass = op->GetInputParameter(0)->GetDirectSource();
	CKBehavior* spf = FindFirstBB(ballNav, "SetPhysicsForce");
	CKParameter* dir[2] = { CreateParamValue(ballNav, "Up", CKPGUID_VECTOR, VxVector(0, 1, 0)),
		CreateParamValue(ballNav, "Down", CKPGUID_VECTOR, VxVector(0, -1, 0)) };
	CKBehavior* wake = FindFirstBB(ballNav, "Physics WakeUp");

	for (int i = 0; i < 2; i++) {
		keyevent[i]->GetInputParameter(0)->SetDirectSource(m_ballForce[i]);
		CreateLink(ballNav, nop[0], keyevent[i], 0, 0);
		CreateLink(ballNav, nop[1], keyevent[i], 0, 1);
		phyforce[i]->GetTargetParameter()->ShareSourceWith(spf->GetTargetParameter());
		phyforce[i]->GetInputParameter(0)->ShareSourceWith(spf->GetInputParameter(0));
		phyforce[i]->GetInputParameter(1)->ShareSourceWith(spf->GetInputParameter(1));
		phyforce[i]->GetInputParameter(2)->SetDirectSource(dir[i]);
		phyforce[i]->GetInputParameter(3)->ShareSourceWith(spf->GetInputParameter(3));
		phyforce[i]->GetInputParameter(4)->SetDirectSource(mass);
		CreateLink(ballNav, keyevent[i], phyforce[i], 0, 0);
		CreateLink(ballNav, keyevent[i], phyforce[i], 1, 1);
		CreateLink(ballNav, nop[1], phyforce[i], 0, 1);
		CreateLink(ballNav, phyforce[i], wake, 0, 0);
		CreateLink(ballNav, phyforce[i], wake, 1, 0);
	}

	CKBehavior* ballMgr = FindFirstBB(script, "BallManager");
	m_dynamicPos = FindNextBB(script, ballMgr, "TT Set Dynamic Position");
	CKBehavior* deactBall = FindFirstBB(ballMgr, "Deactivate Ball");
	CKBehavior* pieces = FindFirstBB(deactBall, "reset Ballpieces");
	m_oclinks[0] = FindNextLink(deactBall, pieces);
	CKBehavior* unphy = FindNextBB(deactBall, FindNextBB(deactBall, m_oclinks[0]->GetOutBehaviorIO()->GetOwner()));
	m_oclinkio[0][1] = unphy->GetInput(1);

	CKBehavior* newBall = FindFirstBB(ballMgr, "New Ball");
	m_phyNewBall = FindFirstBB(newBall, "physicalize new Ball");
	m_oclinks[1] = FindPreviousLink(newBall, FindPreviousBB(newBall, FindPreviousBB(newBall, FindPreviousBB(newBall, m_phyNewBall))));
	m_oclinkio[1][1] = m_phyNewBall->GetInput(0);

	CKBehavior* trafoMgr = FindFirstBB(script, "Trafo Manager");
	m_setNewBall = FindFirstBB(trafoMgr, "set new Ball");
	CKBehavior* sop = FindFirstBB(m_setNewBall, "Switch On Parameter");
	m_curTrafo = sop->GetInputParameter(0)->GetDirectSource();
	m_curLevel = m_bml->GetArrayByName("CurrentLevel");
	m_ingameParam = m_bml->GetArrayByName("IngameParameter");
}

void BMLMod::OnEditScript_Gameplay_Energy(CKBehavior* script) {
	GetLogger()->Info("Insert Counter Active/Inactive Hook");
	CKBehavior* som = FindFirstBB(script, "Switch On Message");
	InsertBB(script, FindNextLink(script, som, nullptr, 3), CreateBB(script, BML_ONCOUNTERACTIVE_GUID));
	InsertBB(script, FindNextLink(script, som, nullptr, 1), CreateBB(script, BML_ONCOUNTERINACTIVE_GUID));

	GetLogger()->Info("Insert Life/Point Hooks");
	CKMessageManager* mm = m_bml->GetMessageManager();
	CKMessageType lifeup = mm->AddMessageType("Life_Up"), balloff = mm->AddMessageType("Ball Off"),
		sublife = mm->AddMessageType("Sub Life"), extrapoint = mm->AddMessageType("Extrapoint");
	CKBehavior* lu, * bo, * sl, * ep;
	FindBB(script, [script, lifeup, balloff, sublife, extrapoint, &lu, &bo, &sl, &ep](CKBehavior* beh) {
		CKMessageType msg = GetParamValue<CKMessageType>(beh->GetInputParameter(0)->GetDirectSource());
		if (msg == lifeup) lu = beh;
		if (msg == balloff) bo = beh;
		if (msg == sublife) sl = beh;
		if (msg == extrapoint) ep = beh;
		return true;
		}, "Wait Message");
	CKBehavior* luhook = CreateBB(script, BML_ONPRELIFEUP_GUID);
	InsertBB(script, FindNextLink(script, lu, "add Life"), luhook);
	CreateLink(script, FindEndOfChain(script, luhook), CreateBB(script, BML_ONPOSTLIFEUP_GUID));
	InsertBB(script, FindNextLink(script, bo, "Delayer"), CreateBB(script, BML_ONBALLOFF_GUID));
	CKBehavior* slhook = CreateBB(script, BML_ONPRESUBLIFE_GUID);
	InsertBB(script, FindNextLink(script, sl, "sub Life"), slhook);
	CreateLink(script, FindEndOfChain(script, slhook), CreateBB(script, BML_ONPOSTSUBLIFE_GUID));
	InsertBB(script, FindNextLink(script, ep, "Show"), CreateBB(script, BML_ONEXTRAPOINT_GUID));

	CKBehavior* delay = FindFirstBB(script, "Delayer");
	m_oclinks[2] = FindPreviousLink(script, delay);
	CKBehaviorLink* link = FindNextLink(script, delay);
	m_oclinkio[2][1] = link->GetOutBehaviorIO();

	for (int i = 0; i < 3; i++) {
		m_oclinkio[i][0] = m_oclinks[i]->GetOutBehaviorIO();
		if (m_overclock->GetBoolean())
			m_oclinks[i]->SetOutBehaviorIO(m_oclinkio[i][1]);
	}
}

void BMLMod::OnEditScript_Gameplay_Events(CKBehavior* script) {
	GetLogger()->Info("Insert Checkpoint & GameOver Hooks");
	CKMessageManager* mm = m_bml->GetMessageManager();
	CKMessageType checkpoint = mm->AddMessageType("Checkpoint reached"),
		gameover = mm->AddMessageType("Game Over"),
		levelfinish = mm->AddMessageType("Level_Finish");
	CKBehavior* cp, * go, * lf;
	FindBB(script, [script, checkpoint, gameover, levelfinish, &cp, &go, &lf](CKBehavior* beh) {
		CKMessageType msg = GetParamValue<CKMessageType>(beh->GetInputParameter(0)->GetDirectSource());
		if (msg == checkpoint) cp = beh;
		if (msg == gameover) go = beh;
		if (msg == levelfinish) lf = beh;
		return true;
		}, "Wait Message");
	CKBehavior* hook = CreateBB(script, BML_ONPRECHECKPOINT_GUID);
	InsertBB(script, FindNextLink(script, cp, "set Resetpoint"), hook);
	CreateLink(script, FindEndOfChain(script, hook), CreateBB(script, BML_ONPOSTCHECKPOINT_GUID));
	InsertBB(script, FindNextLink(script, go, "Send Message"), CreateBB(script, BML_ONGAMEOVER_GUID));
	InsertBB(script, FindNextLink(script, lf, "Send Message"), CreateBB(script, BML_ONLEVELFINISH_GUID));

	CKBehavior* id = FindNextBB(script, script->GetInput(0));
	m_curSector = id->GetOutputParameter(0)->GetDestination(0);
}

void BMLMod::OnEditScript_Levelinit_build(CKBehavior* script) {
	CKBehavior* loadLevel = FindFirstBB(script, "Load LevelXX");
	CKBehaviorLink* inLink = FindNextLink(loadLevel, loadLevel->GetInput(0));
	CKBehavior* op = FindNextBB(loadLevel, inLink->GetOutBehaviorIO()->GetOwner());
	m_levelRow = op->GetOutputParameter(0)->GetDestination(0);
	CKBehavior* objLoad = FindFirstBB(loadLevel, "Object Load");
	CKBehavior* bin = CreateBB(loadLevel, VT_BINARYSWITCH);
	CreateLink(loadLevel, loadLevel->GetInput(0), bin, 0);
	m_loadCustom = CreateLocalParameter(loadLevel, "Custom Level", CKPGUID_BOOL);
	bin->GetInputParameter(0)->SetDirectSource(m_loadCustom);
	inLink->SetInBehaviorIO(bin->GetOutput(1));
	CreateLink(loadLevel, bin, objLoad);
	m_mapFile = objLoad->GetInputParameter(0)->GetDirectSource();
}

void BMLMod::OnEditScript_ExtraLife_Fix(CKBehavior* script) {
	CKBehavior* emitter = FindFirstBB(script, "SphericalParticleSystem");
	emitter->CreateInputParameter("Real-Time Mode", CKPGUID_BOOL)
		->SetDirectSource(CreateParamValue<CKBOOL>(script, "Real-Time Mode", CKPGUID_BOOL, 1));
	emitter->CreateInputParameter("DeltaTime", CKPGUID_FLOAT)
		->SetDirectSource(CreateParamValue<float>(script, "DeltaTime", CKPGUID_FLOAT, 20.0f));
}

void BMLMod::OnCheatEnabled(bool enable) {
	if (enable) {
		SetParamValue(m_ballForce[0], m_ballCheat[0]->GetKey());
		SetParamValue(m_ballForce[1], m_ballCheat[1]->GetKey());
	}
	else {
		SetParamValue(m_ballForce[0], CKKEYBOARD(0));
		SetParamValue(m_ballForce[1], CKKEYBOARD(0));
	}
}

void BMLMod::OnModifyConfig(CKSTRING category, CKSTRING key, IProperty* prop) {
	if (m_bml->IsCheatEnabled()) {
		if (prop == m_ballCheat[0])
			SetParamValue(m_ballForce[0], m_ballCheat[0]->GetKey());
		if (prop == m_ballCheat[1])
			SetParamValue(m_ballForce[1], m_ballCheat[1]->GetKey());
	}
	if (prop == m_overclock) {
		for (int i = 0; i < 3; i++) {
			m_oclinks[i]->SetOutBehaviorIO(m_oclinkio[i][m_overclock->GetBoolean()]);
		}
	}
	if (prop == m_showFPS) {
		m_fps->SetVisible(prop->GetBoolean());
	}
	if (prop == m_showSR && m_bml->IsIngame()) {
		m_srScore->SetVisible(m_showSR->GetBoolean());
		m_srTitle->SetVisible(m_showSR->GetBoolean());
	}
}

void BMLMod::OnLoad() {
	GetConfig()->SetCategoryComment("Misc", "Miscellaneous");
	m_skipAnim = GetConfig()->GetProperty("Misc", "SkipLoadingAnim");
	m_skipAnim->SetComment("Skip the Loading Animation");
	m_skipAnim->SetDefaultBoolean(true);

	m_fullscreenKey = GetConfig()->GetProperty("Misc", "Fullscreen");
	m_fullscreenKey->SetComment("Toggle Fullscreen in game");
	m_fullscreenKey->SetDefaultKey(CKKEY_F11);

	m_unlockRes = GetConfig()->GetProperty("Misc", "UnlockResolution");
	m_unlockRes->SetComment("Unlock 16:9 Resolutions");
	m_unlockRes->SetDefaultBoolean(true);

	m_overclock = GetConfig()->GetProperty("Misc", "Overclock");
	m_overclock->SetComment("Remove delay of spawn / respawn");
	m_overclock->SetDefaultBoolean(false);

	m_showFPS = GetConfig()->GetProperty("Misc", "ShowFPS");
	m_showFPS->SetComment("Show FPS at top-left corner");
	m_showFPS->SetDefaultBoolean(true);

	m_showSR = GetConfig()->GetProperty("Misc", "ShowSRTimer");
	m_showSR->SetComment("Show SR Timer above Time Score");
	m_showSR->SetDefaultBoolean(true);

	m_fixLifeBall = GetConfig()->GetProperty("Misc", "FixLifeBallFreeze");
	m_fixLifeBall->SetComment("Game won't freeze when picking up life balls");
	m_fixLifeBall->SetDefaultBoolean(true);

	GetConfig()->SetCategoryComment("Debug", "Debug Utilities");
	m_suicide = GetConfig()->GetProperty("Debug", "Suicide");
	m_suicide->SetComment("Suicide");
	m_suicide->SetDefaultKey(CKKEY_R);

	m_ballCheat[0] = GetConfig()->GetProperty("Debug", "BallUp");
	m_ballCheat[0]->SetComment("Apply an upward force to the ball");
	m_ballCheat[0]->SetDefaultKey(CKKEY_F1);

	m_ballCheat[1] = GetConfig()->GetProperty("Debug", "BallDown");
	m_ballCheat[1]->SetComment("Apply a downward force to the ball");
	m_ballCheat[1]->SetDefaultKey(CKKEY_F2);

	m_changeBall[0] = GetConfig()->GetProperty("Debug", "TurnPaper");
	m_changeBall[0]->SetComment("Turn into paper ball");
	m_changeBall[0]->SetDefaultKey(CKKEY_I);

	m_changeBall[1] = GetConfig()->GetProperty("Debug", "TurnWood");
	m_changeBall[1]->SetComment("Turn into wood ball");
	m_changeBall[1]->SetDefaultKey(CKKEY_O);

	m_changeBall[2] = GetConfig()->GetProperty("Debug", "TurnStone");
	m_changeBall[2]->SetComment("Turn into stone ball");
	m_changeBall[2]->SetDefaultKey(CKKEY_P);

	m_resetBall = GetConfig()->GetProperty("Debug", "ResetBall");
	m_resetBall->SetComment("Reset ball and all moduls");
	m_resetBall->SetDefaultKey(CKKEY_BACK);

	m_addLife = GetConfig()->GetProperty("Debug", "AddLife");
	m_addLife->SetComment("Add one extra Life");
	m_addLife->SetDefaultKey(CKKEY_L);

	m_speedupBall = GetConfig()->GetProperty("Debug", "BallSpeedUp");
	m_speedupBall->SetComment("Change to 3 times ball speed");
	m_speedupBall->SetDefaultKey(CKKEY_LCONTROL);

	GetConfig()->SetCategoryComment("Auxiliaries", "Temporal Auxiliary Moduls");
	m_addBall[0] = GetConfig()->GetProperty("Auxiliaries", "PaperBall");
	m_addBall[0]->SetComment("Add a Paper Ball");
	m_addBall[0]->SetDefaultKey(CKKEY_J);

	m_addBall[1] = GetConfig()->GetProperty("Auxiliaries", "WoodBall");
	m_addBall[1]->SetComment("Add a Wood Ball");
	m_addBall[1]->SetDefaultKey(CKKEY_K);

	m_addBall[2] = GetConfig()->GetProperty("Auxiliaries", "StoneBall");
	m_addBall[2]->SetComment("Add a Stone Ball");
	m_addBall[2]->SetDefaultKey(CKKEY_N);

	m_addBall[3] = GetConfig()->GetProperty("Auxiliaries", "Box");
	m_addBall[3]->SetComment("Add a Box");
	m_addBall[3]->SetDefaultKey(CKKEY_M);

	m_moveKeys[0] = GetConfig()->GetProperty("Auxiliaries", "MoveFront");
	m_moveKeys[0]->SetComment("Move Front");
	m_moveKeys[0]->SetDefaultKey(CKKEY_UP);

	m_moveKeys[1] = GetConfig()->GetProperty("Auxiliaries", "MoveBack");
	m_moveKeys[1]->SetComment("Move Back");
	m_moveKeys[1]->SetDefaultKey(CKKEY_DOWN);

	m_moveKeys[2] = GetConfig()->GetProperty("Auxiliaries", "MoveLeft");
	m_moveKeys[2]->SetComment("Move Left");
	m_moveKeys[2]->SetDefaultKey(CKKEY_LEFT);

	m_moveKeys[3] = GetConfig()->GetProperty("Auxiliaries", "MoveRight");
	m_moveKeys[3]->SetComment("Move Right");
	m_moveKeys[3]->SetDefaultKey(CKKEY_RIGHT);

	m_moveKeys[4] = GetConfig()->GetProperty("Auxiliaries", "MoveUp");
	m_moveKeys[4]->SetComment("Move Up");
	m_moveKeys[4]->SetDefaultKey(CKKEY_RSHIFT);

	m_moveKeys[5] = GetConfig()->GetProperty("Auxiliaries", "MoveDown");
	m_moveKeys[5]->SetComment("Move Down");
	m_moveKeys[5]->SetDefaultKey(CKKEY_RCONTROL);

	GetConfig()->SetCategoryComment("Camera", "Camera Utilities");
	m_camOn = GetConfig()->GetProperty("Camera", "Enable");
	m_camOn->SetComment("Enable Camera Utilities");
	m_camOn->SetDefaultBoolean(false);

	m_camReset = GetConfig()->GetProperty("Camera", "Reset");
	m_camReset->SetComment("Reset Camera");
	m_camReset->SetDefaultKey(CKKEY_D);

	m_cam45 = GetConfig()->GetProperty("Camera", "Rotate45");
	m_cam45->SetComment("Set to 45 degrees");
	m_cam45->SetDefaultKey(CKKEY_W);

	m_camRot[0] = GetConfig()->GetProperty("Camera", "RotateLeft");
	m_camRot[0]->SetComment("Rotate the camera");
	m_camRot[0]->SetDefaultKey(CKKEY_Q);

	m_camRot[1] = GetConfig()->GetProperty("Camera", "RotateRight");
	m_camRot[1]->SetComment("Rotate the camera");
	m_camRot[1]->SetDefaultKey(CKKEY_E);

	m_camY[0] = GetConfig()->GetProperty("Camera", "MoveUp");
	m_camY[0]->SetComment("Move the camera");
	m_camY[0]->SetDefaultKey(CKKEY_A);

	m_camY[1] = GetConfig()->GetProperty("Camera", "MoveDown");
	m_camY[1]->SetComment("Move the camera");
	m_camY[1]->SetDefaultKey(CKKEY_Z);

	m_camZ[0] = GetConfig()->GetProperty("Camera", "MoveFront");
	m_camZ[0]->SetComment("Move the camera");
	m_camZ[0]->SetDefaultKey(CKKEY_S);

	m_camZ[1] = GetConfig()->GetProperty("Camera", "MoveBack");
	m_camZ[1]->SetComment("Move the camera");
	m_camZ[1]->SetDefaultKey(CKKEY_X);

	m_bml->RegisterCommand(new CommandBML());
	m_bml->RegisterCommand(new CommandHelp());
	m_bml->RegisterCommand(new CommandCheat());
	m_bml->RegisterCommand(new CommandClear());
	m_bml->RegisterCommand(new CommandScore());
	m_bml->RegisterCommand(new CommandSpeed());
	m_bml->RegisterCommand(new CommandKill());
	m_bml->RegisterCommand(new CommandSetSpawn());
	m_bml->RegisterCommand(new CommandSector());
	m_bml->RegisterCommand(new CommandWin());
	m_bml->RegisterCommand(new CommandTravel(this));

	m_pBalls[0] = static_cast<CK3dEntity*>(ExecuteBB::ObjectLoad("3D Entities\\PH\\P_Ball_Paper.nmo", true, "P_Ball_Paper_MF").second);
	m_pBalls[1] = static_cast<CK3dEntity*>(ExecuteBB::ObjectLoad("3D Entities\\PH\\P_Ball_Wood.nmo", true, "P_Ball_Wood_MF").second);
	m_pBalls[2] = static_cast<CK3dEntity*>(ExecuteBB::ObjectLoad("3D Entities\\PH\\P_Ball_Stone.nmo", true, "P_Ball_Stone_MF").second);
	m_pBalls[3] = static_cast<CK3dEntity*>(ExecuteBB::ObjectLoad("3D Entities\\PH\\P_Box.nmo", true, "P_Box_MF").second);
	m_travelCam = static_cast<CKCamera*>(m_bml->GetCKContext()->CreateObject(CKCID_CAMERA, "TravelCam"));
}

void BMLMod::OnProcess() {
	CKContext* ctx = m_bml->GetCKContext();
	InputHook* im = m_bml->GetInputManager();
	if (im->IsKeyPressed(m_fullscreenKey->GetKey())) {
		CKRenderContext* rc = m_bml->GetRenderContext();
		if (rc->IsFullScreen()) {
			rc->StopFullScreen();
			GetLogger()->Info("Switch to Windowed Mode");
		}
		else {
			rc->GoFullScreen(rc->GetWidth(), rc->GetHeight(), -1, rc->GetDriverIndex());
			GetLogger()->Info("Switch to Fullscreen Mode");
		}
	}

	if (m_ingameBanner) {
		CKStats stats;
		ctx->GetProfileStats(&stats);
		m_fpscnt += int(1000 / stats.TotalFrameTime);
		if (++m_fpstimer == 60) {
			m_fps->SetText(("FPS: " + std::to_string(m_fpscnt / 60)).c_str());
			m_fpstimer = 0;
			m_fpscnt = 0;
		}
	}

	if (m_cmdBar) {
		if (!m_cmdTyping && im->oIsKeyPressed(CKKEY_SLASH)) {
			GetLogger()->Info("Toggle Command Bar");
			m_cmdTyping = true;
			InputHook::SetBlock(true);
			m_cmdBar->SetVisible(true);
			m_historyPos = m_cmdHistory.size();
		}

		m_msgLog->Process();
		if (!IsInTravelCam())
			m_ingameBanner->Process();
		if (m_currentGui)
			m_currentGui->Process();
		m_smHook->Process();

		if (m_cmdTyping) {
			m_cmdBar->Process();

			for (int i = 0; i < min(MSG_MAXSIZE, m_msgCnt); i++) {
				m_msg[i].m_bg->SetVisible(true);
				m_msg[i].m_bg->SetColor(VxColor(0, 0, 0, 110));
				m_msg[i].m_text->SetVisible(true);
			}
		}
		else {
			for (int i = 0; i < min(MSG_MAXSIZE, m_msgCnt); i++) {
				int &timer = m_msg[i].timer;
				m_msg[i].m_bg->SetVisible(timer > 0);
				m_msg[i].m_bg->SetColor(VxColor(0, 0, 0, min(110, timer / 2)));
				m_msg[i].m_text->SetVisible(timer > 100);
			}
		}

		for (int i = 0; i < min(MSG_MAXSIZE, m_msgCnt); i++) {
			m_msg[i].timer--;
		}
	}

	if (m_bml->IsPlaying()) {
		if (!m_suicideCd) {
			if (m_bml->IsPlaying() && im->IsKeyPressed(m_suicide->GetKey())) {
				ModLoader::m_instance->ExecuteCommand("kill");
				m_suicideCd = true;
				m_bml->AddTimer(1000.0f, [this]() { m_suicideCd = false; });
			}
		}

		float deltaTime = m_bml->GetTimeManager()->GetLastDeltaTime() / 10;
		if (m_changeBallCd == 0) {
			for (int i = 0; i < 3; i++) {
				if (m_bml->IsCheatEnabled() && im->IsKeyPressed(m_changeBall[i]->GetKey())) {
					CKMessageManager* mm = m_bml->GetMessageManager();
					CKMessageType ballDeact = mm->AddMessageType("BallNav deactivate");

					mm->SendMessageSingle(ballDeact, m_bml->GetGroupByName("All_Gameplay"));
					mm->SendMessageSingle(ballDeact, m_bml->GetGroupByName("All_Sound"));
					m_changeBallCd = 2;

					m_bml->AddTimer(2u, [this, i]() {
						CK3dEntity* curBall = static_cast<CK3dEntity*>(m_curLevel->GetElementObject(0, 1));
						ExecuteBB::Unphysicalize(curBall);

						static char trafoTypes[3][6] = { "paper", "wood", "stone" };
						SetParamString(m_curTrafo, trafoTypes[i]);
						m_setNewBall->ActivateInput(0);
						m_setNewBall->Activate();

						GetLogger()->Info("Set to %s Ball", i == 0 ? "Paper" : i == 1 ? "Wood" : "Stone");
						});
				}
			}
		}
		else m_changeBallCd--;

		if (m_bml->IsCheatEnabled() && im->IsKeyPressed(m_resetBall->GetKey())) {
			CKMessageManager* mm = m_bml->GetMessageManager();
			CKMessageType ballDeact = mm->AddMessageType("BallNav deactivate");

			mm->SendMessageSingle(ballDeact, m_bml->GetGroupByName("All_Gameplay"));
			mm->SendMessageSingle(ballDeact, m_bml->GetGroupByName("All_Sound"));

			m_bml->AddTimer(2u, [this, ctx]() {
				CK3dEntity* curBall = static_cast<CK3dEntity*>(m_curLevel->GetElementObject(0, 1));
				if (curBall) {
					ExecuteBB::Unphysicalize(curBall);

					CKDataArray* ph = m_bml->GetArrayByName("PH");
					for (int i = 0; i < ph->GetRowCount(); i++) {
						CKBOOL set = true;
						char name[100];
						ph->GetElementStringValue(i, 1, name);
						if (!strcmp(name, "P_Extra_Point"))
							ph->SetElementValue(i, 4, &set);
					}

					m_ingameParam->SetElementValueFromParameter(0, 1, m_curSector);
					m_ingameParam->SetElementValueFromParameter(0, 2, m_curSector);
					CKBehavior* sectorMgr = m_bml->GetScriptByName("Gameplay_SectorManager");
					ctx->GetCurrentScene()->Activate(sectorMgr, true);

					m_bml->AddTimerLoop(1u, [this, curBall, sectorMgr, ctx]() {
						if (sectorMgr->IsActive())
							return true;

						m_dynamicPos->ActivateInput(1);
						m_dynamicPos->Activate();

						m_bml->AddTimer(1u, [this, curBall, sectorMgr, ctx]() {
							VxMatrix matrix;
							m_curLevel->GetElementValue(0, 3, &matrix);
							curBall->SetWorldMatrix(matrix);

							CK3dEntity* camMF = m_bml->Get3dEntityByName("Cam_MF");
							m_bml->RestoreIC(camMF, true);
							camMF->SetWorldMatrix(matrix);

							m_bml->AddTimer(1u, [this]() {
								m_dynamicPos->ActivateInput(0);
								m_dynamicPos->Activate();

								m_phyNewBall->ActivateInput(0);
								m_phyNewBall->Activate();
								m_phyNewBall->GetParent()->Activate();

								GetLogger()->Info("Sector Reset");
								});
							});

						return false;
						});
				}
				});
		}

		if (IsInTravelCam()) {
			if (im->IsKeyDown(CKKEY_W)) m_travelCam->Translate(VxVector(0, 0, 0.2f * deltaTime), m_travelCam);
			if (im->IsKeyDown(CKKEY_S)) m_travelCam->Translate(VxVector(0, 0, -0.2f * deltaTime), m_travelCam);
			if (im->IsKeyDown(CKKEY_A)) m_travelCam->Translate(VxVector(-0.2f * deltaTime, 0, 0), m_travelCam);
			if (im->IsKeyDown(CKKEY_D)) m_travelCam->Translate(VxVector(0.2f * deltaTime, 0, 0), m_travelCam);
			if (im->IsKeyDown(CKKEY_SPACE)) m_travelCam->Translate(VxVector(0, 0.2f * deltaTime, 0));
			if (im->IsKeyDown(CKKEY_LSHIFT)) m_travelCam->Translate(VxVector(0, -0.2f * deltaTime, 0));
			VxVector delta;
			im->GetMouseRelativePosition(delta);
			m_travelCam->Rotate(VxVector(0, 1, 0), -delta.x * 2 / m_bml->GetRenderContext()->GetWidth());
			m_travelCam->Rotate(VxVector(1, 0, 0), -delta.y * 2 / m_bml->GetRenderContext()->GetWidth(), m_travelCam);
		}
		else if (m_camOn->GetBoolean()) {
			if (im->IsKeyPressed(m_cam45->GetKey())) {
				m_camOrientRef->Rotate(VxVector(0, 1, 0), PI / 4, m_camOrientRef);
				m_camOrient->SetQuaternion(VxQuaternion(), m_camOrientRef);
			}
			if (im->IsKeyDown(m_camRot[0]->GetKey())) {
				m_camOrientRef->Rotate(VxVector(0, 1, 0), -0.01f * deltaTime, m_camOrientRef);
				m_camOrient->SetQuaternion(VxQuaternion(), m_camOrientRef);
			}
			if (im->IsKeyDown(m_camRot[1]->GetKey())) {
				m_camOrientRef->Rotate(VxVector(0, 1, 0), 0.01f * deltaTime, m_camOrientRef);
				m_camOrient->SetQuaternion(VxQuaternion(), m_camOrientRef);
			}
			if (im->IsKeyDown(m_camY[0]->GetKey()))
				m_camPos->Translate(VxVector(0, 0.15f * deltaTime, 0), m_camOrientRef);
			if (im->IsKeyDown(m_camY[1]->GetKey()))
				m_camPos->Translate(VxVector(0, -0.15f * deltaTime, 0), m_camOrientRef);
			if (im->IsKeyDown(m_camZ[0]->GetKey())) {
				VxVector position;
				m_camPos->GetPosition(&position, m_camOrientRef);
				position.z = (std::min)(position.z + 0.1f * deltaTime, -0.1f);
				m_camPos->SetPosition(position, m_camOrientRef);
			}
			if (im->IsKeyDown(m_camZ[1]->GetKey()))
				m_camPos->Translate(VxVector(0, 0, -0.1f * deltaTime), m_camOrientRef);
			if (im->IsKeyDown(m_camReset->GetKey())) {
				VxQuaternion rotation;
				m_camOrientRef->GetQuaternion(&rotation, m_camTarget);
				if (rotation.angle > 0.9f)
					rotation = VxQuaternion();
				else {
					rotation = rotation + VxQuaternion();
					rotation *= 0.5f;
				}
				m_camOrientRef->SetQuaternion(rotation, m_camTarget);
				m_camOrient->SetQuaternion(VxQuaternion(), m_camOrientRef);
				m_camPos->SetPosition(VxVector(0, 35, -22), m_camOrient);
			}
		}

		if (!m_addLifeCd) {
			if (m_bml->IsCheatEnabled() && im->IsKeyPressed(m_addLife->GetKey())) {
				CKMessageManager* mm = m_bml->GetMessageManager();
				CKMessageType addLife = mm->AddMessageType("Life_Up");

				mm->SendMessageSingle(addLife, m_bml->GetGroupByName("All_Gameplay"));
				mm->SendMessageSingle(addLife, m_bml->GetGroupByName("All_Sound"));
				m_addLifeCd = true;
				m_bml->AddTimer(1000.0f, [this]() { m_addLifeCd = false; });
			}
		}

		if (m_bml->IsCheatEnabled()) {
			if (m_curSel < 0) {
				for (int i = 0; i < 4; i++) {
					if (im->IsKeyDown(m_addBall[i]->GetKey())) {
						m_curSel = i;
						InputHook::SetBlock(true);
					}
				}

				if (m_curSel >= 0) {
					m_curObj = static_cast<CK3dEntity*>(ctx->CopyObject(m_pBalls[m_curSel]));
					m_curObj->SetPosition(VxVector(0, 5, 0), m_camTarget);
					m_curObj->Show();
				}
			}
			else if (im->oIsKeyDown(m_addBall[m_curSel]->GetKey())) {
				if (im->oIsKeyDown(m_moveKeys[0]->GetKey())) m_curObj->Translate(VxVector(0, 0, 0.1f * deltaTime), m_camOrientRef);
				if (im->oIsKeyDown(m_moveKeys[1]->GetKey())) m_curObj->Translate(VxVector(0, 0, -0.1f * deltaTime), m_camOrientRef);
				if (im->oIsKeyDown(m_moveKeys[2]->GetKey())) m_curObj->Translate(VxVector(-0.1f * deltaTime, 0, 0), m_camOrientRef);
				if (im->oIsKeyDown(m_moveKeys[3]->GetKey())) m_curObj->Translate(VxVector(0.1f * deltaTime, 0, 0), m_camOrientRef);
				if (im->oIsKeyDown(m_moveKeys[4]->GetKey())) m_curObj->Translate(VxVector(0, 0.1f * deltaTime, 0), m_camOrientRef);
				if (im->oIsKeyDown(m_moveKeys[5]->GetKey())) m_curObj->Translate(VxVector(0, -0.1f * deltaTime, 0), m_camOrientRef);
			}
			else {
				CKMesh* mesh = m_curObj->GetMesh(0);
				switch (m_curSel) {
				case 0:
					ExecuteBB::PhysicalizeConvex(m_curObj, false, 0.5f, 0.4f, 0.2f, "", false, true, false, 1.5f, 0.1f, mesh->GetName(), VxVector(), mesh);
					break;
				case 1:
					ExecuteBB::PhysicalizeBall(m_curObj, false, 0.6f, 0.2f, 2.0f, "", false, true, false, 0.6f, 0.1f, mesh->GetName());
					break;
				case 2:
					ExecuteBB::PhysicalizeBall(m_curObj, false, 0.7f, 0.1f, 10.0f, "", false, true, false, 0.2f, 0.1f, mesh->GetName());
					break;
				default:
					ExecuteBB::PhysicalizeConvex(m_curObj, false, 0.7f, 0.3f, 1.0f, "", false, true, false, 0.1f, 0.1f, mesh->GetName(), VxVector(), mesh);
					break;
				}

				CKDataArray* ph = m_bml->GetArrayByName("PH");
				ph->AddRow();
				int index = ph->GetRowCount() - 1;
				ph->SetElementValueFromParameter(index, 0, m_curSector);
				static char P_BALL_NAMES[4][13] = { "P_Ball_Paper", "P_Ball_Wood", "P_Ball_Stone", "P_Box" };
				ph->SetElementStringValue(index, 1, P_BALL_NAMES[m_curSel]);
				VxMatrix matrix = m_curObj->GetWorldMatrix();
				ph->SetElementValue(index, 2, &matrix);
				ph->SetElementObject(index, 3, m_curObj);
				CKBOOL set = false;
				ph->SetElementValue(index, 4, &set);

				CKGroup* depth = m_bml->GetGroupByName("DepthTest");
				depth->AddObject(m_curObj);
				m_tempBalls.push_back({ index, m_curObj });

				m_curSel = -1;
				m_curObj = nullptr;
				InputHook::SetBlock(false);

				GetLogger()->Info("Summoned a %s", m_curSel < 2 ? m_curSel == 0 ? "Paper Ball" : "Wood Ball" : m_curSel == 2 ? "Stone Ball" : "Box");
			}
		}

		if (m_bml->IsCheatEnabled()) {
			bool speedup = im->IsKeyDown(m_speedupBall->GetKey());
			if (speedup && !m_speedup)
				ModLoader::m_instance->ExecuteCommand("speed 3");
			if (!speedup && m_speedup)
				ModLoader::m_instance->ExecuteCommand("speed 1");
			m_speedup = speedup;
		}
	}

	if (m_sractive) {
		m_srtimer += m_bml->GetTimeManager()->GetLastDeltaTime();
		int counter = int(m_srtimer);
		int ms = counter % 1000;
		counter /= 1000;
		int s = counter % 60;
		counter /= 60;
		int m = counter % 60;
		counter /= 60;
		int h = counter % 100;
		static char time[16];
		sprintf(time, "%02d:%02d:%02d.%03d", h, m, s, ms);
		m_srScore->SetText(time);
	}

	if (m_mapsGui) {
		bool inStart = m_level01->IsVisible();
		m_customMaps->SetVisible(inStart);
	}
}

void BMLMod::OnPostResetLevel() {
	CKDataArray* ph = m_bml->GetArrayByName("PH");
	for (auto iter = m_tempBalls.rbegin(); iter != m_tempBalls.rend(); iter++) {
		ph->RemoveRow(iter->first);
		m_bml->GetCKContext()->DestroyObject(iter->second);
	}
	m_tempBalls.clear();
}

void BMLMod::OnStartLevel() {
	m_srtimer = 0.0f;
	m_srScore->SetText("00:00:00.000");
	if (m_showSR->GetBoolean()) {
		m_srScore->SetVisible(true);
		m_srTitle->SetVisible(true);
	}
	SetParamValue(m_loadCustom, FALSE);
}

void BMLMod::OnPostExitLevel() {
	m_srScore->SetVisible(false);
	m_srTitle->SetVisible(false);
}

void BMLMod::OnPauseLevel() {
	m_sractive = false;
}

void BMLMod::OnUnpauseLevel() {
	m_sractive = true;
}

void BMLMod::OnCounterActive() {
	m_sractive = true;
}

void BMLMod::OnCounterInactive() {
	m_sractive = false;
}

void BMLMod::OnCmdEdit(CKDWORD key) {
	switch (key) {
	case CKKEY_RETURN:
		m_cmdHistory.push_back(m_cmdInput->GetText());
		if (m_cmdInput->GetText()[0] == '/') {
			ModLoader::m_instance->ExecuteCommand(m_cmdInput->GetText() + 1);
		}
		else {
			AddIngameMessage(m_cmdInput->GetText());
		}
	case CKKEY_ESCAPE:
		m_cmdTyping = false;
		InputHook::SetBlock(false);
		m_cmdBar->SetVisible(false);
		m_cmdInput->SetText("");
		break;
	case CKKEY_TAB:
		if (m_cmdInput->GetText()[0] == '/') {
			m_cmdInput->SetText(('/' + ModLoader::m_instance->TabCompleteCommand(m_cmdInput->GetText() + 1)).c_str());
		}
		break;
	case CKKEY_UP:
		if (m_historyPos > 0)
			m_cmdInput->SetText(m_cmdHistory[--m_historyPos].c_str());
		break;
	case CKKEY_DOWN:
		if (m_historyPos < m_cmdHistory.size())
			m_cmdInput->SetText(++m_historyPos == m_cmdHistory.size() ? "/" : m_cmdHistory[m_historyPos].c_str());
		break;
	default:;
	}
}

void BMLMod::AddIngameMessage(CKSTRING msg) {
	for (int i = min(MSG_MAXSIZE - 1, m_msgCnt) - 1; i >= 0; i--) {
		CKSTRING text = m_msg[i].m_text->GetText();
		m_msg[i + 1].m_text->SetText(text);
		m_msg[i + 1].timer = m_msg[i].timer;
	}

	m_msg[0].m_text->SetText(msg);
	m_msg[0].timer = 1000;
	m_msgCnt++;

	GetLogger()->Info(msg);
}

void BMLMod::ShowCheatBanner(bool show) {
	m_cheat->SetVisible(show);
}

void BMLMod::ShowModOptions() {
	ShowGui(m_modOption);
	m_modOption->SetPage(0);
}

void BMLMod::ShowGui(BGui::Gui* gui) {
	if (m_currentGui != nullptr)
		CloseCurrentGui();
	m_bml->AddTimer(1u, [this, gui]() {
		m_currentGui = gui;
		if (gui)
			gui->SetVisible(true);
		});
}

void BMLMod::CloseCurrentGui() {
	m_currentGui->SetVisible(false);
	m_currentGui = nullptr;
}

void BMLMod::EnterTravelCam() {
	CKCamera* cam = m_bml->GetTargetCameraByName("InGameCam");
	m_travelCam->SetWorldMatrix(cam->GetWorldMatrix());
	int width, height;
	cam->GetAspectRatio(width, height);
	m_travelCam->SetAspectRatio(width, height);
	m_travelCam->SetFov(cam->GetFov());
	m_bml->GetRenderContext()->AttachViewpointToCamera(m_travelCam);
}

void BMLMod::ExitTravelCam() {
	CKCamera* cam = m_bml->GetTargetCameraByName("InGameCam");
	m_bml->GetRenderContext()->AttachViewpointToCamera(cam);
}

void CommandTravel::Execute(IBML* bml, const std::vector<std::string>& args) {
	if (bml->IsPlaying()) {
		if (m_mod->IsInTravelCam()) {
			m_mod->ExitTravelCam();
			m_mod->AddIngameMessage("Exit Travel Camera");
			bml->GetGroupByName("HUD_sprites")->Show();
			bml->GetGroupByName("LifeBalls")->Show();
		}
		else {
			m_mod->EnterTravelCam();
			m_mod->AddIngameMessage("Enter Travel Camera");
			bml->GetGroupByName("HUD_sprites")->Show(CKHIDE);
			bml->GetGroupByName("LifeBalls")->Show(CKHIDE);
		}
	}
}

bool BMLMod::IsInTravelCam() {
	return m_bml->GetRenderContext()->GetAttachedCamera() == m_travelCam;
}

GuiList::GuiList() {
	m_left = AddLeftButton("M_List_Left", 0.12f, 0.36f, [this]() { PreviousPage(); });
	m_right = AddRightButton("M_List_Right", 0.12f, 0.6038f, [this]() { NextPage(); });
	AddBackButton("M_Opt_Mods_Back")->SetCallback([this]() { Exit(); });
}

void GuiList::Init(int size, int maxsize) {
	m_size = size;
	m_maxpage = (size + maxsize - 1) / maxsize;
	m_maxsize = maxsize;
	m_curpage = 0;

	for (int i = 0; i < m_size; i++)
		m_guiList.push_back(CreateSubGui(i));
	for (int i = 0; i < m_maxsize; i++) {
		BGui::Button* button = CreateButton(i);
		if (m_size > 0 && m_guiList[0] != nullptr) {
			button->SetCallback([this, i]() {
				BGui::Gui* gui = m_guiList[m_maxsize * m_curpage + i];
				ModLoader::m_instance->m_bmlmod->ShowGui(gui);
				});
		}
		m_buttons.push_back(button);
	}
}

void GuiList::SetPage(int page) {
	int size = (std::min)(m_maxsize, m_size - page * m_maxsize);
	for (int i = 0; i < m_maxsize; i++)
		m_buttons[i]->SetVisible(i < size);
	for (int i = 0; i < size; i++)
		m_buttons[i]->SetText(GetButtonText(page * m_maxsize + i).c_str());

	m_curpage = page;
	m_left->SetVisible(page > 0);
	m_right->SetVisible(page < m_maxpage - 1);
}

void GuiList::Exit() {
	ModLoader::m_instance->m_bmlmod->ShowGui(GetParentGui());
}

void GuiList::SetVisible(bool visible) {
	Gui::SetVisible(visible);
	if (visible) SetPage(m_curpage);
}

GuiModOption::GuiModOption() {
	Init(ModLoader::m_instance->m_mods.size(), 4);

	AddTextLabel("M_Opt_Mods_Title", "Mod List", ExecuteBB::GAMEFONT_02, 0.35f, 0.1f, 0.3f, 0.1f);
}

BGui::Button* GuiModOption::CreateButton(int index) {
	return AddSettingButton(("M_Opt_Mods_" + std::to_string(index)).c_str(), "", 0.25f + 0.13f * index);
}

std::string GuiModOption::GetButtonText(int index) {
	return ModLoader::m_instance->m_mods[index]->GetID();
}

BGui::Gui* GuiModOption::CreateSubGui(int index) {
	return new GuiModMenu(ModLoader::m_instance->m_mods[index]);
}

BGui::Gui* GuiModOption::GetParentGui() {
	return nullptr;
}

void GuiModOption::Exit() {
	GuiList::Exit();
	ModLoader::m_instance->GetCKContext()->GetCurrentScene()->Activate(
		ModLoader::m_instance->GetScriptByName("Menu_Options"),
		true);
}

GuiModMenu::GuiModMenu(IMod* mod) : GuiList() {
	m_left->SetPosition(Vx2DVector(0.36f, 0.3f));
	m_right->SetPosition(Vx2DVector(0.6038f, 0.3f));
	AddTextLabel("M_Opt_ModMenu_Name", mod->GetName(), ExecuteBB::GAMEFONT_01, 0.35f, 0.1f, 0.3f, 0.05f);
	AddTextLabel("M_Opt_ModMenu_Author", (std::string("by ") + mod->GetAuthor()).c_str(), ExecuteBB::GAMEFONT_03, 0.35f, 0.13f, 0.3f, 0.04f);
	AddTextLabel("M_Opt_ModMenu_Version", (std::string("v") + mod->GetVersion()).c_str(), ExecuteBB::GAMEFONT_03, 0.35f, 0.15f, 0.3f, 0.04f);
	BGui::Label* desc = AddTextLabel("M_Opt_ModMenu_Description", mod->GetDescription(), ExecuteBB::GAMEFONT_03, 0.35f, 0.20f, 0.3f, 0.1f);
	desc->SetTextFlags(TEXT_SCREEN | TEXT_WORDWRAP);
	desc->SetAlignment(ALIGN_TOP);

	m_config = ModLoader::m_instance->GetConfig(mod);
	if (m_config) {
		AddTextLabel("M_Opt_ModMenu_Title", "Mod Options", ExecuteBB::GAMEFONT_01, 0.35f, 0.4f, 0.3f, 0.05f);
		for (auto& cate : m_config->m_data)
			m_categories.push_back(cate.name);
	}

	Init(m_categories.size(), 6);
	SetVisible(false);
}

BGui::Button* GuiModMenu::CreateButton(int index) {
	BGui::Button* button = AddLevelButton(("M_Opt_ModMenu_" + std::to_string(index)).c_str(), "", 0.45f + 0.06f * index);
	button->SetFont(ExecuteBB::GAMEFONT_03);
	return button;
}

std::string GuiModMenu::GetButtonText(int index) {
	return m_categories[index];
}

BGui::Gui* GuiModMenu::CreateSubGui(int index) {
	return new GuiModCategory(this, m_config, m_categories[index]);
}

BGui::Gui* GuiModMenu::GetParentGui() {
	return ModLoader::m_instance->m_bmlmod->m_modOption;
}

GuiCustomMap::GuiCustomMap(BMLMod* mod) : GuiList(), m_mod(mod) {
	m_left->SetPosition(Vx2DVector(0.34f, 0.4f));
	m_right->SetPosition(Vx2DVector(0.6238f, 0.4f));

	AddTextLabel("M_Opt_Mods_Title", "Custom Maps", ExecuteBB::GAMEFONT_02, 0.35f, 0.07f, 0.3f, 0.1f);
	using convert_type = std::codecvt_byname<wchar_t, char, std::mbstate_t>;
	std::wstring_convert<convert_type, wchar_t> converter(new convert_type("zh-CN"));

	for (auto& f : std::filesystem::recursive_directory_iterator("..\\ModLoader\\Maps")) {
		if (f.status().type() == std::filesystem::file_type::regular) {
			std::string ext = f.path().extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
			if (ext == ".nmo") {
				MapInfo info;
				try {
					info.displayname = f.path().stem().string();
					info.searchname = Text2Pinyin(info.displayname);
					info.filepath = "..\\ModLoader\\Maps\\" + info.displayname + ".nmo";
				}
				catch (std::system_error e) {
					std::string filename = converter.to_bytes(f.path().stem().wstring());
					info.displayname = info.searchname = Text2Pinyin(filename);
					info.filepath = "..\\ModLoader\\Cache\\Maps\\" + info.displayname + ".nmo";
					std::filesystem::copy_file(std::filesystem::absolute(f.path()), info.filepath);
				}

				std::transform(info.searchname.begin(), info.searchname.end(), info.searchname.begin(), tolower);
				m_maps.push_back(info);
			}
		}
	}

	m_exit = AddLeftButton("M_Exit_Custom_Maps", 0.4f, 0.34f, [this]() {
		GuiList::Exit();
		ModLoader::m_instance->GetCKContext()->GetCurrentScene()->Activate(
			ModLoader::m_instance->GetScriptByName("Menu_Start"),
			true);
		});

	AddPanel("M_Map_Search_Bg", VxColor(0, 0, 0, 110), 0.4f, 0.18f, 0.2f, 0.03f);
	m_searchBar = AddTextInput("M_Search_Map", ExecuteBB::GAMEFONT_03, 0.4f, 0.18f, 0.2f, 0.03f, [this](CKDWORD) {
		m_searchRes.clear();
		std::string text = m_searchBar->GetText();
		std::transform(text.begin(), text.end(), text.begin(), tolower);

		for (auto& p : m_maps) {
			if (text.length() == 0 || p.searchname.find(text) != std::string::npos) {
				m_searchRes.push_back(&p);
			}
		}
		m_size = m_searchRes.size();
		m_maxpage = (m_size + m_maxsize - 1) / m_maxsize;
		SetPage(0);
		});

	std::sort(m_maps.begin(), m_maps.end());
	for (auto& p : m_maps)
		m_searchRes.push_back(&p);
	Init(m_searchRes.size(), 10);
	SetVisible(false);
}

BGui::Button* GuiCustomMap::CreateButton(int index) {
	m_texts.push_back(AddText(("M_Opt_ModMenu_" + std::to_string(index)).c_str(), "", 0.44f, 0.23f + 0.06f * index, 0.3f, 0.05f));
	return AddLevelButton(("M_Opt_ModMenu_" + std::to_string(index)).c_str(), "", 0.23f + 0.06f * index, 0.4031f, [this, index]() {
		GuiList::Exit();
		SetParamString(m_mod->m_mapFile, m_searchRes[m_curpage * m_maxsize + index]->filepath.c_str());
		SetParamValue(m_mod->m_loadCustom, TRUE);
		int level = rand() % 10 + 2;
		m_mod->m_curLevel->SetElementValue(0, 0, &level);
		level--;
		SetParamValue(m_mod->m_levelRow, level);

		CKContext* ctx = m_mod->m_bml->GetCKContext();
		CKMessageManager* mm = ctx->GetMessageManager();
		CKMessageType loadLevel = mm->AddMessageType("Load Level");
		CKMessageType loadMenu = mm->AddMessageType("Menu_Load");

		mm->SendMessageSingle(loadLevel, ctx->GetCurrentLevel());
		mm->SendMessageSingle(loadMenu, ModLoader::m_instance->GetGroupByName("All_Sound"));
		ModLoader::m_instance->Get2dEntityByName("M_BlackScreen")->Show(CKHIDE);
		m_mod->m_exitStart->ActivateInput(0);
		m_mod->m_exitStart->Activate();
		});
}

std::string GuiCustomMap::GetButtonText(int index) {
	return "";
}

BGui::Gui* GuiCustomMap::CreateSubGui(int index) {
	return nullptr;
}

BGui::Gui* GuiCustomMap::GetParentGui() {
	return nullptr;
}

void GuiCustomMap::SetPage(int page) {
	GuiList::SetPage(page);
	int size = (std::min)(m_maxsize, m_size - page * m_maxsize);
	for (int i = 0; i < m_maxsize; i++)
		m_texts[i]->SetVisible(i < size);
	for (int i = 0; i < size; i++)
		m_texts[i]->SetText(m_searchRes[page * m_maxsize + i]->displayname.c_str());
	m_mod->m_bml->AddTimer(1u, [this, page]() { m_exit->SetVisible(page == 0); });
}

void GuiCustomMap::Exit() {
	GuiList::Exit();
	ModLoader::m_instance->GetCKContext()->GetCurrentScene()->Activate(
		ModLoader::m_instance->GetScriptByName("Menu_Main"),
		true);
}

GuiModCategory::GuiModCategory(GuiModMenu* parent, Config* config, std::string category) {
	for (Property* prop : config->GetCategory(category.c_str()).props) {
		Property* newprop = new Property(nullptr, category, prop->m_key);
		newprop->CopyValue(prop);
		m_data.push_back(newprop);
	}

	m_size = m_data.size();
	m_curpage = 0;

	m_parent = parent;
	m_config = config;
	m_category = category;

	AddTextLabel("M_Opt_Category_Title", category.c_str(), ExecuteBB::GAMEFONT_02, 0.35f, 0.1f, 0.3f, 0.1f);
	m_left = AddLeftButton("M_List_Left", 0.12f, 0.35f, [this]() { PreviousPage(); });
	m_right = AddRightButton("M_List_Right", 0.12f, 0.6138f, [this]() { NextPage(); });
	AddBackButton("M_Opt_Category_Back")->SetCallback([this]() { SaveAndExit(); });
	m_exit = AddBackButton("M_Opt_Category_Back");
	m_exit->SetCallback([this]() { Exit(); });

	Vx2DVector offset(0.0f, ModLoader::m_instance->GetRenderContext()->GetHeight() * 0.015f);

	float cnt = 0.25f, page = 0;
	std::vector<BGui::Element*> elements;
	for (Property* prop : m_data) {
		std::string name = prop->m_key;
		switch (prop->GetType()) {
			case IProperty::STRING: {
				BGui::Button* bg = AddSettingButton(name.c_str(), name.c_str(), cnt);
				bg->SetAlignment(ALIGN_TOP);
				bg->SetFont(ExecuteBB::GAMEFONT_03);
				bg->SetZOrder(15);
				bg->SetOffset(offset);
				elements.push_back(bg);
				BGui::Input* input = AddTextInput(name.c_str(), ExecuteBB::GAMEFONT_03, 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				input->SetText(prop->GetString());
				input->SetCallback([this, prop, input](CKDWORD) { prop->SetString(input->GetText()); });
				elements.push_back(input);
				BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				elements.push_back(panel);
				m_inputs.push_back({ input, nullptr });
				cnt += 0.12f;
				break;
			}
			case IProperty::INTEGER: {
				BGui::Button* bg = AddSettingButton(name.c_str(), name.c_str(), cnt);
				bg->SetAlignment(ALIGN_TOP);
				bg->SetFont(ExecuteBB::GAMEFONT_03);
				bg->SetZOrder(15);
				bg->SetOffset(offset);
				elements.push_back(bg);
				BGui::Input* input = AddTextInput(name.c_str(), ExecuteBB::GAMEFONT_03, 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				input->SetText(std::to_string(prop->GetInteger()).c_str());
				input->SetCallback([this, prop, input](CKDWORD) { prop->SetInteger(atoi(input->GetText())); });
				elements.push_back(input);
				BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				elements.push_back(panel);
				m_inputs.push_back({ input, nullptr });
				cnt += 0.12f;
				break;
			}
			case IProperty::FLOAT: {
				BGui::Button* bg = AddSettingButton(name.c_str(), name.c_str(), cnt);
				bg->SetAlignment(ALIGN_TOP);
				bg->SetFont(ExecuteBB::GAMEFONT_03);
				bg->SetZOrder(15);
				bg->SetOffset(offset);
				elements.push_back(bg);
				BGui::Input* input = AddTextInput(name.c_str(), ExecuteBB::GAMEFONT_03, 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				input->SetText(std::to_string(prop->GetFloat()).c_str());
				input->SetCallback([this, prop, input](CKDWORD) { prop->SetFloat((float) atof(input->GetText())); });
				elements.push_back(input);
				BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
				elements.push_back(panel);
				m_inputs.push_back({ input, nullptr });
				cnt += 0.12f;
				break;
			}
			case IProperty::KEY: {
				std::pair<BGui::Button*, BGui::KeyInput*> key = AddKeyButton(name.c_str(), name.c_str(), cnt);
				key.second->SetKey(prop->GetKey());
				key.second->SetCallback([this, prop](CKDWORD key) { prop->SetKey(CKKEYBOARD(key)); });
				elements.push_back(key.first);
				elements.push_back(key.second);
				m_inputs.push_back({ key.second, nullptr });
				cnt += 0.06f;
				break;
			}
			case IProperty::BOOLEAN: {
				BGui::Button* bg = AddSettingButton(name.c_str(), name.c_str(), cnt);
				bg->SetAlignment(ALIGN_TOP);
				bg->SetFont(ExecuteBB::GAMEFONT_03);
				bg->SetZOrder(15);
				bg->SetOffset(offset);
				elements.push_back(bg);
				std::pair<BGui::Button*, BGui::Button*> yesno = AddYesNoButton(name.c_str(), cnt + 0.043f, 0.4350f, 0.5200f,
					[this, prop](bool value) { prop->SetBoolean(value); });
				yesno.first->SetActive(prop->GetBoolean());
				yesno.second->SetActive(!prop->GetBoolean());
				elements.push_back(yesno.first);
				elements.push_back(yesno.second);
				m_inputs.push_back(yesno);
				cnt += 0.12f;
				break;
			}
		}

		if (cnt > 0.7f) {
			cnt = 0.25f;
			page++;
			m_elements.push_back(elements);
			elements.clear();
		}
	}

	if (cnt > 0.25f) {
		m_elements.push_back(elements);
	}

	m_maxpage = m_elements.size();

	SetVisible(false);
}

void GuiModCategory::SetVisible(bool visible) {
	Gui::SetVisible(visible);
	if (visible) {
		std::vector<Property*> &props = m_config->GetCategory(m_category.c_str()).props;
		for (size_t i = 0; i < props.size(); i++) {
			Property* prop = props[i];
			m_data[i]->CopyValue(prop);
			std::pair<BGui::Element*, BGui::Element*> input = m_inputs[i];
			switch (prop->GetType()) {
				case IProperty::STRING: reinterpret_cast<BGui::Input*>(input.first)->SetText(prop->GetString()); break;
				case IProperty::INTEGER: reinterpret_cast<BGui::Input*>(input.first)->SetText(std::to_string(prop->GetInteger()).c_str()); break;
				case IProperty::FLOAT: reinterpret_cast<BGui::Input*>(input.first)->SetText(std::to_string(prop->GetFloat()).c_str()); break;
				case IProperty::KEY: reinterpret_cast<BGui::KeyInput*>(input.first)->SetKey(prop->GetKey()); break;
				case IProperty::BOOLEAN: {
					reinterpret_cast<BGui::Button*>(input.first)->SetActive(prop->GetBoolean());
					reinterpret_cast<BGui::Button*>(input.second)->SetActive(!prop->GetBoolean());
					break;
				}
			}
		}

		SetPage(m_curpage);
	}
}

void GuiModCategory::SetPage(int page) {
	for (auto& p : m_elements)
		for (auto& e : p)
			e->SetVisible(false);

	for (auto& e : m_elements[page])
		e->SetVisible(true);

	m_curpage = page;
	m_left->SetVisible(page > 0);
	m_right->SetVisible(page < m_maxpage - 1);
	m_exit->SetVisible(false);
}

void GuiModCategory::SaveAndExit() {
	Config::Category& cate = m_config->GetCategory(m_category.c_str());
	for (Property* p : m_data)
		cate.GetProperty(p->m_key.c_str())->CopyValue(p);
	m_config->Save();
	Exit();
}

void GuiModCategory::Exit() {
	ModLoader::m_instance->m_bmlmod->ShowGui(m_parent);
}

void ScreenModeHook::OnScreenModeChanged() {
	CKCamera* cams[] = { ModLoader::m_instance->GetTargetCameraByName("Cam_MenuLevel"),
		ModLoader::m_instance->GetTargetCameraByName("InGameCam") };
	CKRenderContext* rc = ModLoader::m_instance->GetRenderContext();
	for (CKCamera* cam : cams) {
		if (cam) {
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			CKStateChunk* chunk = CKSaveObjectState(cam);

			ModLoader::m_instance->RestoreIC(cam);
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			ModLoader::m_instance->SetIC(cam);

			CKReadObjectState(cam, chunk);
		}
	}
}
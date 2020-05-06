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

using namespace ScriptHelper;

void BMLMod::OnLoadObject(CKSTRING filename, CKSTRING masterName, CK_CLASSID filterClass,
	BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
	XObjectArray* objArray, CKObject* masterObj) {
	if (!strcmp(filename, "3D Entities\\Menu.nmo")) {
		BGui::Gui::InitMaterials();

		m_cmdBar = new BGui::Gui();
		m_cmdBar->AddPanel("M_Cmd_Bg", VxColor(0, 0, 0, 110), 0.02f, 0.94f, 0.95f, 0.025f)->SetZOrder(100);
		m_cmdInput = m_cmdBar->AddTextInput("M_Cmd_Text", ExecuteBB::GAMEFONT_03, 0.02f, 0.94f, 0.95f, 0.025f, [this](CKDWORD key) { OnCmdEdit(key); });
		m_cmdInput->SetAlignment(ALIGN_LEFT);
		m_cmdInput->SetTextFlags(TEXT_SCREEN | TEXT_SHOWCARET);
		m_cmdInput->SetZOrder(110);
		m_cmdBar->SetCanBeBlocked(false);
		m_cmdBar->SetVisible(false);

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

		m_cheatBanner = new BGui::Gui();
		m_cheatBanner->AddTextLabel("M_Use_BML", "Ballance Mod Loader " BML_VERSION, ExecuteBB::GAMEFONT_01, 0, 0, 1, 0.03f);
		m_cheat = m_cheatBanner->AddTextLabel("M_Use_Cheat", "Cheat Mode Enabled", ExecuteBB::GAMEFONT_01, 0, 0.03f, 1, 0.03f);
		m_cheat->SetVisible(false);

		m_modOption = new GuiModOption();
		m_modOption->SetVisible(false);
	}

	if (!strcmp(filename, "3D Entities\\MenuLevel.nmo")) {
		if (m_unlockRes->GetBoolean()) {
			CKCamera* cam = static_cast<CKCamera*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Cam_MenuLevel", CKCID_TARGETCAMERA));
			CKRenderContext* rc = m_bml->GetRenderContext();
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			m_bml->GetCKContext()->GetCurrentScene()->SetObjectInitialValue(cam, CKSaveObjectState(cam));
		}
	}

	if (!strcmp(filename, "3D Entities\\Camera.nmo")) {
		if (m_unlockRes->GetBoolean()) {
			CKCamera* cam = static_cast<CKCamera*>(m_bml->GetCKContext()->GetObjectByNameAndClass("InGameCam", CKCID_TARGETCAMERA));
			CKRenderContext* rc = m_bml->GetRenderContext();
			cam->SetAspectRatio(rc->GetWidth(), rc->GetHeight());
			cam->SetFov(0.75f * rc->GetWidth() / rc->GetHeight());
			m_bml->GetCKContext()->GetCurrentScene()->SetObjectInitialValue(cam, CKSaveObjectState(cam));
		}

		m_camPos = static_cast<CK3dEntity*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Cam_Pos", CKCID_3DENTITY));
		m_camOrient = static_cast<CK3dEntity*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Cam_Orient", CKCID_3DENTITY));
		m_camOrientRef = static_cast<CK3dEntity*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Cam_OrientRef", CKCID_3DENTITY));
		m_camTarget = static_cast<CK3dEntity*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Cam_Target", CKCID_3DENTITY));
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
}

void BMLMod::OnEditScript_Base_DefaultLevel(CKBehavior* script) {
	if (m_unlockRes->GetBoolean()) {
		CKBehavior* sm = FindFirstBB(script, "Screen Modes", false);

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
			}, "Remove Row If", false);

		CKBehavior* it = FindPreviousBB(sm, rrs[0], "Iterator");
		CKBehavior* gc = FindNextBB(sm, rrs[3], "Get Cell");
		DeleteBB(sm, rrs[0]);
		DeleteBB(sm, rrs[3]);
		CreateLink(sm, it, gc, 0, 0);
	}
}

void BMLMod::OnEditScript_Base_EventHandler(CKBehavior* script) {
	CKBehavior* som = FindFirstBB(script, "Switch On Message", false, 2, 11, 11, 0);

	GetLogger()->Info("Insert message Start Menu Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 0, 0)), CreateBB(script, BML_ONSTARTMENU_GUID));

	GetLogger()->Info("Insert message Exit Game Hook");
	InsertBB(script, FindNextLink(script, FindNextBB(script, som, nullptr, 1, 0)), CreateBB(script, BML_ONEXITGAME_GUID));

	GetLogger()->Info("Insert message Load Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 2, 0)), CreateBB(script, BML_ONLOADLEVEL_GUID));

	GetLogger()->Info("Insert message Start Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 3, 0)), CreateBB(script, BML_ONSTARTLEVEL_GUID));

	GetLogger()->Info("Insert message Reset Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 4, 0)), CreateBB(script, BML_ONRESETLEVEL_GUID));

	GetLogger()->Info("Insert message Pause Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 5, 0)), CreateBB(script, BML_ONPAUSELEVEL_GUID));

	GetLogger()->Info("Insert message Unpause Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 6, 0)), CreateBB(script, BML_ONUNPAUSELEVEL_GUID));

	CKBehavior* bs = FindNextBB(script, FindFirstBB(script, "DeleteCollisionSurfaces"));

	GetLogger()->Info("Insert message Exit Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, bs, nullptr, 0, 0)), CreateBB(script, BML_ONEXITLEVEL_GUID));

	GetLogger()->Info("Insert message Next Level Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, bs, nullptr, 1, 0)), CreateBB(script, BML_ONNEXTLEVEL_GUID));

	GetLogger()->Info("Insert message Dead Hook");
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 9, 0)), CreateBB(script, BML_ONDEAD_GUID));

	CKBehavior* hs = FindFirstBB(script, "Highscore");
	hs->AddOutput("Out");
	FindBB(hs, [hs](CKBehavior* beh) {
		CreateLink(hs, beh, hs->GetOutput(0));
		return true;
		}, "Activate Script", false);
	GetLogger()->Info("Insert message End Level Hook");
	CreateLink(script, hs, CreateBB(script, BML_ONENDLEVEL_GUID));
}

void BMLMod::OnEditScript_Menu_MenuInit(CKBehavior* script) {
	m_bml->AddTimer(1u, [this]() {
		CKBehavior* script = static_cast<CKBehavior*>(m_bml->GetCKContext()->GetObjectByNameAndClass("Menu_Init", CKCID_BEHAVIOR));
		CKBehavior* fonts = FindFirstBB(script, "Fonts", false);
		CKBehavior* bbs[7] = { 0 };
		int cnt = 0;
		FindBB(fonts, [&bbs, &cnt](CKBehavior* beh) {
			bbs[cnt++] = beh;
			return true;
			}, "TT CreateFontEx", false);

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
	buttons[0] = static_cast<CK2dEntity*>(context->GetObjectByNameAndClass("M_Options_Title", CKCID_2DENTITY));
	for (int i = 1; i < 4; i++) {
		but_name[14] = '0' + i;
		buttons[i] = static_cast<CK2dEntity*>(context->GetObjectByNameAndClass(but_name, CKCID_2DENTITY));
	}

	buttons[5] = static_cast<CK2dEntity*>(context->GetObjectByNameAndClass("M_Options_But_Back", CKCID_2DENTITY));
	buttons[4] = static_cast<CK2dEntity*>(context->CopyObject(buttons[1]));
	buttons[4]->SetName("M_Options_But_4");
	for (int i = 0; i < 5; i++) {
		Vx2DVector pos;
		buttons[i]->GetPosition(pos, true);
		pos.y = 0.1f + 0.14f * i;
		buttons[i]->SetPosition(pos, true);
	}

	CKDataArray* array = static_cast<CKDataArray*>(context->GetObjectByNameAndClass("Menu_Options_ShowHide", CKCID_DATAARRAY));
	array->InsertRow(3);
	array->SetElementObject(3, 0, buttons[4]);
	BOOL show = 1;
	array->SetElementValue(3, 1, &show, sizeof(show));
	context->GetCurrentScene()->SetObjectInitialValue(array, CKSaveObjectState(array));

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

	CKParameterLocal* pin = CreateLocalParameter(graph, "Pin 5", CKPGUID_INT);
	int value = 4;
	pin->SetValue(&value, sizeof(value));
	up_sop->CreateInputParameter("Pin 5", CKPGUID_INT)->SetDirectSource(pin); up_sop->AddOutput("Out 5");
	down_sop->CreateInputParameter("Pin 5", CKPGUID_INT)->SetDirectSource(pin); down_sop->AddOutput("Out 5");
	up_ps->CreateInputParameter("pIn 4", CKPGUID_INT)->SetDirectSource(pin); up_ps->AddInput("In 4");
	down_ps->CreateInputParameter("pIn 4", CKPGUID_INT)->SetDirectSource(pin); down_ps->AddInput("In 4");

	CKBehavior* text2d = CreateBB(graph, VT_TEXT2D, true);
	CKBehavior* pushbutton = CreateBB(graph, TT_PUSHBUTTON2, true);
	CKBehavior* text2dref = FindFirstBB(graph, "2D Text");
	CKBehavior* nop = FindFirstBB(graph, "Nop");
	CKParameterLocal* entity2d = CreateLocalParameter(graph, "Button", CKPGUID_2DENTITY);
	CK_ID buttonid = CKOBJID(buttons[4]);
	entity2d->SetValue(&buttonid, sizeof(buttonid));
	CKParameterLocal* buttonname = CreateLocalParameter(graph, "Text", CKPGUID_STRING);
	buttonname->SetStringValue("Mods");
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
		}, "Secure Key", false);

	GetLogger()->Info("Mods Button inserted");
}

void BMLMod::OnEditScript_Gameplay_Ingame(CKBehavior* script) {
	CKBehavior* ballNav = FindFirstBB(script, "Ball Navigation", false);
	CKBehavior* nop[2] = { 0 };
	FindBB(ballNav, [&nop, ballNav](CKBehavior* beh) {
		if (nop[0]) nop[1] = beh;
		else nop[0] = beh;
		return !nop[1];
		}, "Nop", false);
	CKBehavior* keyevent[2] = { CreateBB(ballNav, VT_KEYEVENT), CreateBB(ballNav, VT_KEYEVENT) };
	m_ballForce[0] = CreateLocalParameter(ballNav, "Up", CKPGUID_KEY);
	m_ballForce[1] = CreateLocalParameter(ballNav, "Down", CKPGUID_KEY);
	CKBehavior* phyforce[2] = { CreateBB(ballNav, TT_SETPHYSICSFORCE, true), CreateBB(ballNav, TT_SETPHYSICSFORCE, true) };
	CKBehavior* op = FindFirstBB(ballNav, "Op", false);
	CKParameter* mass = op->GetInputParameter(0)->GetDirectSource();
	CKBehavior* spf = FindFirstBB(ballNav, "SetPhysicsForce", false);
	CKParameter* dir[2] = { CreateLocalParameter(ballNav, "Up", CKPGUID_VECTOR), CreateLocalParameter(ballNav, "Down", CKPGUID_VECTOR) };
	SetParamValue(dir[0], VxVector(0, 1, 0));
	SetParamValue(dir[1], VxVector(0, -1, 0));
	CKBehavior* wake = FindFirstBB(ballNav, "Physics WakeUp", false);

	for (int i = 0; i < 2; i++) {
		SetParamValue(m_ballForce[i], CKKEYBOARD(0));
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

	GetConfig()->SetCategoryComment("Debug", "Debug Utilities");
	m_ballCheat[0] = GetConfig()->GetProperty("Debug", "BallUp");
	m_ballCheat[0]->SetComment("Apply an upward force to the ball");
	m_ballCheat[0]->SetDefaultKey(CKKEY_F1);

	m_ballCheat[1] = GetConfig()->GetProperty("Debug", "BallDown");
	m_ballCheat[1]->SetComment("Apply a downward force to the ball");
	m_ballCheat[1]->SetDefaultKey(CKKEY_F2);

	m_suicide = GetConfig()->GetProperty("Debug", "Suicide");
	m_suicide->SetComment("Suicide");
	m_suicide->SetDefaultKey(CKKEY_R);

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

	m_skipSpeed = m_skipAnim->GetBoolean();
	if (m_skipSpeed)
		GetLogger()->Info("Speed up to skip Loading Animation");

	m_bml->RegisterCommand(new CommandBML());
	m_bml->RegisterCommand(new CommandHelp());
	m_bml->RegisterCommand(new CommandCheat());
	m_bml->RegisterCommand(new CommandClear());
	m_bml->RegisterCommand(new CommandScore());
	m_bml->RegisterCommand(new CommandSpeed());
	m_bml->RegisterCommand(new CommandKill());
}

void BMLMod::OnProcess() {
	if (m_skipSpeed)
		m_bml->GetTimeManager()->SetTimeScaleFactor(100.0f);

	InputHook* im = m_bml->GetInputManager();
	if (im->IsKeyPressed(m_fullscreenKey->GetKey())) {
		CKRenderContext* rc = m_bml->GetRenderContext();
		if (rc->IsFullScreen())
			rc->StopFullScreen();
		else rc->GoFullScreen(rc->GetWidth(), rc->GetHeight(), -1, rc->GetDriverIndex());
	}

	if (im->IsKeyPressed(m_suicide->GetKey())) {
		ModLoader::m_instance->ExecuteCommand("kill");
	}

	if (m_cmdBar) {
		if (!m_cmdTyping && im->oIsKeyPressed(CKKEY_SLASH)) {
			m_cmdTyping = true;
			InputHook::SetBlock(true);
			m_cmdBar->SetVisible(true);
			m_historyPos = m_cmdHistory.size();
		}

		m_msgLog->Process();
		m_cheatBanner->Process();
		if (m_currentGui)
			m_currentGui->Process();

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

	if (m_camOn->GetBoolean()) {
		if (im->IsKeyPressed(m_cam45->GetKey())) {
			m_camOrientRef->Rotate(&VxVector(0, 1, 0), PI / 4, m_camOrientRef);
			m_camOrient->SetQuaternion(&VxQuaternion(), m_camOrientRef);
		}
		if (im->IsKeyDown(m_camRot[0]->GetKey())) {
			m_camOrientRef->Rotate(&VxVector(0, 1, 0), -0.01f, m_camOrientRef);
			m_camOrient->SetQuaternion(&VxQuaternion(), m_camOrientRef);
		}
		if (im->IsKeyDown(m_camRot[1]->GetKey())) {
			m_camOrientRef->Rotate(&VxVector(0, 1, 0), 0.01f, m_camOrientRef);
			m_camOrient->SetQuaternion(&VxQuaternion(), m_camOrientRef);
		}
		if (im->IsKeyDown(m_camY[0]->GetKey()))
			m_camPos->Translate(&VxVector(0, 0.1f, 0), m_camOrientRef);
		if (im->IsKeyDown(m_camY[1]->GetKey()))
			m_camPos->Translate(&VxVector(0, -0.1f, 0), m_camOrientRef);
		if (im->IsKeyDown(m_camZ[0]->GetKey())) {
			VxVector position;
			m_camPos->GetPosition(&position, m_camOrientRef);
			position.z = (std::min)(position.z + 0.1f, -0.1f);
			m_camPos->SetPosition(&position, m_camOrientRef);
		}
		if (im->IsKeyDown(m_camZ[1]->GetKey()))
			m_camPos->Translate(&VxVector(0, 0, -0.1f), m_camOrientRef);
		if (im->IsKeyDown(m_camReset->GetKey())) {
			VxQuaternion rotation;
			m_camOrientRef->GetQuaternion(&rotation, m_camTarget);
			if (rotation.angle > 0.9f)
				rotation = VxQuaternion();
			else {
				rotation = rotation + VxQuaternion();
				rotation *= 0.5f;
			}
			m_camOrientRef->SetQuaternion(&rotation, m_camTarget);
			m_camOrient->SetQuaternion(&VxQuaternion(), m_camOrientRef);
			m_camPos->SetPosition(&VxVector(0, 35, -22), m_camOrient);
		}
	}
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
}

void BMLMod::OnStartMenu() {
	if (m_skipSpeed) {
		m_skipSpeed = false;
		m_bml->GetTimeManager()->SetTimeScaleFactor(1.0f);
		GetLogger()->Info("Loading Animation ended, stop speeding up");

		// Fix Ball Pieces
		CKContext* context = m_bml->GetCKContext();
		CKScene* scene = context->GetCurrentScene();
		for (CKSTRING group_name : { "Ball_Paper_Pieces", "Ball_Stone_Pieces", "Ball_Wood_Pieces" }) {
			CKGroup* group = static_cast<CKGroup*>(context->GetObjectByNameAndClass(group_name, CKCID_GROUP));
			int cnt = group->GetObjectCount();
			for (int i = 0; i < cnt; i++) {
				CKBeObject* obj = group->GetObject(i);
				CKStateChunk* chunk = scene->GetObjectInitialValue(obj);
				if (chunk) CKReadObjectState(obj, chunk);
			}
		}
	}
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
	m_currentGui = gui;
	if (gui)
		gui->SetVisible(true);
}

void BMLMod::ShowGuiList(GuiList* gui) {
	ShowGui(gui);
	gui->SetPage(0);
}

void BMLMod::CloseCurrentGui() {
	m_currentGui->SetVisible(false);
	m_currentGui = nullptr;
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
		button->SetCallback([this, i]() {
			BGui::Gui* gui = m_guiList[m_maxsize * m_curpage + i];
			ModLoader::m_instance->m_bmlmod->ShowGui(gui);
			});
		m_buttons.push_back(button);
	}
}

void GuiList::SetPage(int page) {
	ModLoader* bml = ModLoader::m_instance;
	int size = (std::min)((UINT)m_maxsize, m_guiList.size() - page * m_maxsize);
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
	if (visible) SetPage(0);
}

GuiModOption::GuiModOption() {
	Init(ModLoader::m_instance->m_mods.size(), 4);

	AddTextLabel("M_Opt_Mods_Title", "Mod List", ExecuteBB::GAMEFONT_02, 0.35f, 0.1f, 0.3f, 0.1f);
}

BGui::Button* GuiModOption::CreateButton(int index) {
	return AddSettingButton(("M_Opt_Mods_" + std::to_string(index)).c_str(), "", 0.25f + 0.15f * index);
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
		static_cast<CKBehavior*>(ModLoader::m_instance->GetCKContext()->GetObjectByNameAndClass("Menu_Options", CKCID_BEHAVIOR)),
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
			m_categories.push_back(cate.first);
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

GuiModCategory::GuiModCategory(GuiModMenu* parent, Config* config, std::string category) {
	m_data = config->m_data[category].second;
	m_size = m_data.size();
	m_curpage = 0;

	m_parent = parent;
	m_config = config;
	m_category = category;

	AddTextLabel("M_Opt_Category_Title", category.c_str(), ExecuteBB::GAMEFONT_02, 0.35f, 0.1f, 0.3f, 0.1f);
	m_left = AddLeftButton("M_List_Left", 0.12f, 0.36f, [this]() { PreviousPage(); });
	m_right = AddRightButton("M_List_Right", 0.12f, 0.6038f, [this]() { NextPage(); });
	AddBackButton("M_Opt_Category_Back")->SetCallback([this]() { SaveAndExit(); });
	m_exit = AddBackButton("M_Opt_Category_Back");
	m_exit->SetCallback([this]() { Exit(); });

	Vx2DVector offset(0.0f, ModLoader::m_instance->GetRenderContext()->GetHeight() * 0.015f);

	float cnt = 0.25f, page = 0;
	std::vector<BGui::Element*> elements;
	for (auto& p : m_data) {
		std::string name = p.first;
		Property& prop = p.second;
		switch (prop.GetType()) {
		case IProperty::STRING: {
			BGui::Button* bg = AddSettingButton(name.c_str(), name.c_str(), cnt);
			bg->SetAlignment(ALIGN_TOP);
			bg->SetFont(ExecuteBB::GAMEFONT_03);
			bg->SetZOrder(15);
			bg->SetOffset(offset);
			elements.push_back(bg);
			BGui::Input* input = AddTextInput(name.c_str(), ExecuteBB::GAMEFONT_03, 0.43f, cnt + 0.05f, 0.18f, 0.025f);
			input->SetText(prop.GetString());
			input->SetCallback([this, name, input](CKDWORD) { m_data[name].SetString(input->GetText()); });
			elements.push_back(input);
			BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
			elements.push_back(panel);
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
			input->SetText(std::to_string(prop.GetInteger()).c_str());
			input->SetCallback([this, name, input](CKDWORD) { m_data[name].SetInteger(atoi(input->GetText())); });
			elements.push_back(input);
			BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
			elements.push_back(panel);
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
			input->SetText(std::to_string(prop.GetFloat()).c_str());
			input->SetCallback([this, name, input](CKDWORD) { m_data[name].SetFloat((float) atof(input->GetText())); });
			elements.push_back(input);
			BGui::Panel* panel = AddPanel(name.c_str(), VxColor(0, 0, 0, 110), 0.43f, cnt + 0.05f, 0.18f, 0.025f);
			elements.push_back(panel);
			cnt += 0.12f;
			break;
		}
		case IProperty::KEY: {
			std::pair<BGui::Button*, BGui::KeyInput*> key = AddKeyButton(name.c_str(), name.c_str(), cnt);
			key.second->SetKey(prop.GetKey());
			key.second->SetCallback([this, name](CKDWORD key) { m_data[name].SetKey(CKKEYBOARD(key)); });
			elements.push_back(key.first);
			elements.push_back(key.second);
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
				[this, name](bool value) { m_data[name].SetBoolean(value); });
			yesno.first->SetActive(prop.GetBoolean());
			yesno.second->SetActive(!prop.GetBoolean());
			elements.push_back(yesno.first);
			elements.push_back(yesno.second);
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

	if (cnt > 0.0f) {
		m_elements.push_back(elements);
	}

	m_maxpage = m_elements.size();

	SetVisible(false);
}

void GuiModCategory::SetVisible(bool visible) {
	Gui::SetVisible(visible);
	if (visible) SetPage(0);
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
	for (auto& p : m_config->m_data[m_category].second)
		p.second.CopyValue(m_data[p.first]);
	m_config->Save();
	Exit();
}

void GuiModCategory::Exit() {
	ModLoader::m_instance->m_bmlmod->ShowGui(m_parent);
}
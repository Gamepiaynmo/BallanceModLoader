#include "BMLMod.h"
#include "ScriptHelper.h"
#include "RegisterBB.h"

using namespace ScriptHelper;

void BMLMod::OnLoadScript(CKSTRING filename, CKBehavior* script) {
	if (!strcmp(script->GetName(), "Event_handler"))
		OnEditScript_Base_EventHandler(script);

	if (!strcmp(script->GetName(), "Menu_Main"))
		OnEidtScript_Menu_MainMenu(script);
}

void BMLMod::OnEditScript_Base_EventHandler(CKBehavior* script) {
	CKBehavior* som = FindFirstBB(script, "Switch On Message", false, 2, 11, 11, 0);

	// Add Start Menu Hook
	CreateLink(script, FindEndOfChain(script, FindNextBB(script, som, nullptr, 0, 0)), CreateBB(script, BML_ONSTARTMENU_GUID));
}

void BMLMod::OnEidtScript_Menu_MainMenu(CKBehavior* script) {
	char but_name[] = "M_Main_But_X";
	CK2dEntity* buttons[6] = { 0 };
	CKContext* context = m_bml->GetCKContext();
	for (int i = 0; i < 5; i++) {
		but_name[11] = '1' + i;
		buttons[i] = static_cast<CK2dEntity*>(context->GetObjectByNameAndClass(but_name, CKCID_2DENTITY));
	}

	buttons[5] = buttons[4];
	buttons[4] = static_cast<CK2dEntity*>(context->CopyObject(buttons[0]));
	buttons[4]->SetName("M_Main_But_Mods");
	for (int i = 0; i < 6; i++) {
		Vx2DVector pos;
		buttons[i]->GetPosition(pos, true);
		pos.y = 0.1f + 0.14f * i;
		buttons[i]->SetPosition(pos, true);
	}

	CKDataArray* array = static_cast<CKDataArray*>(context->GetObjectByNameAndClass("Menu_Main_ShowHide", CKCID_DATAARRAY));
	array->InsertRow(4);
	array->SetElementObject(4, 0, buttons[4]);
	BOOL show = 1;
	array->SetElementValue(4, 1, &show, sizeof(show));

	CKBehavior* graph = FindFirstBB(script, "Main Menu");
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

	CKParameterLocal* pin = CreateLocalParameter(graph, "Pin 6", CKPGUID_INT);
	int value = 5;
	pin->SetValue(&value, sizeof(value));
	up_sop->CreateInputParameter("Pin 6", CKPGUID_INT)->SetDirectSource(pin); up_sop->AddOutput("Out 6");
	down_sop->CreateInputParameter("Pin 6", CKPGUID_INT)->SetDirectSource(pin); down_sop->AddOutput("Out 6");
	up_ps->CreateInputParameter("pIn 5", CKPGUID_INT)->SetDirectSource(pin); up_ps->AddInput("In 5");
	down_ps->CreateInputParameter("pIn 5", CKPGUID_INT)->SetDirectSource(pin); down_ps->AddInput("In 5");

	CKBehavior* text2d = CreateBB(graph, CKGUID(0x55b29fe, 0x662d5ca0), true);
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

	FindNextLink(graph, up_sop, nullptr, 5, 0)->SetInBehaviorIO(up_sop->GetOutput(6));
	CreateLink(graph, up_sop, text2d, 5, 0);
	CreateLink(graph, text2d, nop, 0, 0);
	CreateLink(graph, text2d, pushbutton, 0, 0);
	FindPreviousLink(graph, up_ps, nullptr, 1, 4)->SetOutBehaviorIO(up_ps->GetInput(5));
	FindPreviousLink(graph, down_ps, nullptr, 2, 4)->SetOutBehaviorIO(down_ps->GetInput(5));
	CreateLink(graph, pushbutton, up_ps, 1, 4);
	CreateLink(graph, pushbutton, down_ps, 2, 4);
	graph->AddOutput("Button 6 Pressed");
	CreateLink(graph, down_sop, graph->GetOutput(5), 6);
	FindNextLink(script, graph, nullptr, 4, 0)->SetInBehaviorIO(graph->GetOutput(5));

	CKBehavior* modsmenu = CreateBB(script, BML_MODSMENU_GUID);
	CKBehavior* exit = FindFirstBB(script, "Exit", false, 1, 0);
	CreateLink(script, graph, modsmenu, 4, 0);
	CreateLink(script, modsmenu, exit, 0, 0);
}

void BMLMod::OnLoad() {
	IProperty* property;

	GetConfig()->SetCategoryComment("test_cate", "Test Cate 1");
	property = GetConfig()->GetProperty("test_cate", "str_key");
	property->SetComment("Test String");
	property->SetDefaultString("Test");

	property = GetConfig()->GetProperty("test_cate", "bool_key");
	property->SetComment("Test Boolean");
	property->SetDefaultBoolean(false);

	GetConfig()->SetCategoryComment("cate2", "Test Cate 2");
	property = GetConfig()->GetProperty("cate2", "float_key");
	property->SetComment("Floatttttttttt");
	property->SetDefaultFloat(100);

	property = GetConfig()->GetProperty("cate2", "int_key");
	property->SetComment("Integerrrrrrrrrr");
	property->SetDefaultInteger(200);
}

void BMLMod::OnProcess() {
	m_bml->GetTimeManager()->SetTimeScaleFactor(10.0f);
}
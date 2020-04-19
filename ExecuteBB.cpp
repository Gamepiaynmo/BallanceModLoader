#include "ExecuteBB.h"
#include "ScriptHelper.h"
#include "RegisterBB.h"
#include "ModLoader.h"

using namespace ScriptHelper;

namespace ExecuteBB {
	int GameFonts[8] = { 0 };
	void InitFont(FontType type, int fontIndex) {
		GameFonts[type] = fontIndex;
	}
	int GetFont(FontType type) {
		return GameFonts[type];
	}

	CKBehavior* ownerScript;
	template<typename T>
	CKParameter* CreateParamValue(CKGUID guid, CKSTRING name, T value) {
		CKParameter* param = CreateLocalParameter(ownerScript, name, guid);
		param->SetValue(&value, sizeof(T));
		return param;
	}

	CKParameter* CreateParamObject(CKGUID guid, CKSTRING name, CKObject* value) {
		return CreateParamValue<CK_ID>(guid, name, CKOBJID(value));
	}

	CKParameter* CreateParamString(CKSTRING name, CKSTRING value) {
		CKParameter* param = CreateLocalParameter(ownerScript, name, CKPGUID_STRING);
		param->SetStringValue(value);
		return param;
	}

	CKBehavior* bb2DText;
	CKBehavior* Create2DText(CK2dEntity* target, FontType font, CKSTRING text, int align, VxRect margin, Vx2DVector offset,
		Vx2DVector pindent, CKMaterial* bgmat, int caretsize, CKMaterial* caretmat, int flags) {
		CKBehavior* beh = CreateBB(ownerScript, VT_TEXT2D, true);
		beh->GetTargetParameter()->SetDirectSource(CreateParamObject(CKPGUID_2DENTITY, "Target", target));
		beh->GetInputParameter(0)->SetDirectSource(CreateParamValue(CKPGUID_FONT, "Font", GetFont(font)));
		beh->GetInputParameter(1)->SetDirectSource(CreateParamString("Text", text));
		beh->GetInputParameter(2)->SetDirectSource(CreateParamValue(CKPGUID_ALIGNMENT, "Alignment", align));
		beh->GetInputParameter(3)->SetDirectSource(CreateParamValue(CKPGUID_RECT, "Margins", margin));
		beh->GetInputParameter(4)->SetDirectSource(CreateParamValue(CKPGUID_2DVECTOR, "Offset", offset));
		beh->GetInputParameter(5)->SetDirectSource(CreateParamValue(CKPGUID_2DVECTOR, "Paragraph Indentation", pindent));
		beh->GetInputParameter(6)->SetDirectSource(CreateParamObject(CKPGUID_MATERIAL, "Background Material", bgmat));
		beh->GetInputParameter(7)->SetDirectSource(CreateParamValue(CKPGUID_INT, "Caret Size", caretsize));
		beh->GetInputParameter(8)->SetDirectSource(CreateParamObject(CKPGUID_MATERIAL, "Caret Material", caretmat));
		SetParamValue(beh->GetLocalParameter(0), flags);
		return beh;
	}
	void Call2DText(CK2dEntity* target, FontType font, CKSTRING text, int align, VxRect margin, Vx2DVector offset,
		Vx2DVector pindent, CKMaterial* bgmat, int caretsize, CKMaterial* caretmat, int flags) {
		SetParamObject(bb2DText->GetTargetParameter()->GetDirectSource(), target);
		SetParamValue(bb2DText->GetInputParameter(0)->GetDirectSource(), GetFont(font));
		SetParamString(bb2DText->GetInputParameter(1)->GetDirectSource(), text);
		SetParamValue(bb2DText->GetInputParameter(2)->GetDirectSource(), align);
		SetParamValue(bb2DText->GetInputParameter(3)->GetDirectSource(), margin);
		SetParamValue(bb2DText->GetInputParameter(4)->GetDirectSource(), offset);
		SetParamValue(bb2DText->GetInputParameter(5)->GetDirectSource(), pindent);
		SetParamObject(bb2DText->GetInputParameter(6)->GetDirectSource(), bgmat);
		SetParamValue(bb2DText->GetInputParameter(7)->GetDirectSource(), caretsize);
		SetParamObject(bb2DText->GetInputParameter(8)->GetDirectSource(), caretmat);
		SetParamValue(bb2DText->GetLocalParameter(0), flags);
		bb2DText->ActivateInput(0);
		bb2DText->Execute(ModLoader::m_instance->GetTimeManager()->GetLastDeltaTime());
	}

	void Init(CKContext* context) {
		for (int i = 0; i < 8; i++)
			GameFonts[i] = i;
		ownerScript = static_cast<CKBehavior*>(context->CreateObject(CKCID_BEHAVIOR, "Owner Script"));
	}
}
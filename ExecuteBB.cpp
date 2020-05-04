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
	FontType GetFontType(int font) {
		for (int i = 0; i < 8; i++)
			if (GameFonts[i] == font)
				return static_cast<FontType>(i);
		return NOFONT;
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
		Vx2DVector pindent, CKMaterial* bgmat, float caretsize, CKMaterial* caretmat, int flags) {
		CKBehavior* beh = CreateBB(ownerScript, VT_TEXT2D, true);
		beh->GetTargetParameter()->SetDirectSource(CreateParamObject(CKPGUID_2DENTITY, "Target", target));
		beh->GetInputParameter(0)->SetDirectSource(CreateParamValue(CKPGUID_FONT, "Font", GetFont(font)));
		beh->GetInputParameter(1)->SetDirectSource(CreateParamString("Text", text));
		beh->GetInputParameter(2)->SetDirectSource(CreateParamValue(CKPGUID_ALIGNMENT, "Alignment", align));
		beh->GetInputParameter(3)->SetDirectSource(CreateParamValue(CKPGUID_RECT, "Margins", margin));
		beh->GetInputParameter(4)->SetDirectSource(CreateParamValue(CKPGUID_2DVECTOR, "Offset", offset));
		beh->GetInputParameter(5)->SetDirectSource(CreateParamValue(CKPGUID_2DVECTOR, "Paragraph Indentation", pindent));
		beh->GetInputParameter(6)->SetDirectSource(CreateParamObject(CKPGUID_MATERIAL, "Background Material", bgmat));
		beh->GetInputParameter(7)->SetDirectSource(CreateParamValue(CKPGUID_PERCENTAGE, "Caret Size", caretsize));
		beh->GetInputParameter(8)->SetDirectSource(CreateParamObject(CKPGUID_MATERIAL, "Caret Material", caretmat));
		SetParamValue(beh->GetLocalParameter(0), flags);
		return beh;
	}

	void Init(CKContext* context) {
		for (int i = 0; i < 8; i++)
			GameFonts[i] = i;
		ownerScript = static_cast<CKBehavior*>(context->CreateObject(CKCID_BEHAVIOR, "Owner Script"));
	}
}
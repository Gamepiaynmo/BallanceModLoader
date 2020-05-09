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

	CKBehavior* bbPhysConv, * bbPhysBall, * bbPhysConc;
	CKBehavior* CreatePhysicalize(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter) {
		CKBehavior* beh = CreateBB(ownerScript, TT_PHYSICALIZE, true);
		beh->GetTargetParameter()->SetDirectSource(CreateParamObject(CKPGUID_3DENTITY, "Target", target));
		beh->GetInputParameter(0)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Fixed", fixed));
		beh->GetInputParameter(1)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Friction", friction));
		beh->GetInputParameter(2)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Elasticity", elasticity));
		beh->GetInputParameter(3)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Mass", mass));
		beh->GetInputParameter(4)->SetDirectSource(CreateParamString("Collision Group", collGroup));
		beh->GetInputParameter(5)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Start Frozen", startFrozen));
		beh->GetInputParameter(6)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Enable Collision", enableColl));
		beh->GetInputParameter(7)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Calculate Mass Center", calcMassCenter));
		beh->GetInputParameter(8)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Linear Speed Damp", linearDamp));
		beh->GetInputParameter(9)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Rot Speed Damp", rotDamp));
		beh->GetInputParameter(10)->SetDirectSource(CreateParamString("Collision Surface", collSurface));
		SetParamValue(beh->GetLocalParameter(3), massCenter);
		return beh;
	}

	CKBehavior* CreatePhysicalizeConvex(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, CKMesh* mesh) {
		CKBehavior* beh = CreatePhysicalize(target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		beh->GetInputParameter(11)->SetDirectSource(CreateParamObject(CKPGUID_MESH, "Mesh", mesh));
		return beh;
	}

	CKBehavior* CreatePhysicalizeBall(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, VxVector ballCenter, float ballRadius) {
		CKBehavior* beh = CreatePhysicalize(target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		SetParamValue(beh->GetLocalParameter(0), 0);
		SetParamValue(beh->GetLocalParameter(1), 1);
		beh->CallCallbackFunction(CKM_BEHAVIORSETTINGSEDITED);
		beh->GetInputParameter(11)->SetDirectSource(CreateParamValue(CKPGUID_VECTOR, "Ball Position", ballCenter));
		beh->GetInputParameter(12)->SetDirectSource(CreateParamValue(CKPGUID_FLOAT, "Ball Radius", ballRadius));
		return beh;
	}

	CKBehavior* CreatePhysicalizeConcave(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, CKMesh* mesh) {
		CKBehavior* beh = CreatePhysicalize(target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		SetParamValue(beh->GetLocalParameter(0), 0);
		SetParamValue(beh->GetLocalParameter(2), 1);
		beh->CallCallbackFunction(CKM_BEHAVIORSETTINGSEDITED);
		beh->GetInputParameter(11)->SetDirectSource(CreateParamObject(CKPGUID_MESH, "Mesh", mesh));
		return beh;
	}

	void PhysicalizeParam(CKBehavior* beh, CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter) {
		SetParamObject(beh->GetTargetParameter()->GetDirectSource(), target);
		SetParamValue(beh->GetInputParameter(0)->GetDirectSource(), fixed);
		SetParamValue(beh->GetInputParameter(1)->GetDirectSource(), friction);
		SetParamValue(beh->GetInputParameter(2)->GetDirectSource(), elasticity);
		SetParamValue(beh->GetInputParameter(3)->GetDirectSource(), mass);
		SetParamString(beh->GetInputParameter(4)->GetDirectSource(), collGroup);
		SetParamValue(beh->GetInputParameter(5)->GetDirectSource(), startFrozen);
		SetParamValue(beh->GetInputParameter(6)->GetDirectSource(), enableColl);
		SetParamValue(beh->GetInputParameter(7)->GetDirectSource(), calcMassCenter);
		SetParamValue(beh->GetInputParameter(8)->GetDirectSource(), linearDamp);
		SetParamValue(beh->GetInputParameter(9)->GetDirectSource(), rotDamp);
		SetParamString(beh->GetInputParameter(10)->GetDirectSource(), collSurface);
		SetParamValue(beh->GetLocalParameter(3), massCenter);
	}

	void PhysicalizeConvex(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, CKMesh* mesh) {
		PhysicalizeParam(bbPhysConv, target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		SetParamObject(bbPhysConv->GetInputParameter(11)->GetDirectSource(), mesh);
		bbPhysConv->ActivateInput(0);
		bbPhysConv->Execute(0);
	}

	void PhysicalizeBall(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, VxVector ballCenter, float ballRadius) {
		PhysicalizeParam(bbPhysBall, target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		SetParamValue(bbPhysBall->GetInputParameter(11)->GetDirectSource(), ballCenter);
		SetParamValue(bbPhysBall->GetInputParameter(12)->GetDirectSource(), ballRadius);
		bbPhysBall->ActivateInput(0);
		bbPhysBall->Execute(0);
	}

	void PhysicalizeConcave(CK3dEntity* target, CKBOOL fixed, float friction, float elasticity, float mass,
		CKSTRING collGroup, CKBOOL startFrozen, CKBOOL enableColl, CKBOOL calcMassCenter, float linearDamp,
		float rotDamp, CKSTRING collSurface, VxVector massCenter, CKMesh* mesh) {
		PhysicalizeParam(bbPhysConc, target, fixed, friction, elasticity, mass, collGroup, startFrozen,
			enableColl, calcMassCenter, linearDamp, rotDamp, collSurface, massCenter);
		SetParamObject(bbPhysConc->GetInputParameter(11)->GetDirectSource(), mesh);
		bbPhysConc->ActivateInput(0);
		bbPhysConc->Execute(0);
	}

	void Unphysicalize(CK3dEntity* target) {
		SetParamObject(bbPhysConv->GetTargetParameter()->GetDirectSource(), target);
		bbPhysConv->ActivateInput(1);
		bbPhysConv->Execute(0);
	}

	CKBehavior* bbObjLoad;
	CKBehavior* CreateObjectLoad(CKSTRING file, CKSTRING mastername, CK_CLASSID filter, CKBOOL addToScene,
		CKBOOL reuseMesh, CKBOOL reuseMtl, CKBOOL dynamic) {
		CKBehavior* beh = CreateBB(ownerScript, VT_OBJECTLOAD);
		beh->GetInputParameter(0)->SetDirectSource(CreateParamString("File", file));
		beh->GetInputParameter(1)->SetDirectSource(CreateParamString("Master Name", mastername));
		beh->GetInputParameter(2)->SetDirectSource(CreateParamValue(CKPGUID_CLASSID, "Filter", filter));
		beh->GetInputParameter(3)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Add to Scene", addToScene));
		beh->GetInputParameter(4)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Reuse Mesh", reuseMesh));
		beh->GetInputParameter(5)->SetDirectSource(CreateParamValue(CKPGUID_BOOL, "Reuse Material", reuseMtl));
		SetParamValue(beh->GetLocalParameter(0), dynamic);
		return beh;
	}

	std::pair<XObjectArray*, CKObject*> ObjectLoad(CKSTRING file, CKSTRING mastername, CK_CLASSID filter, CKBOOL addToScene,
		CKBOOL reuseMesh, CKBOOL reuseMtl, CKBOOL dynamic, bool rename) {
		SetParamString(bbObjLoad->GetInputParameter(0)->GetDirectSource(), file);
		SetParamString(bbObjLoad->GetInputParameter(1)->GetDirectSource(), mastername);
		SetParamValue(bbObjLoad->GetInputParameter(2)->GetDirectSource(), filter);
		SetParamValue(bbObjLoad->GetInputParameter(3)->GetDirectSource(), addToScene);
		SetParamValue(bbObjLoad->GetInputParameter(4)->GetDirectSource(), reuseMesh);
		SetParamValue(bbObjLoad->GetInputParameter(5)->GetDirectSource(), reuseMtl);
		SetParamValue(bbObjLoad->GetLocalParameter(0), dynamic);
		bbObjLoad->ActivateInput(0);
		bbObjLoad->Execute(0);

		XObjectArray* array = *static_cast<XObjectArray**>(bbObjLoad->GetOutputParameterWriteDataPtr(0));
		if (rename) {
			static int count = 0;
			count++;
			for (CK_ID* id = array->Begin(); id != array->End(); id++) {
				CKObject* obj = bbObjLoad->GetCKContext()->GetObject(*id);
				if (CKIsChildClassOf(obj, CKCID_BEOBJECT)) {
					auto name = obj->GetName();
					obj->SetName((obj->GetName() + std::string("_BMLLoad_") + std::to_string(count)).c_str());
				}
			}
		}

		return { array, bbObjLoad->GetOutputParameterObject(1) };
	}

	void Init(CKContext* context) {
		for (int i = 0; i < 8; i++)
			GameFonts[i] = i;
		ownerScript = static_cast<CKBehavior*>(context->GetObjectByNameAndClass("Level_Init", CKCID_BEHAVIOR));

		bbPhysConv = CreatePhysicalizeConvex();
		bbPhysBall = CreatePhysicalizeBall();
		bbPhysConc = CreatePhysicalizeConcave();
		bbObjLoad = CreateObjectLoad();
	}
}
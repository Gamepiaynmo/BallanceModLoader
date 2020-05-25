#include "NewBallTypeMod.h"
#include "ExecuteBB.h"
#include "minhook/MinHook.h"
#include <filesystem>
#include "ScriptHelper.h"
#include "RegisterBB.h"

using namespace ScriptHelper;

FixPath::ResolveFunc FixPath::m_resolve = &FixPath::Resolve;

CKERROR FixPath::Resolve(XString& file, int catIdx, int startIdx) {
	for (int i = 0; i < GetPathCount(catIdx); i++) {
		XString path;
		GetPathName(catIdx, i, path);
		path += file;
		if (std::filesystem::exists(path.CStr())) {
			file = path;
			return CK_OK;
		}
	}

	return (this->*m_resolve)(file, catIdx, startIdx);
}

void NewBallTypeMod::OnLoad() {
	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x24013b3c),
		*reinterpret_cast<LPVOID*>(&FixPath::m_resolve),
		reinterpret_cast<LPVOID*>(&FixPath::m_resolve)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x24013b3c)) != MH_OK) {
		GetLogger()->Warn("Hook ResolveFileName Failed");
	}

	m_stickyImpulse = 90.0f;
	RegisterBallType("Ball_Sticky.nmo", "sticky", "Sticky", "Ball_Sticky", 10.0f, 0.0f, 1.4f, "Ball", 0.8f, 7.0f, 0.12f, 2.0f);
	RegisterTrafo("P_Trafo_Sticky");

	for (int i = 0; i < 2; i++) {
		m_ballRef[i] = static_cast<CK3dEntity*>(m_bml->GetCKContext()->CreateObject(CKCID_3DENTITY, "Ball_Sticky_Ref"));
		m_bml->GetCKContext()->GetCurrentScene()->AddObjectToScene(m_ballRef[i]);
	}
}

void NewBallTypeMod::OnLoadObject(CKSTRING filename, CKSTRING masterName, CK_CLASSID filterClass,
	BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
	XObjectArray* objArray, CKObject* masterObj) {
	if (!strcmp(filename, "3D Entities\\Balls.nmo"))
		OnLoadBalls(objArray);

	if (!strcmp(filename, "3D Entities\\Levelinit.nmo"))
		OnLoadLevelinit(objArray);

	if (!strcmp(filename, "3D Entities\\Sounds.nmo"))
		OnLoadSounds(objArray);
}

void NewBallTypeMod::OnLoadScript(CKSTRING filename, CKBehavior* script) {
	if (!strcmp(script->GetName(), "Gameplay_Ingame"))
		OnEditScript_Gameplay_Ingame(script);

	if (!strcmp(script->GetName(), "Event_handler"))
		OnEditScript_Base_EventHandler(script);
}

void NewBallTypeMod::OnProcess() {
	if (m_bml->IsIngame() && m_curLevel) {
		CK3dEntity* curBall = static_cast<CK3dEntity*>(m_curLevel->GetElementObject(0, 1));
		if (curBall) {
			VxVector pos;
			curBall->GetPosition(&pos);
			pos.y += 1;
			m_ballRef[0]->SetPosition(&pos);
			pos.y -= 2;
			m_ballRef[1]->SetPosition(&pos);

			bool isSticky = !strcmp(curBall->GetName(), "Ball_Sticky");
			SetParamValue(m_stickyForce[0], isSticky ? m_stickyImpulse : 0);
			SetParamValue(m_stickyForce[1], isSticky ? -m_stickyImpulse : 0);
		}
	}
}

void NewBallTypeMod::RegisterBallType(CKSTRING ballFile, CKSTRING ballId, CKSTRING ballName, CKSTRING objName, float friction,
	float elasticity, float mass, CKSTRING collGroup, float linearDamp, float rotDamp, float force, float radius) {
	m_ballTypes.push_back(BallTypeInfo());
	BallTypeInfo& info = m_ballTypes.back();

	info.m_file = ballFile;
	info.m_id = ballId;
	info.m_name = ballName;
	info.m_objName = objName;

	info.m_radius = radius;

	info.m_friction = friction;
	info.m_elasticity = elasticity;
	info.m_mass = mass;
	info.m_collGroup = collGroup;
	info.m_linearDamp = linearDamp;
	info.m_rotDamp = rotDamp;
	info.m_force = force;
}

void NewBallTypeMod::RegisterFloorType(CKSTRING floorName, float friction, float elasticity, float mass, CKSTRING collGroup, bool enableColl) {
	m_floorTypes.push_back(FloorTypeInfo());
	FloorTypeInfo& info = m_floorTypes.back();

	info.m_name = floorName;

	info.m_friction = friction;
	info.m_elasticity = elasticity;
	info.m_mass = mass;
	info.m_collGroup = collGroup;
	info.m_enableColl = enableColl;
}

void NewBallTypeMod::RegisterModulBall(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
	bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp, float radius) {
	m_modulBalls.push_back(ModulBallInfo());
	ModulBallInfo& info = m_modulBalls.back();

	info.m_name = modulName;

	info.m_fixed = fixed;
	info.m_friction = friction;
	info.m_elasticity = elasticity;
	info.m_mass = mass;
	info.m_collGroup = collGroup;
	info.m_frozen = frozen;
	info.m_enableColl = enableColl;
	info.m_massCenter = calcMassCenter;
	info.m_linearDamp = linearDamp;
	info.m_rotDamp = rotDamp;
	info.m_radius = radius;
}

void NewBallTypeMod::RegisterModulConvex(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
	bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp) {
	m_modulContexs.push_back(ModulConvexInfo());
	ModulConvexInfo& info = m_modulContexs.back();

	info.m_name = modulName;

	info.m_fixed = fixed;
	info.m_friction = friction;
	info.m_elasticity = elasticity;
	info.m_mass = mass;
	info.m_collGroup = collGroup;
	info.m_frozen = frozen;
	info.m_enableColl = enableColl;
	info.m_massCenter = calcMassCenter;
	info.m_linearDamp = linearDamp;
	info.m_rotDamp = rotDamp;
}

void NewBallTypeMod::RegisterTrafo(CKSTRING modulName) {
	m_moduls.push_back(ModulInfo());
	ModulInfo& info = m_moduls.back();

	info.m_name = modulName;
	info.m_type = 0;
}

void NewBallTypeMod::RegisterModul(CKSTRING modulName) {
	m_moduls.push_back(ModulInfo());
	ModulInfo& info = m_moduls.back();

	info.m_name = modulName;
	info.m_type = 1;
}


void NewBallTypeMod::OnLoadBalls(XObjectArray* objArray) {
	m_physBall = m_bml->GetArrayByName("Physicalize_GameBall");
	m_allBalls = m_bml->GetGroupByName("All_Balls");
	std::string path = "3D Entities\\";
	CK3dEntity* ballMF = m_bml->Get3dEntityByName("Balls_MF");

	for (BallTypeInfo& info : m_ballTypes) {
		XObjectArray* objArray = ExecuteBB::ObjectLoad((path + info.m_file).c_str(), false).first;

		std::string allGroup = "All_" + info.m_objName;
		std::string piecesGroup = info.m_objName + "_Pieces";
		std::string piecesFrame = info.m_objName + "Pieces_Frame";
		std::string explosion = "Ball_Explosion_" + info.m_name;
		std::string reset = "Ball_ResetPieces_" + info.m_name;

		for (CK_ID* id = objArray->Begin(); id != objArray->End(); id++) {
			CKObject* obj = m_bml->GetCKContext()->GetObject(*id);
			CKSTRING name = obj->GetName();
			if (name) {
				if (allGroup == name)
					info.m_allGroup = static_cast<CKGroup*>(obj);
				if (info.m_objName == name)
					info.m_ballObj = static_cast<CK3dObject*>(obj);
				if (piecesGroup == name)
					info.m_piecesGroup = static_cast<CKGroup*>(obj);
				if (piecesFrame == name)
					info.m_piecesFrame = static_cast<CK3dEntity*>(obj);
				if (explosion == name)
					info.m_explosion = static_cast<CKBehavior*>(obj);
				if (reset == name)
					info.m_reset = static_cast<CKBehavior*>(obj);
			}
		}

		SetParamObject(info.m_ballParam, info.m_ballObj);
		SetParamObject(info.m_resetParam, info.m_reset);
		info.m_ballObj->SetParent(ballMF);
		info.m_piecesFrame->SetParent(ballMF);

		m_physBall->AddRow();
		int row = m_physBall->GetRowCount() - 1;

		m_physBall->SetElementStringValue(row, 0, info.m_objName.c_str());
		m_physBall->SetElementValue(row, 1, &info.m_friction);
		m_physBall->SetElementValue(row, 2, &info.m_elasticity);
		m_physBall->SetElementValue(row, 3, &info.m_mass);
		m_physBall->SetElementStringValue(row, 4, info.m_collGroup.c_str());
		m_physBall->SetElementValue(row, 5, &info.m_linearDamp);
		m_physBall->SetElementValue(row, 6, &info.m_rotDamp);
		m_physBall->SetElementValue(row, 7, &info.m_force);

		for (int i = 0; i < info.m_allGroup->GetObjectCount(); i++)
			m_allBalls->AddObject(info.m_allGroup->GetObject(i));
	}
}

void NewBallTypeMod::OnLoadLevelinit(XObjectArray* objArray) {
	CKDataArray* allLevel = m_bml->GetArrayByName("AllLevel");
	for (int i = 0; i < allLevel->GetRowCount(); i++)
		allLevel->SetElementStringValue(i, 1, "Ball_Sticky");

	CKDataArray* phGroups = m_bml->GetArrayByName("PH_Groups");
	CKDataArray* physBalls = m_bml->GetArrayByName("Physicalize_Balls");
	CKDataArray* physConvexs = m_bml->GetArrayByName("Physicalize_Convex");
	CKDataArray* physFloors = m_bml->GetArrayByName("Physicalize_Floors");

	for (ModulInfo& info : m_moduls) {
		phGroups->AddRow();
		int row = phGroups->GetRowCount() - 1;
		phGroups->SetElementStringValue(row, 0, info.m_name.c_str());
		int activation = 1;
		phGroups->SetElementValue(row, 2, &activation);
		phGroups->SetElementValue(row, 3, &info.m_type);
	}

	for (FloorTypeInfo& info : m_floorTypes) {
		physFloors->AddRow();
		int row = physFloors->GetRowCount() - 1;
		physFloors->SetElementStringValue(row, 0, info.m_name.c_str());
		physFloors->SetElementValue(row, 1, &info.m_friction);
		physFloors->SetElementValue(row, 2, &info.m_elasticity);
		physFloors->SetElementValue(row, 3, &info.m_mass);
		physFloors->SetElementStringValue(row, 4, info.m_collGroup.c_str());
		physFloors->SetElementValue(row, 5, &info.m_enableColl);
	}

	for (ModulConvexInfo& info : m_modulContexs) {
		physConvexs->AddRow();
		int row = physConvexs->GetRowCount() - 1;
		physConvexs->SetElementStringValue(row, 0, info.m_name.c_str());
		physConvexs->SetElementValue(row, 1, &info.m_fixed);
		physConvexs->SetElementValue(row, 2, &info.m_friction);
		physConvexs->SetElementValue(row, 3, &info.m_elasticity);
		physConvexs->SetElementValue(row, 4, &info.m_mass);
		physConvexs->SetElementStringValue(row, 5, info.m_collGroup.c_str());
		physConvexs->SetElementValue(row, 6, &info.m_frozen);
		physConvexs->SetElementValue(row, 7, &info.m_enableColl);
		physConvexs->SetElementValue(row, 8, &info.m_massCenter);
		physConvexs->SetElementValue(row, 9, &info.m_linearDamp);
		physConvexs->SetElementValue(row, 10, &info.m_rotDamp);

		phGroups->AddRow();
		row = phGroups->GetRowCount() - 1;
		phGroups->SetElementStringValue(row, 0, info.m_name.c_str());
		int activation = 2, reset = 2;
		phGroups->SetElementValue(row, 2, &activation);
		phGroups->SetElementValue(row, 3, &reset);
	}

	for (ModulBallInfo& info : m_modulBalls) {
		physBalls->AddRow();
		int row = physBalls->GetRowCount() - 1;
		physBalls->SetElementStringValue(row, 0, info.m_name.c_str());
		physBalls->SetElementValue(row, 1, &info.m_fixed);
		physBalls->SetElementValue(row, 2, &info.m_friction);
		physBalls->SetElementValue(row, 3, &info.m_elasticity);
		physBalls->SetElementValue(row, 4, &info.m_mass);
		physBalls->SetElementStringValue(row, 5, info.m_collGroup.c_str());
		physBalls->SetElementValue(row, 6, &info.m_frozen);
		physBalls->SetElementValue(row, 7, &info.m_enableColl);
		physBalls->SetElementValue(row, 8, &info.m_massCenter);
		physBalls->SetElementValue(row, 9, &info.m_linearDamp);
		physBalls->SetElementValue(row, 10, &info.m_rotDamp);
		physBalls->SetElementValue(row, 11, &info.m_radius);

		phGroups->AddRow();
		row = phGroups->GetRowCount() - 1;
		phGroups->SetElementStringValue(row, 0, info.m_name.c_str());
		int activation = 3, reset = 2;
		phGroups->SetElementValue(row, 2, &activation);
		phGroups->SetElementValue(row, 3, &reset);
	}

	m_bml->SetIC(phGroups);
}

void NewBallTypeMod::OnLoadSounds(XObjectArray* objArray) {
	CKDataArray* ballSound = m_bml->GetArrayByName("BallSound");

	for (BallTypeInfo& info : m_ballTypes) {
		std::string roll = "Roll_" + info.m_name;
		std::string hit = "Hit_" + info.m_name;

		ballSound->AddRow();
		int row = ballSound->GetRowCount() - 1;
		ballSound->SetElementStringValue(row, 0, info.m_objName.c_str());
		ballSound->SetElementStringValue(row, 1, (roll + "_Stone").c_str());
		ballSound->SetElementStringValue(row, 2, (roll + "_Wood").c_str());
		ballSound->SetElementStringValue(row, 3, (roll + "_Metal").c_str());
		ballSound->SetElementStringValue(row, 4, (hit + "_Stone").c_str());
		ballSound->SetElementStringValue(row, 5, (hit + "_Wood").c_str());
		ballSound->SetElementStringValue(row, 6, (hit + "_Metal").c_str());
		ballSound->SetElementStringValue(row, 7, (hit + "_Dome").c_str());
	}
}

void NewBallTypeMod::OnEditScript_Gameplay_Ingame(CKBehavior* script) {
	m_curLevel = m_bml->GetArrayByName("CurrentLevel");

	{
		CKBehavior* ballMgr = FindFirstBB(script, "BallManager");
		CKBehavior* newBall = FindFirstBB(ballMgr, "New Ball");
		CKBehavior* phyNewBall = FindFirstBB(newBall, "physicalize new Ball");
		OnEditScript_PhysicalizeNewBall(phyNewBall);

		CKBehavior* deactBall = FindFirstBB(ballMgr, "Deactivate Ball");
		CKBehavior* resetPieces = FindFirstBB(deactBall, "reset Ballpieces");
		OnEditScript_ResetBallPieces(resetPieces);
	}

	{
		CKBehavior* init = FindFirstBB(script, "Init Ingame");
		CKBehavior* trafoAttr = FindFirstBB(init, "set Trafo-Attribute");
		CKAttributeManager* am = m_bml->GetAttributeManager();
		CKAttributeType trafoType = am->GetAttributeTypeByName("TrafoType");
		for (BallTypeInfo& info : m_ballTypes) {
			CKBehavior* setAttr = CreateBB(trafoAttr, VT_SETATTRIBUTE, true);
			CKParameter* attr = CreateParamValue(trafoAttr, "Attr", CKPGUID_ATTRIBUTE, trafoType);
			CKParameter* attrParam = CreateParamString(trafoAttr, "Param", info.m_id.c_str());
			setAttr->GetTargetParameter()->SetDirectSource(info.m_ballParam);
			setAttr->GetInputParameter(0)->SetDirectSource(attr);
			setAttr->CreateInputParameter("Param", CKPGUID_STRING)->SetDirectSource(attrParam);
			InsertBB(trafoAttr, FindPreviousLink(trafoAttr, trafoAttr->GetOutput(0)), setAttr);
		}
	}

	{
		CKBehavior* trafoMgr = FindFirstBB(script, "Trafo Manager");

		{
			CKBehavior* pieceFlag = FindFirstBB(trafoMgr, "set Piecesflag");
			CKBehavior* sop = FindFirstBB(pieceFlag, "Switch On Parameter");
			CKParameterType booltype = m_bml->GetParameterManager()->ParameterGuidToType(CKPGUID_BOOL);
			for (BallTypeInfo& info : m_ballTypes) {
				CKParameter* id = CreateParamString(pieceFlag, "Pin", info.m_id.c_str());
				CKParameter* boolTrue = CreateParamValue(pieceFlag, "True", CKPGUID_BOOL, TRUE);
				CKBehavior* identity = CreateBB(pieceFlag, VT_IDENTITY);
				identity->GetInputParameter(0)->SetType(booltype);
				identity->GetOutputParameter(0)->SetType(booltype);

				identity->GetInputParameter(0)->SetDirectSource(boolTrue);
				identity->GetOutputParameter(0)->AddDestination(info.m_usedParam, false);
				sop->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(id);
				CreateLink(pieceFlag, sop->CreateOutput("Out"), identity);
				CreateLink(pieceFlag, identity, pieceFlag->GetOutput(0));
			}
		}

		{
		CKBehavior* phyNewBall = FindFirstBB(trafoMgr, "physicalize new Ball");
		OnEditScript_PhysicalizeNewBall(phyNewBall);
		}

		{
			CKBehavior* explode = FindFirstBB(trafoMgr, "start Explosion");
			CKBehavior* sop = FindFirstBB(explode, "Switch On Parameter");
			CKBehavior* ps = FindFirstBB(explode, "Parameter Selector");
			for (BallTypeInfo& info : m_ballTypes) {
				std::string explosion = "Ball_Explosion_" + info.m_name;
				CKParameter* id = CreateParamString(explode, "Pin", info.m_id.c_str());
				CKParameter* script = CreateParamString(explode, "Pin", explosion.c_str());
				sop->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(id);
				ps->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(script);
				CreateLink(explode, sop->CreateOutput("Out"), ps->CreateInput("In"));
			}
		}

		{
			CKBehavior* setNewBall = FindFirstBB(trafoMgr, "set new Ball");
			CKBehavior* sop = FindFirstBB(setNewBall, "Switch On Parameter");
			CKBehavior* ps = FindFirstBB(setNewBall, "Parameter Selector");
			for (BallTypeInfo& info : m_ballTypes) {
				CKParameter* id = CreateParamString(setNewBall, "Pin", info.m_id.c_str());
				sop->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(id);
				ps->CreateInputParameter("Pin", CKPGUID_3DENTITY)->SetDirectSource(info.m_ballParam);
				CreateLink(setNewBall, sop->CreateOutput("Out"), ps->CreateInput("In"));
			}
		}

		{
			CKBehavior* fadeout = FindFirstBB(trafoMgr, "Fadeout Manager");
			CKBehavior* identity = nullptr;
			FindBB(fadeout, [&identity](CKBehavior* beh) {
				if (beh->GetInputParameterCount() == 3) {
					identity = beh;
					return false;
				}
				else return true;
				}, "Identity");
			CKParameterType booltype = m_bml->GetParameterManager()->ParameterGuidToType(CKPGUID_BOOL);
			CKParameter* time = CreateParamValue(fadeout, "Time", CKPGUID_TIME, 20000.0f);
			CKParameter* reset = CreateParamValue(fadeout, "Reset", CKPGUID_BOOL, TRUE);
			CKParameter* setfalse = CreateParamValue(fadeout, "False", CKPGUID_BOOL, FALSE);
			for (BallTypeInfo& info : m_ballTypes) {
				CKBehavior* binswitch[2] = { CreateBB(fadeout, VT_BINARYSWITCH), CreateBB(fadeout, VT_BINARYSWITCH) };
				CKBehavior* seton = CreateBB(fadeout, VT_IDENTITY);
				seton->GetInputParameter(0)->SetType(booltype);
				seton->GetOutputParameter(0)->SetType(booltype);
				CKBehavior* timer = CreateBB(fadeout, VT_TIMER);
				CKBehavior* activate = CreateBB(fadeout, VT_ACTIVATESCRIPT);
				info.m_timer = timer;
				info.m_binswitch[0] = binswitch[0];
				info.m_binswitch[1] = binswitch[1];

				identity->GetOutputParameter(0)->AddDestination(info.m_usedParam, false);
				binswitch[0]->GetInputParameter(0)->SetDirectSource(info.m_usedParam);
				binswitch[1]->GetInputParameter(0)->SetDirectSource(info.m_usedParam);
				seton->GetInputParameter(0)->SetDirectSource(setfalse);
				seton->GetOutputParameter(0)->AddDestination(info.m_usedParam, false);
				timer->GetInputParameter(0)->SetDirectSource(time);
				activate->GetInputParameter(0)->SetDirectSource(reset);
				activate->GetInputParameter(1)->SetDirectSource(info.m_resetParam);

				CreateLink(fadeout, identity, binswitch[0]);
				CreateLink(fadeout, binswitch[0], binswitch[0], 1, 0, 1);
				CreateLink(fadeout, binswitch[0], seton);
				CreateLink(fadeout, seton, timer);
				CreateLink(fadeout, timer, binswitch[1], 1);
				CreateLink(fadeout, binswitch[1], timer, 1, 1, 1);
				CreateLink(fadeout, timer, activate);
				CreateLink(fadeout, binswitch[1], activate);
				CreateLink(fadeout, activate, binswitch[0], 0, 0, 1);
			}
		}
	}

	{
		CKBehavior* ballNav = FindFirstBB(script, "Ball Navigation");
		CKBehavior* oForce = FindFirstBB(ballNav, "SetPhysicsForce");
		CKBehavior* forces[8], * keepActive[8], * perSecond[8];
		m_stickyForce[0] = CreateParamValue(ballNav, "Force", CKPGUID_FLOAT, m_stickyImpulse);
		m_stickyForce[1] = CreateParamValue(ballNav, "Force", CKPGUID_FLOAT, -m_stickyImpulse);
		CKParameter* posRef[2] = { CreateParamObject(ballNav, "PosRef", CKPGUID_3DENTITY, m_ballRef[0]),
			CreateParamObject(ballNav, "PosRef", CKPGUID_3DENTITY, m_ballRef[1]) };
		for (int i = 0; i < 8; i++) {
			keepActive[i] = CreateBB(ballNav, VT_KEEPACTIVE);
			perSecond[i] = CreateBB(ballNav, VT_PERSECOND);
			perSecond[i]->GetInputParameter(0)->SetDirectSource(m_stickyForce[i % 2]);
			CreateLink(ballNav, keepActive[i], perSecond[i], 1);
			forces[i] = CreateBB(ballNav, TT_PHYSICSIMPLUSE, true);
			forces[i]->GetTargetParameter()->ShareSourceWith(oForce->GetTargetParameter());
			forces[i]->GetInputParameter(0)->ShareSourceWith(oForce->GetInputParameter(0));
			forces[i]->GetInputParameter(1)->SetDirectSource(posRef[i % 2]);
			forces[i]->GetInputParameter(3)->ShareSourceWith(oForce->GetInputParameter(3));
			forces[i]->GetInputParameter(4)->SetDirectSource(perSecond[i]->GetOutputParameter(0));
			CreateLink(ballNav, perSecond[i], forces[i]);
		}

		int cnt = 0;
		FindBB(ballNav, [ballNav, forces, keepActive, &cnt](CKBehavior* beh) {
			VxVector dir;
			beh->GetInputParameterValue(2, &dir);
			int idx = -1;
			if (dir.x == 1) idx = 0;
			if (dir.x == -1) idx = 2;
			if (dir.z == 1) idx = 4;
			if (dir.z == -1) idx = 6;
			if (idx >= 0) {
				cnt++;
				for (int i = idx; i < idx + 2; i++) {
					forces[i]->GetInputParameter(2)->ShareSourceWith(beh->GetInputParameter(2));
					CreateLink(ballNav, beh, keepActive[i], 0, 1);
					CreateLink(ballNav, beh, keepActive[i], 1, 0);
				}
			}
			return cnt < 4;
			}, "SetPhysicsForce");
	}
}

void NewBallTypeMod::OnEditScript_Base_EventHandler(CKBehavior* script) {
	for (BallTypeInfo& info : m_ballTypes) {
		info.m_ballParam = CreateLocalParameter(script, "Target", CKPGUID_BEOBJECT);
		info.m_usedParam = CreateLocalParameter(script, "Used", CKPGUID_BOOL);
		info.m_resetParam = CreateLocalParameter(script, "Script", CKPGUID_SCRIPT);
	}

	auto addResetAttr = [this](CKBehavior* graph) {
		CKBehavior* remAttr = FindFirstBB(graph, "Remove Attribute");
		for (BallTypeInfo& info : m_ballTypes) {
			CKBehavior* attr = CreateBB(graph, VT_REMOVEATTRIBUTE, true);
			attr->GetTargetParameter()->SetDirectSource(info.m_ballParam);
			attr->GetInputParameter(0)->ShareSourceWith(remAttr->GetInputParameter(0));
			InsertBB(graph, FindNextLink(graph, graph->GetInput(0)), attr);
		}
	};

	CKBehavior* resetLevel = FindFirstBB(script, "reset Level");
	CKBehavior* resetPieces = FindFirstBB(resetLevel, "reset Ballpieces");
	OnEditScript_ResetBallPieces(resetPieces);
	resetLevel = FindFirstBB(resetLevel, "reset  Level");
	resetLevel = FindFirstBB(resetLevel, "reset Level");
	addResetAttr(resetLevel);

	CKBehavior* exitLevel = FindFirstBB(script, "Exit Level");
	resetPieces = FindFirstBB(exitLevel, "reset Ballpieces");
	OnEditScript_ResetBallPieces(resetPieces);
	resetLevel = FindFirstBB(exitLevel, "reset Level");
	addResetAttr(resetLevel);
}

void NewBallTypeMod::OnEditScript_PhysicalizeNewBall(CKBehavior* graph) {
	CKBehavior* physicalize = FindFirstBB(graph, "Physicalize");
	CKBehavior* sop = FindFirstBB(graph, "Switch On Parameter");
	CKBehavior* show = FindFirstBB(graph, "Show");
	CKBehavior* op = FindNextBB(graph, graph->GetInput(0));

	for (BallTypeInfo& info : m_ballTypes) {
		CKParameter* ballName = CreateParamString(graph, "Pin", info.m_objName.c_str());
		sop->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(ballName);
		CKBehavior* newPhy = nullptr;
		if (info.m_radius > 0) {
			newPhy = ExecuteBB::CreatePhysicalizeBall();
			SetParamValue(newPhy->GetInputParameter(12)->GetDirectSource(), info.m_radius);
		}
		else {
			newPhy = ExecuteBB::CreatePhysicalizeConvex();
			newPhy->GetInputParameter(11)->SetDirectSource(op->GetOutputParameter(0));
		}

		graph->AddSubBehavior(newPhy);
		newPhy->GetTargetParameter()->ShareSourceWith(physicalize->GetTargetParameter());
		for (int i = 0; i < 11; i++)
			newPhy->GetInputParameter(i)->ShareSourceWith(physicalize->GetInputParameter(i));
		CreateLink(graph, sop->CreateOutput("Out"), newPhy);
		CreateLink(graph, newPhy, show);
	}
}

void NewBallTypeMod::OnEditScript_ResetBallPieces(CKBehavior* graph) {
	CKBehavior* seq = FindFirstBB(graph, "Sequencer");
	CKBehavior* ps = FindFirstBB(graph, "Parameter Selector");

	for (BallTypeInfo& info : m_ballTypes) {
		std::string reset = "Ball_ResetPieces_" + info.m_name;
		CKParameter* script = CreateParamString(graph, "Pin", reset.c_str());
		ps->CreateInputParameter("Pin", CKPGUID_STRING)->SetDirectSource(script);

		int cnt = seq->GetOutputCount() - 1;
		FindNextLink(graph, seq->GetOutput(cnt))->SetInBehaviorIO(seq->CreateOutput("Out"));
		CreateLink(graph, seq->GetOutput(seq->GetOutputCount() - 2), ps->CreateInput("In"));
	}
}
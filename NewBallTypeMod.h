#pragma once

#include "IMod.h"
#include "Version.h"

struct BallTypeInfo {
	friend class NewBallTypeMod;

	std::string m_file;
	std::string m_id;
	std::string m_name;
	std::string m_objName;

	CKGroup* m_allGroup = nullptr;
	CK3dObject* m_ballObj = nullptr;

	CKGroup* m_piecesGroup = nullptr;
	CK3dEntity* m_piecesFrame = nullptr;

	CKBehavior* m_explosion = nullptr;
	CKBehavior* m_reset = nullptr;

	std::string m_collGroup;
	float m_friction, m_elasticity, m_mass;
	float m_linearDamp, m_rotDamp, m_force;
	float m_radius;

private:
	CKParameter* m_ballParam = nullptr;
	CKParameter* m_usedParam = nullptr;
	CKParameter* m_resetParam = nullptr;
	CKBehavior* m_timer = nullptr;
	CKBehavior* m_binswitch[2];
};

class FixPath : public CKPathManager {
public:
	CKERROR Resolve(XString& file, int catIdx, int startIdx);

	typedef CKERROR (FixPath::*ResolveFunc)(XString&, int, int);
	static ResolveFunc m_resolve;
};

struct FloorTypeInfo {
	std::string m_name;

	std::string m_collGroup;
	float m_friction, m_elasticity, m_mass;
	CKBOOL m_enableColl;
};

struct ModulConvexInfo : public FloorTypeInfo {
	CKBOOL m_fixed, m_frozen, m_massCenter;
	float m_linearDamp, m_rotDamp;
};

struct ModulBallInfo : public ModulConvexInfo {
	float m_radius;
};

struct ModulInfo {
	std::string m_name;
	int m_type;
};

class NewBallTypeMod : public IMod {
public:
	NewBallTypeMod(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "NewBallType"; }
	virtual CKSTRING GetVersion() override { return BML_VERSION; }
	virtual CKSTRING GetName() override { return "New Ball Type"; }
	virtual CKSTRING GetAuthor() override { return "Gamepiaynmo & YingChe"; }
	virtual CKSTRING GetDescription() override { return "Implementation of registering new ball types."; }

	virtual void OnLoad() override;
	virtual void OnLoadObject(CKSTRING filename, CKSTRING masterName, CK_CLASSID filterClass,
		BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
		XObjectArray* objArray, CKObject* masterObj) override;
	virtual void OnLoadScript(CKSTRING filename, CKBehavior* script) override;
	virtual void OnProcess() override;

	void RegisterBallType(CKSTRING ballFile, CKSTRING ballId, CKSTRING ballName, CKSTRING objName, float friction, float elasticity,
		float mass, CKSTRING collGroup, float linearDamp, float rotDamp, float force, float radius);
	void RegisterFloorType(CKSTRING floorName, float friction, float elasticity, float mass, CKSTRING collGroup, bool enableColl);
	void RegisterModulBall(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp, float radius);
	void RegisterModulConvex(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp);
	void RegisterTrafo(CKSTRING modulName);
	void RegisterModul(CKSTRING modulName);

private:
	CKDataArray* m_physBall = nullptr;
	CKGroup* m_allBalls = nullptr;
	void OnLoadBalls(XObjectArray* objArray);
	void OnLoadLevelinit(XObjectArray* objArray);
	void OnLoadSounds(XObjectArray* objArray);

	CK3dEntity* m_ballRef[2] = { 0 };
	CK3dEntity* m_camTarget = nullptr;
	CKDataArray* m_curLevel = nullptr;
	float m_stickyImpulse;
	CKParameter* m_stickyForce[2];
	void OnEditScript_Gameplay_Ingame(CKBehavior* script);
	void OnEditScript_Base_EventHandler(CKBehavior* script);
	void OnEditScript_PhysicalizeNewBall(CKBehavior* graph);
	void OnEditScript_ResetBallPieces(CKBehavior* graph);

	std::vector<BallTypeInfo> m_ballTypes;
	std::vector<FloorTypeInfo> m_floorTypes;
	std::vector<ModulInfo> m_moduls;
	std::vector<ModulConvexInfo> m_modulContexs;
	std::vector<ModulBallInfo> m_modulBalls;
};
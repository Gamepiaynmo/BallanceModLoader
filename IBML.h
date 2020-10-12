#pragma once

#include "Export.h"
#include "ILogger.h"
#include "virtools/CKAll.h"
#include <functional>
#include "Gui.h"
#include "ICommand.h"

class BML_EXPORT IMessageReceiver {
public:
	virtual void OnPreStartMenu() {};
	virtual void OnPostStartMenu() {};

	virtual void OnExitGame() {};

	virtual void OnPreLoadLevel() {};
	virtual void OnPostLoadLevel() {};

	virtual void OnStartLevel() {};

	virtual void OnPreResetLevel() {};
	virtual void OnPostResetLevel() {};

	virtual void OnPauseLevel() {};
	virtual void OnUnpauseLevel() {};

	virtual void OnPreExitLevel() {};
	virtual void OnPostExitLevel() {};

	virtual void OnPreNextLevel() {};
	virtual void OnPostNextLevel() {};

	virtual void OnDead() {};

	virtual void OnPreEndLevel() {};
	virtual void OnPostEndLevel() {};

	virtual void OnCounterActive() {};
	virtual void OnCounterInactive() {};

	virtual void OnBallNavActive() {};
	virtual void OnBallNavInactive() {};

	virtual void OnCamNavActive() {};
	virtual void OnCamNavInactive() {};

	virtual void OnBallOff() {};

	virtual void OnPreCheckpointReached() {};
	virtual void OnPostCheckpointReached() {};

	virtual void OnLevelFinish() {};

	virtual void OnGameOver() {};
	
	virtual void OnExtraPoint() {};

	virtual void OnPreSubLife() {};
	virtual void OnPostSubLife() {};

	virtual void OnPreLifeUp() {};
	virtual void OnPostLifeUp() {};
};

class BML_EXPORT IBML : public IMessageReceiver {
public:
	virtual CKContext* GetCKContext() = 0;
	virtual CKRenderContext* GetRenderContext() = 0;

	virtual void ExitGame() = 0;

	virtual CKAttributeManager* GetAttributeManager() = 0;
	virtual CKBehaviorManager* GetBehaviorManager() = 0;
	virtual CKCollisionManager* GetCollisionManager() = 0;
	virtual InputHook* GetInputManager() = 0;
	virtual CKMessageManager* GetMessageManager() = 0;
	virtual CKPathManager* GetPathManager() = 0;
	virtual CKParameterManager* GetParameterManager() = 0;
	virtual CKRenderManager* GetRenderManager() = 0;
	virtual CKSoundManager* GetSoundManager() = 0;
	virtual CKTimeManager* GetTimeManager() = 0;

	virtual void AddTimer(CKDWORD delay, std::function<void()> callback) = 0;
	virtual void AddTimerLoop(CKDWORD delay, std::function<bool()> callback) = 0;
	virtual void AddTimer(float delay, std::function<void()> callback) = 0;
	virtual void AddTimerLoop(float delay, std::function<bool()> callback) = 0;

	virtual bool IsCheatEnabled() = 0;
	virtual void EnableCheat(bool enable) = 0;

	virtual void SendIngameMessage(CKSTRING msg) = 0;

	virtual void RegisterCommand(ICommand* cmd) = 0;

	virtual void SetIC(CKBeObject* obj, bool hierarchy = false) = 0;
	virtual void RestoreIC(CKBeObject* obj, bool hierarchy = false) = 0;
	virtual void Show(CKBeObject* obj, CK_OBJECT_SHOWOPTION show, bool hierarchy = false) = 0;

	virtual bool IsIngame() = 0;
	virtual bool IsPaused() = 0;
	virtual bool IsPlaying() = 0;

	virtual CKDataArray* GetArrayByName(CKSTRING name) = 0;
	virtual CKGroup* GetGroupByName(CKSTRING name) = 0;
	virtual CKMaterial* GetMaterialByName(CKSTRING name) = 0;
	virtual CKMesh* GetMeshByName(CKSTRING name) = 0;
	virtual CK2dEntity* Get2dEntityByName(CKSTRING name) = 0;
	virtual CK3dEntity* Get3dEntityByName(CKSTRING name) = 0;
	virtual CK3dObject* Get3dObjectByName(CKSTRING name) = 0;
	virtual CKCamera* GetCameraByName(CKSTRING name) = 0;
	virtual CKTargetCamera* GetTargetCameraByName(CKSTRING name) = 0;
	virtual CKLight* GetLightByName(CKSTRING name) = 0;
	virtual CKTargetLight* GetTargetLightByName(CKSTRING name) = 0;
	virtual CKSound* GetSoundByName(CKSTRING name) = 0;
	virtual CKTexture* GetTextureByName(CKSTRING name) = 0;
	virtual CKBehavior* GetScriptByName(CKSTRING name) = 0;

	virtual void RegisterBallType(CKSTRING ballFile, CKSTRING ballId, CKSTRING ballName, CKSTRING objName, float friction, float elasticity,
		float mass, CKSTRING collGroup, float linearDamp, float rotDamp, float force, float radius) = 0;
	virtual void RegisterFloorType(CKSTRING floorName, float friction, float elasticity, float mass, CKSTRING collGroup, bool enableColl) = 0;
	virtual void RegisterModulBall(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp, float radius) = 0;
	virtual void RegisterModulConvex(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp) = 0;
	virtual void RegisterTrafo(CKSTRING modulName) = 0;
	virtual void RegisterModul(CKSTRING modulName) = 0;

	virtual int GetModCount() = 0;
	virtual class IMod* GetMod(int index) = 0;
};

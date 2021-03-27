#pragma once

#include "IBML.h"
#include <cstdio>
#include <functional>
#include <list>
#include <vector>
#include <Windows.h>
#include "virtools/CKAll.h"
#include "IMod.h"
#include "Config.h"
#include "Timer.h"
#include "Gui.h"
#include <map>
#include <filesystem>

class BMLMod;
class NewBallTypeMod;

typedef IMod* (*EntryFunc)(IBML*);
typedef void (*RegisterBBFunc)(XObjectDeclarationArray*);

template<typename T>
void* func_addr(T func) {
	return *reinterpret_cast<void**>(&func);
}

class ModLoader : public IBML {
	friend class BMLMod;
	friend class CommandBML;
	friend class CommandHelp;
	friend class CommandCheat;
	friend class CommandClear;
	friend class CommandSector;
	friend class GuiList;
	friend class GuiModOption;
	friend class GuiModMenu;
	friend class GuiModCategory;
public:
	ModLoader();
	~ModLoader();

	static ModLoader* m_instance;

	void Init();
	void Release();

	CKERROR Step(CKDWORD result);
	void Process(CKERROR result);
	void Render(CK_RENDER_FLAGS flags, CKERROR result);

	bool Inited() { return m_inited; }
	FILE* GetLogFile() { return m_logfile; }
	void AddConfig(Config* config) { m_configs.push_back(config); }
	Config* GetConfig(IMod* mod);

	static void WriteMemory(LPVOID dest, LPVOID src, int len);

	virtual CKContext* GetCKContext() override { return m_context; }
	virtual CKRenderContext* GetRenderContext() override { return m_renderContext; }

	virtual void ExitGame() override { m_exiting = true; }

	virtual CKAttributeManager* GetAttributeManager() override { return m_attributeManager; }
	virtual CKBehaviorManager* GetBehaviorManager() override { return m_behaviorManager; }
	virtual CKCollisionManager* GetCollisionManager() override { return m_collisionManager; }
	virtual InputHook* GetInputManager() override { return m_inputManager; }
	virtual CKMessageManager* GetMessageManager() override { return m_messageManager; }
	virtual CKPathManager* GetPathManager() override { return m_pathManager; }
	virtual CKParameterManager* GetParameterManager() override { return m_parameterManager; }
	virtual CKRenderManager* GetRenderManager() override { return m_renderManager; }
	virtual CKSoundManager* GetSoundManager() override { return m_soundManager; }
	virtual CKTimeManager* GetTimeManager() override { return m_timeManager; }

	void OpenModsMenu();
	void OnModifyConfig(IMod* mod, CKSTRING category, CKSTRING key, IProperty* prop) { mod->OnModifyConfig(category, key, prop); }
	void ExecuteCommand(CKSTRING cmd);
	std::string TabCompleteCommand(CKSTRING cmd);

	void AddDataPath(const std::filesystem::path &path);
	void PreloadMods();
	void RegisterModBBs(XObjectDeclarationArray* reg);

	virtual void OnPreStartMenu() override;
	virtual void OnPostStartMenu() override;
	virtual void OnExitGame() override;
	virtual void OnPreLoadLevel() override;
	virtual void OnPostLoadLevel() override;
	virtual void OnStartLevel() override;
	virtual void OnPreResetLevel() override;
	virtual void OnPostResetLevel() override;
	virtual void OnPauseLevel() override;
	virtual void OnUnpauseLevel() override;
	virtual void OnPreExitLevel() override;
	virtual void OnPostExitLevel() override;
	virtual void OnPreNextLevel() override;
	virtual void OnPostNextLevel() override;
	virtual void OnDead() override;
	virtual void OnPreEndLevel() override;
	virtual void OnPostEndLevel() override;

	virtual void OnCounterActive() override;
	virtual void OnCounterInactive() override;
	virtual void OnBallNavActive() override;
	virtual void OnBallNavInactive() override;
	virtual void OnCamNavActive() override;
	virtual void OnCamNavInactive() override;
	virtual void OnBallOff() override;
	virtual void OnPreCheckpointReached() override;
	virtual void OnPostCheckpointReached() override;
	virtual void OnLevelFinish() override;
	virtual void OnGameOver() override;
	virtual void OnExtraPoint() override;
	virtual void OnPreSubLife() override;
	virtual void OnPostSubLife() override;
	virtual void OnPreLifeUp() override;
	virtual void OnPostLifeUp() override;

	virtual void AddTimer(CKDWORD delay, std::function<void()> callback) override;
	virtual void AddTimerLoop(CKDWORD delay, std::function<bool()> callback) override;
	virtual void AddTimer(float delay, std::function<void()> callback) override;
	virtual void AddTimerLoop(float delay, std::function<bool()> callback) override;

	virtual bool IsCheatEnabled() override;
	virtual void EnableCheat(bool enable) override;

	virtual void SendIngameMessage(CKSTRING msg) override;

	virtual void RegisterCommand(ICommand* cmd) override;

	virtual void SetIC(CKBeObject* obj, bool hierarchy = false) override;
	virtual void RestoreIC(CKBeObject* obj, bool hierarchy = false) override;
	virtual void Show(CKBeObject* obj, CK_OBJECT_SHOWOPTION show, bool hierarchy = false) override;

	virtual bool IsIngame() override { return m_ingame; }
	virtual bool IsPaused() override { return m_paused; }
	virtual bool IsPlaying() override { return m_ingame && !m_paused; }

	virtual CKDataArray* GetArrayByName(CKSTRING name) override {
		return static_cast<CKDataArray*>(m_context->GetObjectByNameAndClass(name, CKCID_DATAARRAY)); }
	virtual CKGroup* GetGroupByName(CKSTRING name) override {
		return static_cast<CKGroup*>(m_context->GetObjectByNameAndClass(name, CKCID_GROUP)); }
	virtual CKMaterial* GetMaterialByName(CKSTRING name) override {
		return static_cast<CKMaterial*>(m_context->GetObjectByNameAndClass(name, CKCID_MATERIAL)); }
	virtual CKMesh* GetMeshByName(CKSTRING name) override {
		return static_cast<CKMesh*>(m_context->GetObjectByNameAndClass(name, CKCID_MESH)); }
	virtual CK2dEntity* Get2dEntityByName(CKSTRING name) override {
		return static_cast<CK2dEntity*>(m_context->GetObjectByNameAndClass(name, CKCID_2DENTITY)); }
	virtual CK3dEntity* Get3dEntityByName(CKSTRING name) override {
		return static_cast<CK3dEntity*>(m_context->GetObjectByNameAndClass(name, CKCID_3DENTITY)); }
	virtual CK3dObject* Get3dObjectByName(CKSTRING name) override {
		return static_cast<CK3dObject*>(m_context->GetObjectByNameAndClass(name, CKCID_3DOBJECT)); }
	virtual CKCamera* GetCameraByName(CKSTRING name) override {
		return static_cast<CKCamera*>(m_context->GetObjectByNameAndClass(name, CKCID_CAMERA)); }
	virtual CKTargetCamera* GetTargetCameraByName(CKSTRING name) override {
		return static_cast<CKTargetCamera*>(m_context->GetObjectByNameAndClass(name, CKCID_TARGETCAMERA)); }
	virtual CKLight* GetLightByName(CKSTRING name) override {
		return static_cast<CKLight*>(m_context->GetObjectByNameAndClass(name, CKCID_LIGHT)); }
	virtual CKTargetLight* GetTargetLightByName(CKSTRING name) override {
		return static_cast<CKTargetLight*>(m_context->GetObjectByNameAndClass(name, CKCID_TARGETLIGHT)); }
	virtual CKSound* GetSoundByName(CKSTRING name) override {
		return static_cast<CKSound*>(m_context->GetObjectByNameAndClass(name, CKCID_SOUND)); }
	virtual CKTexture* GetTextureByName(CKSTRING name) override {
		return static_cast<CKTexture*>(m_context->GetObjectByNameAndClass(name, CKCID_TEXTURE)); }
	virtual CKBehavior* GetScriptByName(CKSTRING name) override {
		return static_cast<CKBehavior*>(m_context->GetObjectByNameAndClass(name, CKCID_BEHAVIOR)); }

	virtual void RegisterBallType(CKSTRING ballFile, CKSTRING ballId, CKSTRING ballName, CKSTRING objName, float friction, float elasticity,
		float mass, CKSTRING collGroup, float linearDamp, float rotDamp, float force, float radius) override;
	virtual void RegisterFloorType(CKSTRING floorName, float friction, float elasticity, float mass, CKSTRING collGroup, bool enableColl) override;
	virtual void RegisterModulBall(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp, float radius) override;
	virtual void RegisterModulConvex(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
		bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp) override;
	virtual void RegisterTrafo(CKSTRING modulName) override;
	virtual void RegisterModul(CKSTRING modulName) override;

	virtual int GetModCount() override;
	virtual IMod* GetMod(int index) override;

	virtual float GetSRScore() override;
	virtual int GetHSScore() override;

private:
	bool m_inited = false;
	bool m_exiting = false;

	FILE* m_logfile = nullptr;
	ILogger* m_logger = nullptr;

	CKContext* m_context = nullptr;
	CKRenderContext* m_renderContext = nullptr;

	CKAttributeManager* m_attributeManager = nullptr;
	CKBehaviorManager* m_behaviorManager = nullptr;
	CKCollisionManager* m_collisionManager = nullptr;
	InputHook* m_inputManager = nullptr;
	CKMessageManager* m_messageManager = nullptr;
	CKPathManager* m_pathManager = nullptr;
	CKParameterManager* m_parameterManager = nullptr;
	CKRenderManager* m_renderManager = nullptr;
	CKSoundManager* m_soundManager = nullptr;
	CKTimeManager* m_timeManager = nullptr;

	BMLMod* m_bmlmod;
	NewBallTypeMod* m_ballTypeMod;
	bool m_cheatEnabled = false;
	std::vector<IMod*> m_mods;
	std::vector<Config*> m_configs;
	std::list<Timer> m_timers;
	std::vector<ICommand*> m_cmds;
	std::map<std::string, ICommand*> m_cmdm;

	struct PreloadMod {
		std::string dllPath;
		std::string modPath;
		HMODULE handle;
		EntryFunc entry;
		RegisterBBFunc registerBB;
	};
	std::vector<PreloadMod> m_preloadMods;

	typedef int (*BuildingBoxFunc)(const CKBehaviorContext& behcontext);
	static int ObjectLoader(const CKBehaviorContext& behcontext);
	static int Physicalize(const CKBehaviorContext& behcontext);
	BuildingBoxFunc m_objectLoader, m_physicalize;

	void GetContextsAndManagers();
	ICommand* FindCommand(const std::string& name);

	bool m_ingame = false, m_paused = false;

	std::map<void*, std::vector<IMod*>> m_callback_map;
	void FillCallbackMap(IMod* mod);

	template<typename T>
	void BroadcastCallback(T func, std::function<void(IMod*)> callback) {
		for (IMod* mod : m_callback_map[func_addr(func)])
			callback(mod);
	}

	template<typename T>
	void BroadcastMessage(CKSTRING msg, T func) {
		m_logger->Info("On Message %s", msg);
		BroadcastCallback(func, func);
	}
};

class Player {
public:
	CKERROR Step();
	CKERROR Process();
	CKERROR Render(CK_RENDER_FLAGS flags);

	typedef CKERROR(Player::* StepFunc)();
	static StepFunc m_step;
	typedef CKERROR(Player::* RenderFunc)(CK_RENDER_FLAGS);
};
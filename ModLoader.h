#pragma once

#include "IBML.h"
#include <cstdio>
#include <Windows.h>
#include "virtools/CKAll.h"
#include <vector>
#include "IMod.h"
#include "Config.h"

class ModLoader : public IBML {
	friend class BMLMod;
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

	static void WriteMemory(LPVOID dest, LPVOID src, int len);

	virtual CKContext* GetCKContext() override { return m_context; }
	virtual CKRenderContext* GetRenderContext() override { return m_renderContext; }

	virtual void ExitGame() override { m_exiting = true; }

	virtual CKAttributeManager* GetAttributeManager() override { return m_attributeManager; }
	virtual CKBehaviorManager* GetBehaviorManager() override { return m_behaviorManager; }
	virtual CKCollisionManager* GetCollisionManager() override { return m_collisionManager; }
	virtual CKInputManager* GetInputManager() override { return m_inputManager; }
	virtual CKMessageManager* GetMessageManager() override { return m_messageManager; }
	virtual CKParameterManager* GetParameterManager() override { return m_parameterManager; }
	virtual CKRenderManager* GetRenderManager() override { return m_renderManager; }
	virtual CKSoundManager* GetSoundManager() override { return m_soundManager; }
	virtual CKTimeManager* GetTimeManager() override { return m_timeManager; }

	void OpenModsMenu();

	void OnModifyConfig(IMod* mod, CKSTRING category, CKSTRING key, IProperty* prop) { mod->OnModifyConfig(category, key, prop); }
	virtual void OnStartMenu() override;

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
	CKInputManager* m_inputManager = nullptr;
	CKMessageManager* m_messageManager = nullptr;
	CKParameterManager* m_parameterManager = nullptr;
	CKRenderManager* m_renderManager = nullptr;
	CKSoundManager* m_soundManager = nullptr;
	CKTimeManager* m_timeManager = nullptr;

	std::vector<IMod*> m_mods;
	std::vector<Config*> m_configs;

	static int ObjectLoader(const CKBehaviorContext& behcontext);
	typedef int (*ObjectLoaderFunc)(const CKBehaviorContext& behcontext);
	ObjectLoaderFunc m_objectLoader;

	void GetContextsAndManagers();
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
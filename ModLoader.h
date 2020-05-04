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

class BMLMod;

class ModLoader : public IBML {
	friend class BMLMod;
	friend class CommandBML;
	friend class CommandHelp;
	friend class CommandCheat;
	friend class CommandClear;
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
	virtual CKParameterManager* GetParameterManager() override { return m_parameterManager; }
	virtual CKRenderManager* GetRenderManager() override { return m_renderManager; }
	virtual CKSoundManager* GetSoundManager() override { return m_soundManager; }
	virtual CKTimeManager* GetTimeManager() override { return m_timeManager; }

	void OpenModsMenu();
	void OnModifyConfig(IMod* mod, CKSTRING category, CKSTRING key, IProperty* prop) { mod->OnModifyConfig(category, key, prop); }
	void ExecuteCommand(CKSTRING cmd);
	std::string TabCompleteCommand(CKSTRING cmd);

	virtual void OnStartMenu() override;
	virtual void OnExitGame() override;
	virtual void OnLoadLevel() override;
	virtual void OnStartLevel() override;
	virtual void OnResetLevel() override;
	virtual void OnPauseLevel() override;
	virtual void OnUnpauseLevel() override;
	virtual void OnExitLevel() override;
	virtual void OnNextLevel() override;
	virtual void OnDead() override;
	virtual void OnEndLevel() override;

	virtual void AddTimer(CKDWORD delay, std::function<void()> callback) override;
	virtual void AddTimer(CKDWORD delay, std::function<bool()> callback) override;
	virtual void AddTimer(float delay, std::function<void()> callback) override;
	virtual void AddTimer(float delay, std::function<bool()> callback) override;

	virtual bool IsCheatEnabled() override;
	virtual void EnableCheat(bool enable) override;

	virtual void SendIngameMessage(CKSTRING msg) override;

	virtual void RegisterCommand(ICommand* cmd) override;

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
	CKParameterManager* m_parameterManager = nullptr;
	CKRenderManager* m_renderManager = nullptr;
	CKSoundManager* m_soundManager = nullptr;
	CKTimeManager* m_timeManager = nullptr;

	BMLMod* m_bmlmod;
	bool m_cheatEnabled = false;
	std::vector<IMod*> m_mods;
	std::vector<Config*> m_configs;
	std::list<Timer> m_timers;
	std::vector<ICommand*> m_cmds;
	std::map<std::string, ICommand*> m_cmdm;

	static int ObjectLoader(const CKBehaviorContext& behcontext);
	typedef int (*ObjectLoaderFunc)(const CKBehaviorContext& behcontext);
	ObjectLoaderFunc m_objectLoader;

	void GetContextsAndManagers();
	ICommand* FindCommand(const std::string& name);
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
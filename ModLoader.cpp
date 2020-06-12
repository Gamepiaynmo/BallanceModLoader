#include "BMLAll.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "BMLMod.h"
#include "ExecuteBB.h"
#include <ImageHlp.h>
#include <ctime>
#include "NewBallTypeMod.h"
#include "Logger.h"
#include <filesystem>
#include "zip/unzip.h"

Player::StepFunc Player::m_step = &Player::Step;

std::vector<std::string> SplitString(const std::string& str, const std::string& de) {
	size_t lpos, pos = 0;
	std::vector<std::string> res;

	lpos = str.find_first_not_of(de, pos);
	while (lpos != std::string::npos) {
		pos = str.find_first_of(de, lpos);
		res.push_back(str.substr(lpos, pos - lpos));
		if (pos == std::string::npos) break;

		lpos = str.find_first_not_of(de, pos);
	}

	if (pos != std::string::npos)
		res.push_back("");

	return res;
}

bool StartWith(const std::string& str, const std::string& start) {
	return str.substr(0, start.size()) == start;
}

ModLoader::ModLoader() {
	m_instance = this;

	m_logfile = fopen("..\\ModLoader\\ModLoader.log", "w");
	m_logger = new Logger("ModLoader");
}

ModLoader::~ModLoader() {
	m_instance = nullptr;
}

void ModLoader::AddDataPath(const std::filesystem::path& path) {
	std::filesystem::path abs = std::filesystem::absolute(path);
	std::string texturePath = abs.string() + "\\Textures\\";
	std::string soundPath = abs.string() + "\\Sounds\\";
	m_pathManager->AddPath(DATA_PATH_IDX, (abs.string() + "\\").c_str());
	m_pathManager->AddPath(BITMAP_PATH_IDX, texturePath.c_str());
	m_pathManager->AddPath(SOUND_PATH_IDX, soundPath.c_str());
}

void ModLoader::Init() {
	MakeSureDirectoryPathExists("..\\ModLoader\\Cache\\");
	MakeSureDirectoryPathExists("..\\ModLoader\\Config\\");
	MakeSureDirectoryPathExists("..\\ModLoader\\Maps\\");
	MakeSureDirectoryPathExists("..\\ModLoader\\Mods\\");

	srand((UINT)time(0));

#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	m_logger->Info("Initializing Mod Loader version " BML_VERSION);

	if (MH_Initialize() != MH_OK) {
		m_logger->Error("MinHook Initialize Failed");
		return;
	}

	m_logger->Info("MinHook Initialized");

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x00401BF0),
		*reinterpret_cast<LPVOID*>(&Player::m_step),
		reinterpret_cast<LPVOID*>(&Player::m_step)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x00401BF0)) != MH_OK) {
		m_logger->Error("Create Step Hook Failed");
		return;
	}

	m_logger->Info("Step Hook created");

	if (MH_CreateHook(reinterpret_cast<LPVOID>(0x25681C30), &ObjectLoader,
		reinterpret_cast<LPVOID*>(&m_objectLoader)) != MH_OK
		|| MH_EnableHook(reinterpret_cast<LPVOID>(0x25681C30)) != MH_OK) {
		m_logger->Error("Create Object Loader Hook Failed");
		return;
	}

	m_logger->Info("Object Loader Hook created");

	if (!InputHook::InitHook()) {
		m_logger->Error("Create Input Manager Hooks Failed");
		return;
	}

	m_logger->Info("Input Manager Hooks created");

	GetContextsAndManagers();

	AddDataPath("..\\ModLoader");

	m_logger->Info("Loading Mod Loader");

	Player::StepFunc process = &Player::Process;
	WriteMemory(reinterpret_cast<LPVOID>(0x0040a018), &process, sizeof(process));
	m_logger->Info("Process Function Hooked");

	Player::RenderFunc* render = new Player::RenderFunc(&Player::Render);
	BYTE jmpAddr[6] = { 0xff, 0x25 };
	*reinterpret_cast<Player::RenderFunc**>(jmpAddr + 2) = render;
	WriteMemory(reinterpret_cast<LPVOID>(0x00409B86), &jmpAddr, sizeof(jmpAddr));
	BYTE jmpFunc[5] = { 0xE8, 0x18, 0x43 };
	WriteMemory(reinterpret_cast<LPVOID>(0x00405869), &jmpFunc, sizeof(jmpFunc));
	m_logger->Info("Render Function Hooked");

	m_inited = true;
}

void ModLoader::Release() {
	m_inited = false;

	for (IMod* mod : m_instance->m_mods)
		mod->OnUnload();

	for (Config* config : m_instance->m_configs)
		config->Save();
	m_instance->m_configs.clear();

	for (IMod* mod : m_instance->m_mods)
		delete mod;
	m_instance->m_mods.clear();

	m_logger->Info("Unloading Mod Loader");

	m_logger->Info("Releasing Mod Loader");

	if (MH_Uninitialize() != MH_OK)
		m_logger->Warn("MinHook Uninitialize Failed");
	else m_logger->Info("MinHook Uninitialized");

#ifdef _DEBUG
	FreeConsole();
#endif

	m_logger->Info("Goodbye!");

	delete m_logger;
	fclose(m_logfile);
}

void ModLoader::GetContextsAndManagers() {
	m_context = ::GetCKContext(0);
	m_logger->Info("Get CKContext pointer 0x%08x", m_context);

	m_attributeManager = m_context->GetAttributeManager();
	m_logger->Info("Get Attribute Manager pointer 0x%08x", m_attributeManager);

	m_behaviorManager = m_context->GetBehaviorManager();
	m_logger->Info("Get Behavior Manager pointer 0x%08x", m_behaviorManager);

	m_collisionManager = static_cast<CKCollisionManager*>(m_context->GetManagerByGuid(COLLISION_MANAGER_GUID));
	m_logger->Info("Get Collision Manager pointer 0x%08x", m_collisionManager);

	m_inputManager = static_cast<InputHook*>(m_context->GetManagerByGuid(INPUT_MANAGER_GUID));
	m_logger->Info("Get Input Manager pointer 0x%08x", m_inputManager);

	m_messageManager = m_context->GetMessageManager();
	m_logger->Info("Get Message Manager pointer 0x%08x", m_messageManager);

	m_pathManager = m_context->GetPathManager();
	m_logger->Info("Get Path Manager pointer 0x%08x", m_pathManager);

	m_parameterManager = m_context->GetParameterManager();
	m_logger->Info("Get Parameter Manager pointer 0x%08x", m_parameterManager);

	m_soundManager = static_cast<CKSoundManager*>(m_context->GetManagerByGuid(SOUND_MANAGER_GUID));
	m_logger->Info("Get Sound Manager pointer 0x%08x", m_soundManager);

	m_timeManager = m_context->GetTimeManager();
	m_logger->Info("Get Time Manager pointer 0x%08x", m_timeManager);
}

// Game Loop
CKERROR Player::Step() {
	return ModLoader::m_instance->Step((this->*m_step)());
}

// Game Tick
CKERROR Player::Process() {
	CKERROR result = ModLoader::m_instance->GetCKContext()->Process();
	ModLoader::m_instance->Process(result);
	return result;
}

// Render Tick
CKERROR Player::Render(CK_RENDER_FLAGS flags) {
	CKERROR result = ModLoader::m_instance->GetRenderContext()->Render(flags);
	ModLoader::m_instance->Render(flags, result);
	return result;
}

CKERROR ModLoader::Step(CKDWORD result) {
	if (result) {
		if (!m_renderContext) {
			m_renderContext = m_context->GetPlayerRenderContext();
			m_logger->Info("Get Render Context pointer 0x%08x", m_renderContext);

			m_renderManager = m_context->GetRenderManager();
			m_logger->Info("Get Render Manager pointer 0x%08x", m_renderManager);

			ExecuteBB::Init(m_context);

			m_bmlmod = new BMLMod(this);
			m_mods.push_back(m_bmlmod);

			m_ballTypeMod = new NewBallTypeMod(this);
			m_mods.push_back(m_ballTypeMod);

			for (auto& mod : m_preloadMods) {
				if (mod.entry) {
					m_mods.push_back(mod.entry(this));
					if (!mod.modPath.empty())
						AddDataPath(mod.modPath);
				}
			}

/*
#ifdef _DEBUG
			class TestMod : public IMod {
			public:
				TestMod(IBML* bml, int id) : IMod(bml), m_id(id) {
					m_modid = "mod" + std::to_string(m_id);
					m_name = "Mod #" + std::to_string(m_id);
				}
				virtual CKSTRING GetID() override { return m_modid.c_str(); }
				virtual CKSTRING GetVersion() override { return "1.0"; }
				virtual CKSTRING GetName() override { return m_name.c_str(); }
				virtual CKSTRING GetAuthor() override { return "Gamepiaynmo"; }
				virtual CKSTRING GetDescription() override { return "Test Mod Description"; }
			private:
				int m_id;
				std::string m_modid, m_name;
			};

			for (int i = 1; i < 10; i++)
				m_mods.push_back(new TestMod(this, i));
#endif
*/

			for (IMod* mod : m_instance->m_mods) {
				m_logger->Info("Loading Mod %s[%s] v%s by %s", mod->GetID(), mod->GetName(), mod->GetVersion(), mod->GetAuthor());
				mod->OnLoad();
			}

			std::sort(m_cmds.begin(), m_cmds.end(), [](ICommand* A, ICommand* B) {
				return A->GetName() < B->GetName();
				});

			for (Config* config : m_instance->m_configs)
				config->Save();

			int scriptCnt = m_context->GetObjectsCountByClassID(CKCID_BEHAVIOR);
			CK_ID* scripts = m_context->GetObjectsListByClassID(CKCID_BEHAVIOR);
			for (int i = 0; i < scriptCnt; i++) {
				CKBehavior* beh = static_cast<CKBehavior*>(m_context->GetObject(scripts[i]));
				if (beh->GetType() == CKBEHAVIORTYPE_SCRIPT)
					for (IMod* mod : m_instance->m_mods)
						mod->OnLoadScript("base.cmo", beh);
			}
		}

		return !m_exiting;
	}

	return result;
}

void ModLoader::PreloadMods() {
	for (auto& i : std::filesystem::directory_iterator("..\\ModLoader\\Cache"))
		std::filesystem::remove_all(i.path());

	for (auto& f : std::filesystem::directory_iterator("..\\ModLoader\\Mods")) {
		std::filesystem::path ext = f.path().extension();
		PreloadMod mod;

		if (f.status().type() == std::filesystem::file_type::regular) {
			if (ext == ".bmod") {
				mod.dllPath = f.path().string();
			}
			else if (ext == ".zip") {
				HZIP hz = OpenZip(f.path().string().c_str(), 0);
				ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
				std::string filepath = "..\\ModLoader\\Cache\\" + f.path().filename().string() + "\\";
				mod.modPath = filepath;
				for (int zi = 0; zi < numitems; zi++) {
					ZIPENTRY ze; GetZipItem(hz, zi, &ze);
					std::string path = filepath + ze.name;
					UnzipItem(hz, zi, path.c_str());

					if (!(ze.attr & FILE_ATTRIBUTE_DIRECTORY) &&
						std::filesystem::path(path).extension() == ".bmod")
						mod.dllPath = path;
				}
				CloseZip(hz);
			}
		}
		else if (f.status().type() == std::filesystem::file_type::directory) {
			mod.modPath = f.path().string();
			for (auto& m : std::filesystem::directory_iterator(f.path())) {
				if (m.status().type() == std::filesystem::file_type::regular
					&& m.path().extension() == ".bmod")
					mod.dllPath = m.path().string();
			}
		}

		mod.handle = LoadLibrary(mod.dllPath.c_str());
		mod.entry = reinterpret_cast<EntryFunc>(GetProcAddress(mod.handle, "BMLEntry"));
		mod.registerBB = reinterpret_cast<RegisterBBFunc>(GetProcAddress(mod.handle, "RegisterBB"));
		if (mod.entry || mod.registerBB)
			m_preloadMods.push_back(mod);
	}
}

void ModLoader::RegisterModBBs(XObjectDeclarationArray* reg) {
	for (auto& mod : m_preloadMods) {
		if (mod.registerBB)
			mod.registerBB(reg);
	}
}

void ModLoader::Process(CKERROR result) {
	for (auto iter = m_timers.begin(); iter != m_timers.end(); ) {
		if (!iter->Process(m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()))
			iter = m_timers.erase(iter);
		else iter++;
	}

	for (IMod* mod : m_instance->m_mods)
		mod->OnProcess();

	m_inputManager->Process();
}

void ModLoader::Render(CK_RENDER_FLAGS flags, CKERROR result) {
	for (IMod* mod : m_instance->m_mods)
		mod->OnRender(flags);
}

int ModLoader::ObjectLoader(const CKBehaviorContext& behcontext) {
	CKBehavior* beh = behcontext.Behavior;
	CKContext* ctx = behcontext.Context;
	bool active = beh->IsInputActive(0);

	int result = m_instance->m_objectLoader(behcontext);

	if (active) {
		CKSTRING filename = (CKSTRING)beh->GetInputParameterReadDataPtr(0);
		CKSTRING mastername = (CKSTRING)beh->GetInputParameterReadDataPtr(1);
		CK_CLASSID cid = CKCID_3DOBJECT;
		beh->GetInputParameterValue(2, &cid);
		BOOL addtoscene = TRUE, reuseMeshes = FALSE, reuseMaterials = FALSE;
		beh->GetInputParameterValue(3, &addtoscene);
		beh->GetInputParameterValue(4, &reuseMeshes);
		beh->GetInputParameterValue(5, &reuseMaterials);

		BOOL dynamic = TRUE;
		beh->GetLocalParameterValue(0, &dynamic);

		XObjectArray* oarray = *(XObjectArray**)beh->GetOutputParameterWriteDataPtr(0);
		CKObject* masterobject = NULL;
		beh->GetOutputParameterObject(1);

		for (IMod* mod : m_instance->m_mods)
			mod->OnLoadObject(filename, mastername, cid, addtoscene, reuseMeshes, reuseMaterials, dynamic, oarray, masterobject);
		for (CK_ID* id = oarray->Begin(); id != oarray->End(); id++) {
			CKObject* obj = m_instance->m_context->GetObject(*id);
			if (obj->GetClassID() == CKCID_BEHAVIOR) {
				CKBehavior* beh = static_cast<CKBehavior*>(obj);
				if (beh->GetType() == CKBEHAVIORTYPE_SCRIPT)
					for (IMod* mod : m_instance->m_mods)
						mod->OnLoadScript(filename, beh);
			}
		}
	}

	return result;
}

void ModLoader::WriteMemory(LPVOID dest, LPVOID src, int len) {
	DWORD oldFlag;
	VirtualProtect(dest, len, PAGE_EXECUTE_READWRITE, &oldFlag);
	memcpy(dest, src, len);
	VirtualProtect(dest, len, oldFlag, &oldFlag);
}

Config* ModLoader::GetConfig(IMod* mod) {
	for (Config* cfg : m_configs) {
		if (cfg->GetMod() == mod)
			return cfg;
	}

	return nullptr;
}

void ModLoader::OpenModsMenu() {
	m_logger->Info("Open Mods Menu");
	m_bmlmod->ShowModOptions();
}

void ModLoader::OnPreStartMenu() {
	BoardcastMessage("PreStartMenu", &IMod::OnPreStartMenu);
}

void ModLoader::OnPostStartMenu() {
	BoardcastMessage("PostStartMenu", &IMod::OnPostStartMenu);
}

void ModLoader::OnExitGame() {
	BoardcastMessage("ExitGame", &IMod::OnExitGame);
}

void ModLoader::OnPreLoadLevel() {
	BoardcastMessage("PreLoadLevel", &IMod::OnPreLoadLevel);
}

void ModLoader::OnPostLoadLevel() {
	BoardcastMessage("PostLoadLevel", &IMod::OnPostLoadLevel);
}

void ModLoader::OnStartLevel() {
	BoardcastMessage("StartLevel", &IMod::OnStartLevel);
	m_ingame = true;
	m_paused = false;
}

void ModLoader::OnPreResetLevel() {
	BoardcastMessage("PreResetLevel", &IMod::OnPreResetLevel);
}

void ModLoader::OnPostResetLevel() {
	BoardcastMessage("PostResetLevel", &IMod::OnPostResetLevel);
}

void ModLoader::OnPauseLevel() {
	BoardcastMessage("PauseLevel", &IMod::OnPauseLevel);
	m_paused = true;
}

void ModLoader::OnUnpauseLevel() {
	BoardcastMessage("UnpauseLevel", &IMod::OnUnpauseLevel);
	m_paused = false;
}

void ModLoader::OnPreExitLevel() {
	BoardcastMessage("PreExitLevel", &IMod::OnPreExitLevel);
}

void ModLoader::OnPostExitLevel() {
	BoardcastMessage("PostExitLevel", &IMod::OnPostExitLevel);
	m_ingame = false;
}

void ModLoader::OnPreNextLevel() {
	BoardcastMessage("PreNextLevel", &IMod::OnPreNextLevel);
}

void ModLoader::OnPostNextLevel() {
	BoardcastMessage("PostNextLevel", &IMod::OnPostNextLevel);
}

void ModLoader::OnDead() {
	BoardcastMessage("Dead", &IMod::OnDead);
	m_ingame = false;
}

void ModLoader::OnPreEndLevel() {
	BoardcastMessage("PreEndLevel", &IMod::OnPreEndLevel);
}

void ModLoader::OnPostEndLevel() {
	BoardcastMessage("PostEndLevel", &IMod::OnPostEndLevel);
	m_ingame = false;
}

void ModLoader::OnCounterActive() {
	BoardcastMessage("CounterActive", &IMod::OnCounterActive);
}

void ModLoader::OnCounterInactive() {
	BoardcastMessage("CounterInactive", &IMod::OnCounterInactive);
}

void ModLoader::OnBallNavActive() {
	BoardcastMessage("BallNavActive", &IMod::OnBallNavActive);
}

void ModLoader::OnBallNavInactive() {
	BoardcastMessage("BallNavInactive", &IMod::OnBallNavInactive);
}

void ModLoader::OnCamNavActive() {
	BoardcastMessage("CamNavActive", &IMod::OnCamNavActive);
}

void ModLoader::OnCamNavInactive() {
	BoardcastMessage("CamNavInactive", &IMod::OnCamNavInactive);
}

void ModLoader::OnBallOff() {
	BoardcastMessage("BallOff", &IMod::OnBallOff);
}

void ModLoader::OnPreCheckpointReached() {
	BoardcastMessage("PreCheckpoint", &IMod::OnPreCheckpointReached);
}

void ModLoader::OnPostCheckpointReached() {
	BoardcastMessage("PostCheckpoint", &IMod::OnPostCheckpointReached);
}

void ModLoader::OnLevelFinish() {
	BoardcastMessage("LevelFinish", &IMod::OnLevelFinish);
}

void ModLoader::OnGameOver() {
	BoardcastMessage("GameOver", &IMod::OnGameOver);
}

void ModLoader::OnExtraPoint() {
	BoardcastMessage("ExtraPoint", &IMod::OnExtraPoint);
}

void ModLoader::OnPreSubLife() {
	BoardcastMessage("PreSubLife", &IMod::OnPreSubLife);
}

void ModLoader::OnPostSubLife() {
	BoardcastMessage("PostSubLife", &IMod::OnPostSubLife);
}

void ModLoader::OnPreLifeUp() {
	BoardcastMessage("PreLifeUp", &IMod::OnPreLifeUp);
}

void ModLoader::OnPostLifeUp() {
	BoardcastMessage("PostLifeUp", &IMod::OnPostLifeUp);
}

void ModLoader::AddTimer(CKDWORD delay, std::function<void()> callback) {
	m_timers.push_back(Timer(delay, callback, m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()));
}

void ModLoader::AddTimerLoop(CKDWORD delay, std::function<bool()> callback) {
	m_timers.push_back(Timer(delay, callback, m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()));
}

void ModLoader::AddTimer(float delay, std::function<void()> callback) {
	m_timers.push_back(Timer(delay, callback, m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()));
}

void ModLoader::AddTimerLoop(float delay, std::function<bool()> callback) {
	m_timers.push_back(Timer(delay, callback, m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()));
}

void ModLoader::SendIngameMessage(CKSTRING msg) {
	m_bmlmod->AddIngameMessage(msg);
}

void ModLoader::RegisterCommand(ICommand* cmd) {
	m_cmds.push_back(cmd);

	auto iter = m_cmdm.find(cmd->GetName());
	if (iter == m_cmdm.end())
		m_cmdm[cmd->GetName()] = cmd;
	else m_logger->Warn("Command Name Conflict: %s is redefined.", cmd->GetName());

	if (!cmd->GetAlias().empty()) {
		auto iter = m_cmdm.find(cmd->GetAlias());
		if (iter == m_cmdm.end())
			m_cmdm[cmd->GetAlias()] = cmd;
		else m_logger->Warn("Command Alias Conflict: %s is redefined.", cmd->GetAlias());
	}
}

ICommand* ModLoader::FindCommand(const std::string& name) {
	auto iter = m_cmdm.find(name);
	if (iter == m_cmdm.end()) return nullptr;
	return !iter->second->IsCheat() || m_cheatEnabled ? iter->second : nullptr;
}

void ModLoader::ExecuteCommand(CKSTRING cmd) {
	m_logger->Info("Execute Command: %s", cmd);
	std::vector<std::string> args = SplitString(cmd, " ");
	ICommand* command = FindCommand(args[0]);
	if (command) command->Execute(this, args);
	else m_bmlmod->AddIngameMessage(("Error: Unknown Command " + args[0]).c_str());
}

std::string ModLoader::TabCompleteCommand(CKSTRING cmd) {
	std::vector<std::string> args = SplitString(cmd, " ");
	std::vector<std::string> res;
	if (args.size() == 1) {
		for (auto& p : m_cmdm) {
			if (StartWith(p.first, args[0])) {
				if (!p.second->IsCheat() || m_cheatEnabled)
					res.push_back(p.first);
			}
		}
	}
	else {
		ICommand* command = FindCommand(args[0]);
		if (command) {
			for (const std::string& str : command->GetTabCompletion(this, args))
				if (StartWith(str, args[args.size() - 1]))
					res.push_back(str);
		}
	}

	if (res.size() == 0) return cmd;
	if (res.size() == 1) {
		if (args.size() == 1) return res[0];
		else {
			std::string str(cmd);
			str = str.substr(0, str.size() - args[args.size() - 1].size());
			str += res[0];
			return str;
		}
	}

	std::string str = res[0];
	for (unsigned int i = 1; i < res.size(); i++)
		str += ", " + res[i];
	m_bmlmod->AddIngameMessage(str.c_str());
	return cmd;
}

bool ModLoader::IsCheatEnabled() {
	return m_cheatEnabled;
}

void ModLoader::EnableCheat(bool enable) {
	m_cheatEnabled = enable;
	m_bmlmod->ShowCheatBanner(enable);
	for (IMod* mod : m_mods)
		mod->OnCheatEnabled(enable);
}

void ModLoader::SetIC(CKBeObject* obj, bool hierarchy) {
	m_context->GetCurrentScene()->SetObjectInitialValue(obj, CKSaveObjectState(obj));

	if (hierarchy) {
		if (CKIsChildClassOf(obj, CKCID_2DENTITY)) {
			CK2dEntity* entity = static_cast<CK2dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				SetIC(entity->GetChild(i), true);
		}
		if (CKIsChildClassOf(obj, CKCID_3DENTITY)) {
			CK3dEntity* entity = static_cast<CK3dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				SetIC(entity->GetChild(i), true);
		}
	}
}

void ModLoader::RestoreIC(CKBeObject* obj, bool hierarchy) {
	CKStateChunk* chunk = m_context->GetCurrentScene()->GetObjectInitialValue(obj);
	if (chunk) CKReadObjectState(obj, chunk);

	if (hierarchy) {
		if (CKIsChildClassOf(obj, CKCID_2DENTITY)) {
			CK2dEntity* entity = static_cast<CK2dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				RestoreIC(entity->GetChild(i), true);
		}
		if (CKIsChildClassOf(obj, CKCID_3DENTITY)) {
			CK3dEntity* entity = static_cast<CK3dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				RestoreIC(entity->GetChild(i), true);
		}
	}
}

void ModLoader::Show(CKBeObject* obj, CK_OBJECT_SHOWOPTION show, bool hierarchy) {
	obj->Show(show);

	if (hierarchy) {
		if (CKIsChildClassOf(obj, CKCID_2DENTITY)) {
			CK2dEntity* entity = static_cast<CK2dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				Show(entity->GetChild(i), show, true);
		}
		if (CKIsChildClassOf(obj, CKCID_3DENTITY)) {
			CK3dEntity* entity = static_cast<CK3dEntity*>(obj);
			for (int i = 0; i < entity->GetChildrenCount(); i++)
				Show(entity->GetChild(i), show, true);
		}
	}
}
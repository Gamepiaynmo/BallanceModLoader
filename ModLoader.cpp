#include "BMLAll.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "BMLMod.h"
#include "ExecuteBB.h"
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

void ToLower(std::string& data) {
	std::transform(data.begin(), data.end(), data.begin(),
								 [](unsigned char c) { return std::tolower(c); });
}

bool StartWith(const std::string& str, const std::string& start) {
	return str.substr(0, start.size()) == start;
}

ModLoader::ModLoader() {
	m_instance = this;

	std::filesystem::create_directories("..\\ModLoader\\");
	std::filesystem::create_directories("..\\ModLoader\\Cache\\");
	std::filesystem::create_directories("..\\ModLoader\\Config\\");
	std::filesystem::create_directories("..\\ModLoader\\Maps\\");
	std::filesystem::create_directories("..\\ModLoader\\Mods\\");

	for (auto& i : std::filesystem::directory_iterator("..\\ModLoader\\Cache"))
		std::filesystem::remove_all(i.path());

	std::filesystem::create_directories("..\\ModLoader\\Cache\\Maps");
	std::filesystem::create_directories("..\\ModLoader\\Cache\\Mods");

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
	srand((UINT)time(0));

#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	m_logger->Info("Initializing Mod Loader version " BML_VERSION);
	m_logger->Info("Website: https://github.com/Gamepiaynmo/BallanceModLoader");

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

#ifdef _DEBUG
	m_logger->Info("Player.exe Address: 0x%08x", GetModuleHandle("Player.exe"));
	m_logger->Info("CK2.dll Address: 0x%08x", GetModuleHandle("CK2.dll"));
	m_logger->Info("VxMath.dll Address: 0x%08x", GetModuleHandle("VxMath.dll"));
#endif

	HMODULE narratives = GetModuleHandle("Narratives.dll");
	if (narratives == nullptr) {
		m_logger->Error("Get Narratives Address Failed");
		return;
	}

	LPVOID objectLoadAddr = reinterpret_cast<LPBYTE>(narratives) + 0x1C30;
	if (MH_CreateHook(objectLoadAddr, &ObjectLoader,
		reinterpret_cast<LPVOID*>(&m_objectLoader)) != MH_OK
		|| MH_EnableHook(objectLoadAddr) != MH_OK) {
		m_logger->Error("Create Object Loader Hook Failed");
		return;
	}

	m_logger->Info("Object Loader Hook created");

	HMODULE physics_RT = GetModuleHandle("Physics_RT.dll");
	if (physics_RT == nullptr) {
		m_logger->Error("Get Physics_RT Address Failed");
		return;
	}

	LPVOID physicalizeAddr = reinterpret_cast<BYTE*>(physics_RT) + 0x26B0;
	if (MH_CreateHook(physicalizeAddr, &Physicalize,
		reinterpret_cast<LPVOID*>(&m_physicalize)) != MH_OK
		|| MH_EnableHook(physicalizeAddr) != MH_OK) {
		m_logger->Error("Create Physicalize Hook Failed");
		return;
	}

	m_logger->Info("Physicalize Hook created");

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

	BroadcastMessage("OnUnload", &IMod::OnUnload);

	for (Config* config : m_instance->m_configs)
		config->Save();
	m_instance->m_configs.clear();

	for (IMod* mod : m_instance->m_mods)
		delete mod;
	m_instance->m_mods.clear();

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
	if (!ModLoader::m_instance->IsSkipRender()) {
		CKERROR result = ModLoader::m_instance->GetCKContext()->GetPlayerRenderContext()->Render(flags);
		ModLoader::m_instance->Render(flags, result);
		return result;
	}

	return CK_OK;
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

			BMLVersion curVer;
			for (auto& preload : m_preloadMods) {
				if (preload.entry) {
					IMod* mod = preload.entry(this);
					BMLVersion reqVer = mod->GetBMLVersion();
					if (curVer < reqVer) {
						m_logger->Warn("Mod %s[%s] requires BML %d.%d.%d", mod->GetID(), mod->GetName(), reqVer.major, reqVer.minor, reqVer.build);
						continue;
					}

					m_mods.push_back(mod);
					if (!preload.modPath.empty())
						AddDataPath(preload.modPath);
				}
			}

			for (IMod* mod : m_instance->m_mods) {
				m_logger->Info("Loading Mod %s[%s] v%s by %s", mod->GetID(), mod->GetName(), mod->GetVersion(), mod->GetAuthor());
				FillCallbackMap(mod);
				mod->OnLoad();
			}

			std::sort(m_cmds.begin(), m_cmds.end(), [](ICommand* A, ICommand* B) {
				return A->GetName() < B->GetName();
				});

			for (Config* config : m_instance->m_configs)
				config->Save();

			BroadcastCallback(&IMod::OnLoadObject, std::bind(&IMod::OnLoadObject, std::placeholders::_1, "base.cmo", false,
				"", CKCID_3DOBJECT, true, true, true, false, nullptr, nullptr));
			int scriptCnt = m_context->GetObjectsCountByClassID(CKCID_BEHAVIOR);
			CK_ID* scripts = m_context->GetObjectsListByClassID(CKCID_BEHAVIOR);
			for (int i = 0; i < scriptCnt; i++) {
				CKBehavior* beh = static_cast<CKBehavior*>(m_context->GetObject(scripts[i]));
				if (beh->GetType() == CKBEHAVIORTYPE_SCRIPT)
					BroadcastCallback(&IMod::OnLoadScript, std::bind(&IMod::OnLoadScript, std::placeholders::_1, "base.cmo", beh));
			}
		}

		return !m_exiting;
	}

	return result;
}

void ModLoader::PreloadMods() {
	for (auto& f : std::filesystem::directory_iterator("..\\ModLoader\\Mods")) {
		std::filesystem::path modpath = f.path();
		std::string modext = modpath.extension().string();
		std::transform(modext.begin(), modext.end(), modext.begin(), tolower);
		PreloadMod mod;

		if (f.status().type() == std::filesystem::file_type::regular) {
			if (modext == ".bmod") {
				mod.dllPath = modpath.string();
			}
			else if (modext == ".zip") {
				HZIP hz = OpenZip(modpath.string().c_str(), 0);
				ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
				std::string filepath = "..\\ModLoader\\Cache\\Mods\\" + modpath.filename().string() + "\\";
				mod.modPath = filepath;
				for (int zi = 0; zi < numitems; zi++) {
					ZIPENTRY ze; GetZipItem(hz, zi, &ze);
					std::string path = filepath + ze.name;
					UnzipItem(hz, zi, path.c_str());

					std::string ext = std::filesystem::path(path).extension().string();
					std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
					if (!(ze.attr & FILE_ATTRIBUTE_DIRECTORY) && ext == ".bmod")
						mod.dllPath = path;
				}
				CloseZip(hz);
			}
		}
		else if (f.status().type() == std::filesystem::file_type::directory) {
			mod.modPath = modpath.string();
			for (auto& m : std::filesystem::directory_iterator(modpath)) {
				if (m.status().type() == std::filesystem::file_type::regular) {
					std::string ext = m.path().extension().string();
					std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
					if (ext == ".bmod")
						mod.dllPath = m.path().string();
				}
			}
		}

		mod.handle = LoadLibraryEx(mod.dllPath.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (mod.handle) {
			mod.entry = reinterpret_cast<EntryFunc>(GetProcAddress(mod.handle, "BMLEntry"));
			mod.registerBB = reinterpret_cast<RegisterBBFunc>(GetProcAddress(mod.handle, "RegisterBB"));
			if (mod.entry || mod.registerBB)
				m_preloadMods.push_back(mod);
		}
	}
}

void ModLoader::RegisterModBBs(XObjectDeclarationArray* reg) {
	for (auto& mod : m_preloadMods) {
		if (mod.registerBB)
			mod.registerBB(reg);
	}
}

void ModLoader::Process(CKERROR result) {
	m_skipRender = false;
	for (auto iter = m_timers.begin(); iter != m_timers.end(); ) {
		if (!iter->Process(m_timeManager->GetMainTickCount(), m_timeManager->GetAbsoluteTime()))
			iter = m_timers.erase(iter);
		else iter++;
	}

	BroadcastCallback(&IMod::OnProcess, &IMod::OnProcess);
	if (IsCheatEnabled() && m_skipRenderKey && m_inputManager->IsKeyDown(m_skipRenderKey->GetKey()))
		SkipRenderForNextTick();

	m_inputManager->Process();
}

void ModLoader::Render(CK_RENDER_FLAGS flags, CKERROR result) {
	BroadcastCallback(&IMod::OnRender, std::bind(&IMod::OnRender, std::placeholders::_1, flags));
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
		CKObject* masterobject = beh->GetOutputParameterObject(1);
		BOOL isMap = !strcmp(beh->GetOwnerScript()->GetName(), "Levelinit_build");

		m_instance->BroadcastCallback(&IMod::OnLoadObject, std::bind(&IMod::OnLoadObject, std::placeholders::_1, filename, isMap,
			mastername, cid, addtoscene, reuseMeshes, reuseMaterials, dynamic, oarray, masterobject));

		for (CK_ID* id = oarray->Begin(); id != oarray->End(); id++) {
			CKObject* obj = m_instance->m_context->GetObject(*id);
			if (obj->GetClassID() == CKCID_BEHAVIOR) {
				CKBehavior* beh = static_cast<CKBehavior*>(obj);
				if (beh->GetType() == CKBEHAVIORTYPE_SCRIPT)
					m_instance->BroadcastCallback(&IMod::OnLoadScript, std::bind(&IMod::OnLoadScript, std::placeholders::_1, filename, beh));
			}
		}
	}

	return result;
}

int ModLoader::Physicalize(const CKBehaviorContext& behcontext) {
	CKBehavior* beh = behcontext.Behavior;
	CKContext* ctx = behcontext.Context;
	bool physicalize = beh->IsInputActive(0);
	CK3dEntity* target = (CK3dEntity*)beh->GetTarget();

	if (physicalize) {
		BOOL fixed;
		float friction, elasticity, mass;
		beh->GetInputParameterValue(0, &fixed);
		beh->GetInputParameterValue(1, &friction);
		beh->GetInputParameterValue(2, &elasticity);
		beh->GetInputParameterValue(3, &mass);
		CKSTRING collGroup = (CKSTRING)beh->GetInputParameterReadDataPtr(4);
		BOOL startFrozen, enableColl, calcMassCenter;
		float linearDamp, rotDamp;
		beh->GetInputParameterValue(5, &startFrozen);
		beh->GetInputParameterValue(6, &enableColl);
		beh->GetInputParameterValue(7, &calcMassCenter);
		beh->GetInputParameterValue(8, &linearDamp);
		beh->GetInputParameterValue(9, &rotDamp);
		CKSTRING collSurface = (CKSTRING)beh->GetInputParameterReadDataPtr(10);
		VxVector massCenter;
		beh->GetLocalParameterValue(3, &massCenter);

		int convexCnt, ballCnt, concaveCnt;
		beh->GetLocalParameterValue(0, &convexCnt);
		beh->GetLocalParameterValue(1, &ballCnt);
		beh->GetLocalParameterValue(2, &concaveCnt);
		CKMesh **convexMesh = nullptr, **concaveMesh = nullptr;
		VxVector* ballCenter = nullptr; float* ballRadius = nullptr;

		int paramPos = 11;
		if (convexCnt > 0) {
			convexMesh = new CKMesh*[convexCnt];
			for (int i = 0; i < convexCnt; i++)
				convexMesh[i] = (CKMesh*)beh->GetInputParameterObject(paramPos + i);
			paramPos += convexCnt;
		}

		if (ballCnt > 0) {
			ballCenter = new VxVector[ballCnt];
			ballRadius = new float[ballCnt];
			for (int i = 0; i < ballCnt; i++) {
				beh->GetInputParameterValue(paramPos + 2 * i, ballCenter + i);
				beh->GetInputParameterValue(paramPos + 2 * i + 1, ballRadius + i);
			}
			paramPos += ballCnt * 2;
		}

		if (concaveCnt > 0) {
			concaveMesh = new CKMesh*[concaveCnt];
			for (int i = 0; i < concaveCnt; i++)
				concaveMesh[i] = (CKMesh*)beh->GetInputParameterObject(paramPos + i);
			paramPos += concaveCnt;
		}

		m_instance->BroadcastCallback(&IMod::OnPhysicalize, std::bind(&IMod::OnPhysicalize, std::placeholders::_1, target,
			fixed, friction, elasticity, mass, collGroup, startFrozen, enableColl, calcMassCenter, linearDamp, rotDamp,
			collSurface, massCenter, convexCnt, convexMesh, ballCnt, ballCenter, ballRadius, concaveCnt, concaveMesh));

		if (convexMesh) delete[] convexMesh;
		if (ballCenter) delete[] ballCenter;
		if (ballRadius) delete[] ballRadius;
		if (concaveMesh) delete[] concaveMesh;
	}
	else {
		m_instance->BroadcastCallback(&IMod::OnUnphysicalize, std::bind(&IMod::OnUnphysicalize, std::placeholders::_1, target));
	}

	return m_instance->m_physicalize(behcontext);
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
	BroadcastMessage("PreStartMenu", &IMod::OnPreStartMenu);
}

void ModLoader::OnPostStartMenu() {
	BroadcastMessage("PostStartMenu", &IMod::OnPostStartMenu);
}

void ModLoader::OnExitGame() {
	BroadcastMessage("ExitGame", &IMod::OnExitGame);
}

void ModLoader::OnPreLoadLevel() {
	BroadcastMessage("PreLoadLevel", &IMod::OnPreLoadLevel);
}

void ModLoader::OnPostLoadLevel() {
	BroadcastMessage("PostLoadLevel", &IMod::OnPostLoadLevel);
}

void ModLoader::OnStartLevel() {
	BroadcastMessage("StartLevel", &IMod::OnStartLevel);
	m_ingame = true;
	m_paused = false;
}

void ModLoader::OnPreResetLevel() {
	BroadcastMessage("PreResetLevel", &IMod::OnPreResetLevel);
}

void ModLoader::OnPostResetLevel() {
	BroadcastMessage("PostResetLevel", &IMod::OnPostResetLevel);
}

void ModLoader::OnPauseLevel() {
	BroadcastMessage("PauseLevel", &IMod::OnPauseLevel);
	m_paused = true;
}

void ModLoader::OnUnpauseLevel() {
	BroadcastMessage("UnpauseLevel", &IMod::OnUnpauseLevel);
	m_paused = false;
}

void ModLoader::OnPreExitLevel() {
	BroadcastMessage("PreExitLevel", &IMod::OnPreExitLevel);
}

void ModLoader::OnPostExitLevel() {
	BroadcastMessage("PostExitLevel", &IMod::OnPostExitLevel);
	m_ingame = false;
}

void ModLoader::OnPreNextLevel() {
	BroadcastMessage("PreNextLevel", &IMod::OnPreNextLevel);
}

void ModLoader::OnPostNextLevel() {
	BroadcastMessage("PostNextLevel", &IMod::OnPostNextLevel);
}

void ModLoader::OnDead() {
	BroadcastMessage("Dead", &IMod::OnDead);
	m_ingame = false;
}

void ModLoader::OnPreEndLevel() {
	BroadcastMessage("PreEndLevel", &IMod::OnPreEndLevel);
}

void ModLoader::OnPostEndLevel() {
	BroadcastMessage("PostEndLevel", &IMod::OnPostEndLevel);
	m_ingame = false;
}

void ModLoader::OnCounterActive() {
	BroadcastMessage("CounterActive", &IMod::OnCounterActive);
}

void ModLoader::OnCounterInactive() {
	BroadcastMessage("CounterInactive", &IMod::OnCounterInactive);
}

void ModLoader::OnBallNavActive() {
	BroadcastMessage("BallNavActive", &IMod::OnBallNavActive);
}

void ModLoader::OnBallNavInactive() {
	BroadcastMessage("BallNavInactive", &IMod::OnBallNavInactive);
}

void ModLoader::OnCamNavActive() {
	BroadcastMessage("CamNavActive", &IMod::OnCamNavActive);
}

void ModLoader::OnCamNavInactive() {
	BroadcastMessage("CamNavInactive", &IMod::OnCamNavInactive);
}

void ModLoader::OnBallOff() {
	BroadcastMessage("BallOff", &IMod::OnBallOff);
}

void ModLoader::OnPreCheckpointReached() {
	BroadcastMessage("PreCheckpoint", &IMod::OnPreCheckpointReached);
}

void ModLoader::OnPostCheckpointReached() {
	BroadcastMessage("PostCheckpoint", &IMod::OnPostCheckpointReached);
}

void ModLoader::OnLevelFinish() {
	BroadcastMessage("LevelFinish", &IMod::OnLevelFinish);
	m_bmlmod->ShowWatermark(true);
}

void ModLoader::OnGameOver() {
	BroadcastMessage("GameOver", &IMod::OnGameOver);
}

void ModLoader::OnExtraPoint() {
	BroadcastMessage("ExtraPoint", &IMod::OnExtraPoint);
}

void ModLoader::OnPreSubLife() {
	BroadcastMessage("PreSubLife", &IMod::OnPreSubLife);
}

void ModLoader::OnPostSubLife() {
	BroadcastMessage("PostSubLife", &IMod::OnPostSubLife);
}

void ModLoader::OnPreLifeUp() {
	BroadcastMessage("PreLifeUp", &IMod::OnPreLifeUp);
}

void ModLoader::OnPostLifeUp() {
	BroadcastMessage("PostLifeUp", &IMod::OnPostLifeUp);
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
	ToLower(args[0]);
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
	if (!enable && IsCheatEnabled())
		ModLoader::m_instance->ExecuteCommand("speed 1");
	m_cheatEnabled = enable;
	m_bmlmod->ShowCheatBanner(enable);
	BroadcastCallback(&IMod::OnCheatEnabled, std::bind(&IMod::OnCheatEnabled, std::placeholders::_1, enable));
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

void ModLoader::RegisterBallType(CKSTRING ballFile, CKSTRING ballId, CKSTRING ballName, CKSTRING objName, float friction, float elasticity,
	float mass, CKSTRING collGroup, float linearDamp, float rotDamp, float force, float radius) {
	m_ballTypeMod->RegisterBallType(ballFile, ballId, ballName, objName, friction, elasticity,
		mass, collGroup, linearDamp, rotDamp, force, radius);
}

void ModLoader::RegisterFloorType(CKSTRING floorName, float friction, float elasticity, float mass, CKSTRING collGroup, bool enableColl) {
	m_ballTypeMod->RegisterFloorType(floorName, friction, elasticity, mass, collGroup, enableColl);
}

void ModLoader::RegisterModulBall(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
	bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp, float radius) {
	m_ballTypeMod->RegisterModulBall(modulName, fixed, friction, elasticity, mass, collGroup,
		frozen, enableColl, calcMassCenter, linearDamp, rotDamp, radius);
}

void ModLoader::RegisterModulConvex(CKSTRING modulName, bool fixed, float friction, float elasticity, float mass, CKSTRING collGroup,
	bool frozen, bool enableColl, bool calcMassCenter, float linearDamp, float rotDamp) {
	m_ballTypeMod->RegisterModulConvex(modulName, fixed, friction, elasticity, mass, collGroup,
		frozen, enableColl, calcMassCenter, linearDamp, rotDamp);
}

void ModLoader::RegisterTrafo(CKSTRING modulName) {
	m_ballTypeMod->RegisterTrafo(modulName);
}

void ModLoader::RegisterModul(CKSTRING modulName) {
	m_ballTypeMod->RegisterModul(modulName);
}

void ModLoader::FillCallbackMap(IMod* mod) {
	static class BlankMod : IMod {
	public:
		BlankMod(IBML* bml) : IMod(bml) {}
		virtual CKSTRING GetID() override { return ""; }
		virtual CKSTRING GetVersion() override { return ""; }
		virtual CKSTRING GetName() override { return ""; }
		virtual CKSTRING GetAuthor() override { return ""; }
		virtual CKSTRING GetDescription() override { return ""; }
		DECLARE_BML_VERSION;
	} blank(this);

	void** vtable[2] = {
		*reinterpret_cast<void***>(&blank),
		*reinterpret_cast<void***>(mod) };

	int index = 0;
#define CHECK_V_FUNC(IDX, FUNC) { \
	auto idx = IDX; \
	if (vtable[0][idx] != vtable[1][idx]) \
		m_callback_map[func_addr(FUNC)].push_back(mod); \
}

	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreStartMenu);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostStartMenu);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnExitGame);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreLoadLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostLoadLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnStartLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreResetLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostResetLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPauseLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnUnpauseLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreExitLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostExitLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreNextLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostNextLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnDead);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreEndLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostEndLevel);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnCounterActive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnCounterInactive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnBallNavActive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnBallNavInactive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnCamNavActive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnCamNavInactive);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnBallOff);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreCheckpointReached);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostCheckpointReached);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnLevelFinish);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnGameOver);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnExtraPoint);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreSubLife);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostSubLife);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPreLifeUp);
	CHECK_V_FUNC(index++, &IMessageReceiver::OnPostLifeUp);

	index += 7;

	CHECK_V_FUNC(index++, &IMod::OnLoad);
	CHECK_V_FUNC(index++, &IMod::OnUnload);
	CHECK_V_FUNC(index++, &IMod::OnModifyConfig);
	CHECK_V_FUNC(index++, &IMod::OnLoadObject);
	CHECK_V_FUNC(index++, &IMod::OnLoadScript);
	CHECK_V_FUNC(index++, &IMod::OnProcess);
	CHECK_V_FUNC(index++, &IMod::OnRender);
	CHECK_V_FUNC(index++, &IMod::OnCheatEnabled);

	if (mod->GetBMLVersion() >= BMLVersion(0, 3, 34)) {
		CHECK_V_FUNC(index++, &IMod::OnPhysicalize);
		CHECK_V_FUNC(index++, &IMod::OnUnphysicalize);
	}

#undef CHECK_V_FUNC
}

int ModLoader::GetModCount() {
	return m_mods.size();
}

IMod* ModLoader::GetMod(int index) {
	return m_mods[index];
}

float ModLoader::GetSRScore() {
	return m_bmlmod->GetSRScore();
}

int ModLoader::GetHSScore() {
	return m_bmlmod->GetHSScore();
}

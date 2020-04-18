#include "BMLAll.h"
#include "minhook/MinHook.h"
#include <iostream>
#include "BMLMod.h"

Player::StepFunc Player::m_step = &Player::Step;

ModLoader::ModLoader() {
	m_instance = this;
}

ModLoader::~ModLoader() {
	m_instance = nullptr;
}

void ModLoader::Init() {
	m_logfile = fopen("../ModLoader/ModLoader.log", "w");
	m_logger = new Logger("ModLoader");

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

	GetContextsAndManagers();

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

	m_mods.push_back(new BMLMod(this));
	for (IMod* mod : m_instance->m_mods)
		mod->OnLoad();

	for (Config* config : m_instance->m_configs)
		config->Save();

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

	m_inputManager = static_cast<CKInputManager*>(m_context->GetManagerByGuid(INPUT_MANAGER_GUID));
	m_logger->Info("Get Input Manager pointer 0x%08x", m_inputManager);

	m_messageManager = m_context->GetMessageManager();
	m_logger->Info("Get Message Manager pointer 0x%08x", m_messageManager);

	m_parameterManager = m_context->GetParameterManager();
	m_logger->Info("Get Parameter Manager pointer 0x%08x", m_parameterManager);

	m_renderManager = m_context->GetRenderManager();
	m_logger->Info("Get Render Manager pointer 0x%08x", m_renderManager);

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

void ModLoader::Process(CKERROR result) {
	for (IMod* mod : m_instance->m_mods)
		mod->OnProcess();
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

void ModLoader::OpenModsMenu() {
	m_logger->Info("Open Mods Menu");
}

void ModLoader::OnStartMenu() {
	m_logger->Info("On message Start Menu");
	for (IMod* mod : m_instance->m_mods)
		mod->OnStartMenu();
}

void ModLoader::OnExitGame() {
	m_logger->Info("On message Exit Game");
	for (IMod* mod : m_instance->m_mods)
		mod->OnExitGame();
}

void ModLoader::OnLoadLevel() {
	m_logger->Info("On message Load Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnLoadLevel();
}

void ModLoader::OnStartLevel() {
	m_logger->Info("On message Start Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnStartLevel();
}

void ModLoader::OnResetLevel() {
	m_logger->Info("On message Reset Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnResetLevel();
}

void ModLoader::OnPauseLevel() {
	m_logger->Info("On message Pause Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnPauseLevel();
}

void ModLoader::OnUnpauseLevel() {
	m_logger->Info("On message Unpause Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnUnpauseLevel();
}

void ModLoader::OnExitLevel() {
	m_logger->Info("On message Exit Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnExitLevel();
}

void ModLoader::OnNextLevel() {
	m_logger->Info("On message Next Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnNextLevel();
}

void ModLoader::OnDead() {
	m_logger->Info("On message Dead");
	for (IMod* mod : m_instance->m_mods)
		mod->OnDead();
}

void ModLoader::OnEndLevel() {
	m_logger->Info("On message End Level");
	for (IMod* mod : m_instance->m_mods)
		mod->OnEndLevel();
}

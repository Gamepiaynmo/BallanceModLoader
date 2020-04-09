#include "BMLAll.h"
#include "minhook/MinHook.h"
#include <iostream>

Player::StepFunc Player::m_step = &Player::Step;
Player::ProcessFunc Player::m_process = &Player::Process;
const CKDWORD STEP_ADDR = 0x00401BF0, PROCESS_ADDR = 0x004057A0;

ModLoader::ModLoader() {
	m_instance = this;
}

ModLoader::~ModLoader() {
	m_instance = nullptr;
}

void ModLoader::Init() {
	m_logfile = fopen("../ModLoader/ModLoader.log", "w");
	m_logger = CreateLogger("BML");

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

	if (MH_CreateHook(reinterpret_cast<LPVOID>(STEP_ADDR),
		*reinterpret_cast<LPVOID*>(&Player::m_step),
		reinterpret_cast<LPVOID*>(&Player::m_step)) != MH_OK) {
		m_logger->Error("Create Step Hook Failed");
		return;
	}
	
	if (MH_CreateHook(reinterpret_cast<LPVOID>(PROCESS_ADDR),
		*reinterpret_cast<LPVOID*>(&Player::m_process),
		reinterpret_cast<LPVOID*>(&Player::m_process)) != MH_OK) {
		m_logger->Error("Create Process Hook Failed");
		return;
	}

	if (MH_EnableHook(reinterpret_cast<LPVOID>(STEP_ADDR)) != MH_OK) {
		m_logger->Error("Enable Step Hook Failed");
		return;
	}

	if (MH_EnableHook(reinterpret_cast<LPVOID>(PROCESS_ADDR)) != MH_OK) {
		m_logger->Error("Enable Process Hook Failed");
		return;
	}

	m_logger->Info("Step & Process Hook created");

	m_inited = true;
}

void ModLoader::Release() {
	if (m_loaded)
		Unload();

	m_inited = false;

	m_logger->Info("Releasing Mod Loader");

	if (MH_Uninitialize() != MH_OK)
		m_logger->Warn("MinHook Uninitialize Failed");
	else m_logger->Info("MinHook Uninitialized");

#ifdef _DEBUG
	FreeConsole();
#endif

	delete m_logger;
	fclose(m_logfile);
}

// Game Loop
CKDWORD Player::Step() {
	return ModLoader::m_instance->Step((this->*m_step)());
}

// Game Tick
void Player::Process() {
	(this->*m_process)();
	ModLoader::m_instance->Process();
}

CKDWORD ModLoader::Step(CKDWORD result) {
	if (!m_loaded) {
		Load();
		if (!m_loaded) {
			m_logger->Error("Failed to load Mod Loader");
			Unload();
			Release();
			return 0;
		}
	}

	if (!result) {
		m_logger->Info("Ballance is exiting");
		Unload();
		return 0;
	}

	return 1;
}

void ModLoader::Load() {
	m_logger->Info("Loading Mod Loader");

	m_context = GetCKContext(0);
	m_logger->Info("Get CKContext pointer 0x%08x", m_context);

	m_timeManager = m_context->GetTimeManager();
	m_logger->Info("Get Time Manager pointer 0x%08x", m_timeManager);

	m_inputManager = static_cast<CKInputManager*>(m_context->GetManagerByGuid(INPUT_MANAGER_GUID));
	m_logger->Info("Get Input Manager pointer 0x%08x", m_inputManager);

	m_loaded = true;
}

void ModLoader::Process() {
	m_timeManager->SetTimeScaleFactor(3.0f);

	int cnt = m_context->GetObjectsCountByClassID(CKCID_BEHAVIOR);
	if (cnt > 0) {
		CK_ID* objs = m_context->GetObjectsListByClassID(CKCID_BEHAVIOR);
		for (int i = 0; i < cnt; i++) {
			CKBehavior* beh = static_cast<CKBehavior*>(m_context->GetObject(objs[i]));
			if (beh->GetType() == CKBEHAVIORTYPE_SCRIPT)
				m_logger->Info(beh->GetName());
		}
	}

	cnt = 0;
}

void ModLoader::Unload() {
	m_loaded = false;

	m_logger->Info("Unloading Mod Loader");
}

Logger* ModLoader::CreateLogger(const char* modname) {
	return new Logger(modname);
}

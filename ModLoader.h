#pragma once

#include "IBML.h"
#include <cstdio>
#include <Windows.h>

class ModLoader : public IBML {
public:
	ModLoader();
	~ModLoader();

	static ModLoader* m_instance;

	void Init();
	void Release();

	void Load();
	void Unload();

	UINT Step(UINT stop);
	void Process();

	bool Inited() { return m_inited; }
	FILE* GetLogFile() { return m_logfile; }

	virtual Logger* CreateLogger(const char* modname) override;

private:
	bool m_inited = false, m_loaded = false;

	FILE* m_logfile = nullptr;
	Logger* m_logger = nullptr;
};

class Player {
public:
	UINT Step();
	void Process();

	typedef void (Player::* ProcessFunc)();
	static ProcessFunc m_process;
	typedef UINT (Player::* StepFunc)();
	static StepFunc m_step;
};
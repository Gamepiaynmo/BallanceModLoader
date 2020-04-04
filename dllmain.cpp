﻿#include "BMLAll.h"
#include <Windows.h>

ModLoader *ModLoader::m_instance = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            ModLoader::m_instance = new ModLoader();
            ModLoader::m_instance->Init();
            if (!ModLoader::m_instance->Inited())
                delete ModLoader::m_instance;

            break;

        case DLL_PROCESS_DETACH:
            if (ModLoader::m_instance != nullptr) {
                ModLoader::m_instance->Release();
                delete ModLoader::m_instance;
            }

            break;
    }

    return TRUE;
}

class XStringDef {
public:
	XStringDef(const char* str) {
		m_str = str;
		m_len = m_alloc = (short) strlen(str);
	}

private:
	const char* m_str;
	short m_len, m_alloc;
};

struct CKPluginInfo {
	UINT m_GUID[4] = { 0 };
	UINT m_Extension = 0;
	XStringDef m_Description = "Ballance Mod Loader";
	XStringDef m_Author = "Gamepiaynmo";
	XStringDef m_Summary = "Mod Loader for Ballance";
	DWORD m_Version = BML_MAJOR_VER << 16 | BML_MINOR_VER << 8 | BML_BUILD_VER;
	DWORD m_InitInstanceFct = 0;
	DWORD m_Type = 4;
	DWORD m_ExitInstanceFct = 0;
} g_pInfo;

EXTERN_C_START

BML_EXPORT int CKGetPluginInfoCount() { return 1; }
BML_EXPORT CKPluginInfo* CKGetPluginInfo(int Index) { return &g_pInfo; }
BML_EXPORT void RegisterBehaviorDeclarations(void* reg) {}

EXTERN_C_END
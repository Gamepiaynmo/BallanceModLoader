#include "BMLAll.h"
#include <Windows.h>
#include "virtools/CKAll.h"
#include "RegisterBB.h"

ModLoader *ModLoader::m_instance = nullptr;

void HookPrototypeRuntime() {
    BYTE data[] = { 0xeb, 0x75 };
    ModLoader::WriteMemory(reinterpret_cast<LPVOID>(0x240388F4), &data, sizeof(data));
}

CKERROR InitInstance(CKContext* context) {
    if (ModLoader::m_instance == nullptr) {
        ModLoader::m_instance = new ModLoader();
        ModLoader::m_instance->Init();
        if (!ModLoader::m_instance->Inited())
            delete ModLoader::m_instance;
    }
    return CK_OK;
}

CKERROR ExitInstance(CKContext* context) {
    if (ModLoader::m_instance != nullptr) {
        ModLoader::m_instance->Release();
        delete ModLoader::m_instance;
    }
    return CK_OK;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            HookPrototypeRuntime();
            break;
        case DLL_PROCESS_DETACH:
            ExitInstance(GetCKContext(0));
            break;
    }

    return TRUE;
}

CKPluginInfo g_pInfo;

EXTERN_C_START

BML_EXPORT int CKGetPluginInfoCount() { return 1; }

BML_EXPORT CKPluginInfo* CKGetPluginInfo(int Index) {
	g_pInfo.m_Author = "Gamepiaynmo";
	g_pInfo.m_Description = "Ballance Mod Loader";
	g_pInfo.m_Extension = "";
	g_pInfo.m_Type = CKPLUGIN_BEHAVIOR_DLL;
	g_pInfo.m_Version = BML_MAJOR_VER << 16 | BML_MINOR_VER;
	g_pInfo.m_InitInstanceFct = InitInstance;
	g_pInfo.m_ExitInstanceFct = ExitInstance;
	g_pInfo.m_GUID = CKGUID(0x6229385d, 0x197331db);
	g_pInfo.m_Summary = "Mod Loader for Ballance";
    return &g_pInfo;
}

BML_EXPORT void RegisterBehaviorDeclarations(XObjectDeclarationArray* reg) {
    RegisterBBs(reg);
}

EXTERN_C_END
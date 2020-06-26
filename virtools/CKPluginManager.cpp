#include "CKPluginManager.h"

NAKED int CKPluginManager::ParsePlugins(CKSTRING Directory) {
	JUMP(0x240153B3);
}

NAKED CKERROR CKPluginManager::RegisterPlugin(CKSTRING str) {
	JUMP(0x24015425);
}

NAKED CKPluginEntry* CKPluginManager::FindComponent(CKGUID Component, int catIdx) {
	JUMP(0x24014B99);
}

NAKED int CKPluginManager::AddCategory(CKSTRING cat) {
	JUMP(0x240161F7);
}

NAKED CKERROR CKPluginManager::RemoveCategory(int catIdx) {
	JUMP(0x240162ED);
}

NAKED int CKPluginManager::GetCategoryCount() {
	JUMP(0x24016347);
}

NAKED CKSTRING CKPluginManager::GetCategoryName(int catIdx) {
	JUMP(0x24016354);
}

NAKED int CKPluginManager::GetCategoryIndex(CKSTRING cat) {
	JUMP(0x2401638B);
}

NAKED CKERROR CKPluginManager::RenameCategory(int catIdx, CKSTRING newName) {
	JUMP(0x2401636F);
}

NAKED int CKPluginManager::GetPluginDllCount() {
	JUMP(0x240160D0);
}

NAKED CKPluginDll* CKPluginManager::GetPluginDllInfo(int PluginDllIdx) {
	JUMP(0x240160DA);
}

NAKED CKPluginDll* CKPluginManager::GetPluginDllInfo(CKSTRING PluginName, int* idx) {
	JUMP(0x240160E7);
}

NAKED CKERROR CKPluginManager::UnLoadPluginDll(int PluginDllIdx) {
	JUMP(0x24015DC4);
}

NAKED CKERROR CKPluginManager::ReLoadPluginDll(int PluginDllIdx) {
	JUMP(0x24015E8A);
}

NAKED int CKPluginManager::GetPluginCount(int catIdx) {
	JUMP(0x24016158);
}

NAKED CKPluginEntry* CKPluginManager::GetPluginInfo(int catIdx, int PluginIdx) {
	JUMP(0x24016171);
}

NAKED BOOL CKPluginManager::SetReaderOptionData(CKContext* context, void* memdata, CKParameterOut* Param, CKFileExtension ext, CKGUID* guid) {
	JUMP(0x24016960);
}

NAKED CKParameterOut* CKPluginManager::GetReaderOptionData(CKContext* context, void* memdata, CKFileExtension ext, CKGUID* guid) {
	JUMP(0x2401681B);
}

NAKED CKBitmapReader* CKPluginManager::GetBitmapReader(CKFileExtension& ext, CKGUID* preferedGUID) {
	JUMP(0x240165A9);
}

NAKED CKSoundReader* CKPluginManager::GetSoundReader(CKFileExtension& ext, CKGUID* preferedGUID) {
	JUMP(0x240165D3);
}

NAKED CKModelReader* CKPluginManager::GetModelReader(CKFileExtension& ext, CKGUID* preferedGUID) {
	JUMP(0x240165FD);
}

NAKED CKMovieReader* CKPluginManager::GetMovieReader(CKFileExtension& ext, CKGUID* preferedGUID) {
	JUMP(0x24016627);
}

NAKED CKERROR CKPluginManager::Load(CKContext* context, CKSTRING FileName, CKObjectArray* liste, CK_LOAD_FLAGS LoadFlags, CKCharacter* carac, CKGUID* Readerguid) {
	JUMP(0x24016416);
}

NAKED CKERROR CKPluginManager::Save(CKContext* context, CKSTRING FileName, CKObjectArray* liste, CKDWORD SaveFlags, CKGUID* Readerguid) {
	JUMP(0x240164EE);
}

#include "CKPathManager.h"

NAKED int CKPathManager::AddCategory(const XString& cat) {
	JUMP(0x24013759);
}

NAKED CKERROR CKPathManager::RemoveCategory(int catIdx) {
	JUMP(0x24013843);
}

NAKED int CKPathManager::GetCategoryCount() {
	JUMP(0x24013866);
}

NAKED CKERROR CKPathManager::GetCategoryName(int catIdx, XString& catName) {
	JUMP(0x24013873);
}

NAKED int CKPathManager::GetCategoryIndex(const XString& cat) {
	JUMP(0x240138AC);
}

NAKED CKERROR CKPathManager::RenameCategory(int catIdx, const XString& newName) {
	JUMP(0x24013890);
}

NAKED int CKPathManager::AddPath(int catIdx, const XString& path) {
	JUMP(0x24013936);
}

NAKED CKERROR CKPathManager::RemovePath(int catIdx, int pathIdx) {
	JUMP(0x240139FC);
}

NAKED CKERROR CKPathManager::SwapPaths(int catIdx, int pathIdx1, int pathIdx2) {
	JUMP(0x24013A27);
}

NAKED int CKPathManager::GetPathCount(int catIdx) {
	JUMP(0x240138F8);
}

NAKED CKERROR CKPathManager::GetPathName(int catIdx, int pathIdx, XString& path) {
	JUMP(0x24013911);
}

NAKED int CKPathManager::GetPathIndex(int catIdx, const XString& path) {
	JUMP(0x24013980);
}

NAKED CKERROR CKPathManager::RenamePath(int catIdx, int pathIdx, const XString& path) {
	JUMP(0x240139D8);
}

NAKED CKERROR CKPathManager::ResolveFileName(XString& file, int catIdx, int startIdx) {
	JUMP(0x24013B3C);
}

NAKED BOOL CKPathManager::PathIsAbsolute(const XString& file) {
	JUMP(0x24014068);
}

NAKED BOOL CKPathManager::PathIsUNC(const XString& file) {
	JUMP(0x240140B0);
}

NAKED BOOL CKPathManager::PathIsURL(const XString& file) {
	JUMP(0x240140FE);
}

NAKED BOOL CKPathManager::PathIsFile(const XString& file) {
	JUMP(0x24014185);
}

NAKED void CKPathManager::RemoveEscapedSpace(char* str) {
	JUMP(0x24013AE1);
}

NAKED void CKPathManager::AddEscapedSpace(const XString& str) {
	JUMP(0x24013A92);
}

NAKED const XString CKPathManager::GetVirtoolsTemporaryFolder() {
	JUMP(0x24013A51);
}

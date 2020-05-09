#pragma once

#include "CKBaseManager.h"

class CKPathManager : public CKBaseManager {
public:
	int AddCategory(XString& cat);
	CKERROR RemoveCategory(int catIdx);
	int GetCategoryCount();
	CKERROR GetCategoryName(int catIdx, XString& catName);
	int GetCategoryIndex(XString& cat);
	CKERROR RenameCategory(int catIdx, XString& newName);
	int AddPath(int catIdx, XString& path);
	CKERROR RemovePath(int catIdx, int pathIdx);
	CKERROR SwapPaths(int catIdx, int pathIdx1, int pathIdx2);
	int GetPathCount(int catIdx);
	CKERROR GetPathName(int catIdx, int pathIdx, XString& path);
	int GetPathIndex(int catIdx, XString& path);
	CKERROR RenamePath(int catIdx, int pathIdx, XString& path);
	CKERROR ResolveFileName(XString& file, int catIdx, int startIdx = -1);
	BOOL PathIsAbsolute(XString& file);
	BOOL PathIsUNC(XString& file);
	BOOL PathIsURL(XString& file);
	BOOL PathIsFile(XString& file);
	void RemoveEscapedSpace(char* str);
	void AddEscapedSpace(XString& str);
	XString GetVirtoolsTemporaryFolder();

protected:
	CKPathManager() {};
	~CKPathManager() {};
};
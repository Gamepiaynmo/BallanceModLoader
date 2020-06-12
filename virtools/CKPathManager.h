#pragma once

#include "CKBaseManager.h"

typedef enum CK_PATHMANAGER_CATEGORY {
	BITMAP_PATH_IDX = 0,	// Category index for bitmaps paths
	DATA_PATH_IDX = 1,	// Category index for datas paths
	SOUND_PATH_IDX = 2	// Category index for sounds paths
} CK_PATHMANAGER_CATEGORY;

class BML_EXPORT CKPathManager : public CKBaseManager {
public:
	int AddCategory(const XString& cat);
	CKERROR RemoveCategory(int catIdx);
	int GetCategoryCount();
	CKERROR GetCategoryName(int catIdx, XString& catName);
	int GetCategoryIndex(const XString& cat);
	CKERROR RenameCategory(int catIdx, const XString& newName);
	int AddPath(int catIdx, const XString& path);
	CKERROR RemovePath(int catIdx, int pathIdx);
	CKERROR SwapPaths(int catIdx, int pathIdx1, int pathIdx2);
	int GetPathCount(int catIdx);
	CKERROR GetPathName(int catIdx, int pathIdx, XString& path);
	int GetPathIndex(int catIdx, const XString& path);
	CKERROR RenamePath(int catIdx, int pathIdx, const XString& path);
	CKERROR ResolveFileName(XString& file, int catIdx, int startIdx = -1);
	BOOL PathIsAbsolute(const XString& file);
	BOOL PathIsUNC(const XString& file);
	BOOL PathIsURL(const XString& file);
	BOOL PathIsFile(const XString& file);
	void RemoveEscapedSpace(char* str);
	void AddEscapedSpace(const XString& str);
	const XString GetVirtoolsTemporaryFolder();

protected:
	CKPathManager() {};
	~CKPathManager() {};
};
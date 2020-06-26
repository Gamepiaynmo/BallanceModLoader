#pragma once

#include "CKDef.h"

#undef GetObject

struct CKStreamWriter;

typedef XClassArray<CKClassDesc> XClassInfoArray;
typedef XArray<CKBaseManager*> XManagerArray;

typedef XHashTable<CKBaseManager*, CKGUID>		XManagerHashTable;
typedef XManagerHashTable::Iterator				XManagerHashTableIt;
typedef XManagerHashTable::Pair					XManagerHashTablePair;

typedef XHashTable<CKObjectDeclaration*, CKGUID>		XObjDeclHashTable;
typedef XObjDeclHashTable::Iterator					XObjDeclHashTableIt;
typedef XObjDeclHashTable::Pair						XObjDeclHashTablePair;

class BML_EXPORT CKContext {
public:
	CKLevel* GetCurrentLevel();
	CKScene* GetCurrentScene();
	CKRenderContext* GetPlayerRenderContext();
	void SetCurrentLevel(CKLevel* level);

	CKERROR ClearAll();
	CKDWORD GetFocusLostBehavior();
	CKBOOL IsInBreak();
	CKBOOL IsInClearAll();
	CKBOOL IsPlaying();
	CKBOOL IsReseted();
	CKERROR Pause();
	CKERROR Play();
	CKERROR Process();
	CKERROR Reset();

	CKBOOL IsInInterfaceMode();
	CKERROR OutputToConsole(CKSTRING str, CKBOOL bBeep = TRUE);
	CKERROR OutputToConsoleEx(CKSTRING format, ...);
	CKERROR OutputToConsoleExBeep(CKSTRING format, ...);
	CKERROR OutputToInfo(CKSTRING format, ...);
	CKERROR Select(const XObjectArray& o, BOOL clearSelection = TRUE);
	CKDWORD SendInterfaceMessage(CKDWORD reason, CKDWORD param1, CKDWORD param2, CKDWORD param3 = 0);
	CKERROR ShowSetup(CK_ID);
	CKERROR UICopyObjects(const XObjectArray& iObjects, CKBOOL iClearClipboard = TRUE);
	CKERROR UIPasteObjects(const XObjectArray& oObjects);

	void ActivateManager(CKBaseManager* bm, CKBOOL active);
	CKAttributeManager* GetAttributeManager();
	CKBehaviorManager* GetBehaviorManager();
	CKBaseManager* GetInactiveManager(int index);
	int GetInactiveManagerCount();
	CKBaseManager* GetManager(int index);
	CKBaseManager* GetManagerByGuid(CKGUID guid);
	CKBaseManager* GetManagerByName(CKSTRING ManagerName);
	int GetManagerCount();
	XManagerHashTableIt GetManagers();
	CKMessageManager* GetMessageManager();
	CKParameterManager* GetParameterManager();
	CKPathManager* GetPathManager();
	CKRenderManager* GetRenderManager();
	CKTimeManager* GetTimeManager();
	CKVariableManager* GetVariableManager();
	CKBOOL HasManagerDuplicates(CKBaseManager* bm);
	CKBOOL IsManagerActive(CKBaseManager* bm);
	CKERROR RegisterNewManager(CKBaseManager* manager);

	const XObjectPointerArray& CKFillObjectsUnused();
	void ChangeObjectDynamic(CKObject* iObject, CKBOOL iSetDynamic = TRUE);
	CKObject* CopyObject(CKObject* src, CKDependencies* Dependencies = NULL, CKSTRING AppendName = NULL, CK_OBJECTCREATION_OPTIONS Options = CK_OBJECTCREATION_NONAMECHECK);
	const XObjectArray& CopyObjects(const XObjectArray& SrcObjects, CKDependencies* Dependencies = NULL, CK_OBJECTCREATION_OPTIONS Options = CK_OBJECTCREATION_NONAMECHECK, CKSTRING AppendName = NULL);
	CKObject* CreateObject(CK_CLASSID cid, CKSTRING Name = NULL, CK_OBJECTCREATION_OPTIONS Options = CK_OBJECTCREATION_NONAMECHECK, CK_CREATIONMODE* Res = NULL);
	void DestroyAllDynamicObjects();
	CKERROR DestroyObject(CKObject* obj, DWORD Flags = 0, CKDependencies* depoptions = NULL);
	CKERROR DestroyObject(CK_ID id, DWORD Flags = 0, CKDependencies* depoptions = NULL);
	CKERROR DestroyObjects(CK_ID* obj_ids, int Count, CKDWORD Flags = 0, CKDependencies* depoptions = NULL);
	CKObject* GetObject(CK_ID ObjID);
	CKObject* GetObjectByName(CKSTRING name, CKObject* previous = NULL);
	CKObject* GetObjectByNameAndClass(CKSTRING name, CK_CLASSID cid, CKObject* previous = NULL);
	CKObject* GetObjectByNameAndParentClass(CKSTRING name, CK_CLASSID pcid, CKObject* previous);
	int GetObjectCount();
	const XObjectPointerArray& GetObjectListByType(CK_CLASSID cid, CKBOOL derived);
	int GetObjectSize(CKObject* obj);
	int GetObjectsCountByClassID(CK_CLASSID cid);
	CK_ID* GetObjectsListByClassID(CK_CLASSID cid);
	CKBOOL IsObjectSafe(CKObject* obj);

	CKERROR GetFileInfo(CKSTRING FileName, CKFileInfo* FileInfo);
	CKERROR GetFileInfo(int BufferSize, void* MemoryBuffer, CKFileInfo* FileInfo);

	void EnableProfiling(CKBOOL enable);
	float GetLastUserProfileTime(CKDWORD UserSlot);
	void GetProfileStats(CKStats* stats);
	CKBOOL IsProfilingEnable();
	void UserProfileStart(CKDWORD UserSlot);
	float UserProfileEnd(CKDWORD UserSlot);

	CKFile* CreateCKFile();
	CKERROR DeleteCKFile(CKFile*);
	CKSTRING GetLastCmoLoaded();
	CKSTRING GetLastFileLoaded();
	CKSTRING GetLastFileSaved();
	CKBOOL IsInLoad();
	CKBOOL IsInSave();
	CKERROR Load(CKSTRING FileName, CKObjectArray* liste, CK_LOAD_FLAGS LoadFlags = CK_LOAD_DEFAULT, CKGUID* ReaderGuid = NULL);
	CKERROR Load(int BufferSize, void* MemoryBuffer, CKObjectArray* ckarray, CK_LOAD_FLAGS LoadFlags = CK_LOAD_DEFAULT);
	CKERROR LoadAnimationOnCharacter(CKSTRING FileName, CKObjectArray* liste, CKCharacter* carac, CKGUID* ReaderGuid = NULL, BOOL AsDynamicObjects = FALSE);
	CKERROR LoadAnimationOnCharacter(int BufferSize, void* MemoryBuffer, CKObjectArray* ckarray, CKCharacter* carac, BOOL AsDynamicObjects = FALSE);
	CKERROR Save(CKSTRING FileName, CKObjectArray* liste, CKDWORD SaveFlags, CKDependencies* dependencies = NULL, CKGUID* ReaderGuid = NULL);
	void SetLastCmoLoaded(CKSTRING str);
	void SetLastFileSaved(CKSTRING str);
	void SetStreamWriter(CKStreamWriter* iWriter);

	int GetCompressionLevel();
	CK_FILE_WRITEMODE GetFileWriteMode();
	CKBitmapProperties* GetGlobalImagesSaveFormat();
	CK_TEXTURE_SAVEOPTIONS GetGlobalImagesSaveOptions();
	CK_SOUND_SAVEOPTIONS GetGlobalSoundsSaveOptions();
	void SetCompressionLevel(int level);
	void SetFileWriteMode(CK_FILE_WRITEMODE mode);
	void SetGlobalImagesSaveFormat(CKBitmapProperties* Format);
	void SetGlobalImagesSaveOptions(CK_TEXTURE_SAVEOPTIONS Options);
	void SetGlobalSoundsSaveOptions(CK_SOUND_SAVEOPTIONS Options);

	int GetSelectedRenderEngine();
	CKDWORD GetStartOptions();

	CKParameterIn* CreateCKParameterIn(CKSTRING Name, CKParameterType type, CKBOOL Dynamic = FALSE);
	CKParameterIn* CreateCKParameterIn(CKSTRING Name, CKGUID guid, CKBOOL Dynamic = FALSE);
	CKParameterIn* CreateCKParameterIn(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic = FALSE);
	CKParameterLocal* CreateCKParameterLocal(CKSTRING Name, CKParameterType type, CKBOOL Dynamic = FALSE);
	CKParameterLocal* CreateCKParameterLocal(CKSTRING Name, CKGUID guid, CKBOOL Dynamic = FALSE);
	CKParameterLocal* CreateCKParameterLocal(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic = FALSE);
	CKParameterOperation* CreateCKParameterOperation(CKSTRING Name, CKGUID opguid, CKGUID ResGuid, CKGUID p1Guid, CKGUID p2Guid);
	CKParameterOut* CreateCKParameterOut(CKSTRING Name, CKParameterType type, CKBOOL Dynamic = FALSE);
	CKParameterOut* CreateCKParameterOut(CKSTRING Name, CKGUID guid, CKBOOL Dynamic = FALSE);
	CKParameterOut* CreateCKParameterOut(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic = FALSE);
	CKBOOL DumpObjectManagerMemoryUse(CKSTRING DumpFilename, CKBOOL DumpAllObjects);

	WIN_HANDLE GetMainWindow();
	CKGUID GetSecureGuid();

protected:
	CKContext() {};
	~CKContext() {};
};
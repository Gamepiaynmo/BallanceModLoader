#include "CKContext.h"

NAKED CKLevel* CKContext::GetCurrentLevel() {
	JUMP(0x24035166);
}

NAKED CKScene* CKContext::GetCurrentScene() {
	JUMP(0x24035190);
}

NAKED CKRenderContext* CKContext::GetPlayerRenderContext() {
	JUMP(0x240351A9);
}

NAKED void CKContext::SetCurrentLevel(CKLevel* level) {
	JUMP(0x24035172);
}

NAKED CKERROR CKContext::ClearAll() {
	JUMP(0x240354C6);
}

NAKED CKBOOL CKContext::IsInClearAll() {
	JUMP(0x240354BF);
}

NAKED CKBOOL CKContext::IsPlaying() {
	JUMP(0x240354B1);
}

NAKED CKBOOL CKContext::IsReseted() {
	JUMP(0x240354B8);
}

NAKED CKERROR CKContext::Pause() {
	JUMP(0x24035317);
}

NAKED CKERROR CKContext::Play() {
	JUMP(0x240352BB);
}

NAKED CKERROR CKContext::Process() {
	JUMP(0x24035231);
}

NAKED CKERROR CKContext::Reset() {
	JUMP(0x2403532F);
}

NAKED CKBOOL CKContext::IsInInterfaceMode() {
	JUMP(0x24035577);
}

NAKED CKERROR CKContext::OutputToConsole(CKSTRING str, CKBOOL bBeep) {
	JUMP(0x2403557E);
}

NAKED CKERROR CKContext::OutputToConsoleEx(CKSTRING format, ...) {
	JUMP(0x240355B7);
}

NAKED CKERROR CKContext::OutputToConsoleExBeep(CKSTRING format, ...) {
	JUMP(0x2403563A);
}

NAKED CKERROR CKContext::OutputToInfo(CKSTRING format, ...) {
	JUMP(0x2403567B);
}

NAKED CKERROR CKContext::Select(const XObjectArray& o, BOOL clearSelection) {
	JUMP(0x24035707);
}

NAKED CKDWORD CKContext::SendInterfaceMessage(CKDWORD reason, CKDWORD param1, CKDWORD param2, CKDWORD param3) {
	JUMP(0x240357E2);
}

NAKED CKERROR CKContext::ShowSetup(CK_ID) {
	JUMP(0x240356D4);
}

NAKED CKERROR CKContext::UICopyObjects(const XObjectArray& iObjects, CKBOOL iClearClipboard) {
	JUMP(0x24035776);
}

NAKED CKERROR CKContext::UIPasteObjects(const XObjectArray& oObjects) {
	JUMP(0x240357AF);
}

NAKED void CKContext::ActivateManager(CKBaseManager* bm, CKBOOL active) {
	JUMP(0x24035FAD);
}

NAKED CKAttributeManager* CKContext::GetAttributeManager() {
	JUMP(0x2403619B);
}

NAKED CKBehaviorManager* CKContext::GetBehaviorManager() {
	JUMP(0x2403617F);
}

NAKED CKBaseManager* CKContext::GetInactiveManager(int index) {
	JUMP(0x24035F42);
}

NAKED int CKContext::GetInactiveManagerCount() {
	JUMP(0x24035F38);
}

NAKED CKBaseManager* CKContext::GetManager(int index) {
	JUMP(0x24036062);
}

NAKED CKBaseManager* CKContext::GetManagerByGuid(CKGUID guid) {
	JUMP(0x240360AD);
}

NAKED CKBaseManager* CKContext::GetManagerByName(CKSTRING ManagerName) {
	JUMP(0x240360D3);
}

NAKED int CKContext::GetManagerCount() {
	JUMP(0x24035F34);
}

NAKED XManagerHashTableIt CKContext::GetManagers() {
	JUMP(0x2403609D);
}

NAKED CKMessageManager* CKContext::GetMessageManager() {
	JUMP(0x2403618D);
}

NAKED CKParameterManager* CKContext::GetParameterManager() {
	JUMP(0x24036186);
}

NAKED CKPathManager* CKContext::GetPathManager() {
	JUMP(0x240361A2);
}

NAKED CKRenderManager* CKContext::GetRenderManager() {
	JUMP(0x24036156);
}

NAKED CKTimeManager* CKContext::GetTimeManager() {
	JUMP(0x24036194);
}

NAKED CKBOOL CKContext::HasManagerDuplicates(CKBaseManager* bm) {
	JUMP(0x24035F72);
}

NAKED CKBOOL CKContext::IsManagerActive(CKBaseManager* bm) {
	JUMP(0x24035F4F);
}

NAKED CKERROR CKContext::RegisterNewManager(CKBaseManager* manager) {
	JUMP(0x24035ECA);
}

NAKED const XObjectPointerArray& CKContext::CKFillObjectsUnused() {
	JUMP(0x24034EE7);
}

NAKED void CKContext::ChangeObjectDynamic(CKObject* iObject, CKBOOL iSetDynamic) {
	JUMP(0x24035146);
}

NAKED CKObject* CKContext::CopyObject(CKObject* src, CKDependencies* Dependencies, CKSTRING AppendName, CK_OBJECTCREATION_OPTIONS Options) {
	JUMP(0x24034D31);
}

NAKED const XObjectArray& CKContext::CopyObjects(const XObjectArray& SrcObjects, CKDependencies* Dependencies, CK_OBJECTCREATION_OPTIONS Options, CKSTRING AppendName) {
	JUMP(0x24034DC1);
}

NAKED CKObject* CKContext::CreateObject(CK_CLASSID cid, CKSTRING Name, CK_OBJECTCREATION_OPTIONS Options, CK_CREATIONMODE* Res) {
	JUMP(0x24034BF8);
}

NAKED void CKContext::DestroyAllDynamicObjects() {
	JUMP(0x2403513B);
}

NAKED CKERROR CKContext::DestroyObject(CKObject* obj, DWORD Flags, CKDependencies* depoptions) {
	JUMP(0x240350F5);
}

NAKED CKERROR CKContext::DestroyObject(CK_ID id, DWORD Flags, CKDependencies* depoptions) {
	JUMP(0x24035118);
}

NAKED CKERROR CKContext::DestroyObjects(CK_ID* obj_ids, int Count, CKDWORD Flags, CKDependencies* depoptions) {
	JUMP(0x240350AA);
}

NAKED CKObject* CKContext::GetObject(CK_ID ObjID) {
	JUMP(0x24034E9F);
}

NAKED CKObject* CKContext::GetObjectByName(CKSTRING name, CKObject* previous) {
	JUMP(0x24034EC6);
}

NAKED CKObject* CKContext::GetObjectByNameAndClass(CKSTRING name, CK_CLASSID cid, CKObject* previous) {
	JUMP(0x24034ED1);
}

NAKED CKObject* CKContext::GetObjectByNameAndParentClass(CKSTRING name, CK_CLASSID pcid, CKObject* previous) {
	JUMP(0x24034EDC);
}

NAKED int CKContext::GetObjectCount() {
	JUMP(0x24034EBB);
}

NAKED const XObjectPointerArray& CKContext::GetObjectListByType(CK_CLASSID cid, CKBOOL derived) {
	JUMP(0x24035066);
}

NAKED int CKContext::GetObjectSize(CKObject* obj) {
	JUMP(0x24034E8B);
}

NAKED int CKContext::GetObjectsCountByClassID(CK_CLASSID cid) {
	JUMP(0x24035094);
}

NAKED CK_ID* CKContext::GetObjectsListByClassID(CK_CLASSID cid) {
	JUMP(0x2403509F);
}

NAKED CKERROR CKContext::GetFileInfo(CKSTRING FileName, CKFileInfo* FileInfo) {
	JUMP(0x240205E4);
}

NAKED CKERROR CKContext::GetFileInfo(int BufferSize, void* MemoryBuffer, CKFileInfo* FileInfo) {
	JUMP(0x24020655);
}

NAKED void CKContext::EnableProfiling(CKBOOL enable) {
	JUMP(0x240358B7);
}

NAKED float CKContext::GetLastUserProfileTime(CKDWORD UserSlot) {
	JUMP(0x24035886);
}

NAKED void CKContext::GetProfileStats(CKStats* stats) {
	JUMP(0x240358CB);
}

NAKED CKBOOL CKContext::IsProfilingEnable() {
	JUMP(0x240358C4);
}

NAKED void CKContext::UserProfileStart(CKDWORD UserSlot) {
	JUMP(0x2403581A);
}

NAKED float CKContext::UserProfileEnd(CKDWORD UserSlot) {
	JUMP(0x24035846);
}

NAKED CKFile* CKContext::CreateCKFile() {
	JUMP(0x24035B8D);
}

NAKED CKERROR CKContext::DeleteCKFile(CKFile*) {
	JUMP(0x24035BC7);
}

NAKED CKSTRING CKContext::GetLastCmoLoaded() {
	JUMP(0x24035B47);
}

NAKED CKSTRING CKContext::GetLastFileLoaded() {
	JUMP(0x24035B37);
}

NAKED CKBOOL CKContext::IsInLoad() {
	JUMP(0x24035B22);
}

NAKED CKBOOL CKContext::IsInSave() {
	JUMP(0x24035B30);
}

NAKED CKERROR CKContext::Load(CKSTRING FileName, CKObjectArray* liste, CK_LOAD_FLAGS LoadFlags, CKGUID* ReaderGuid) {
	JUMP(0x240358E1);
}

NAKED CKERROR CKContext::Load(int BufferSize, void* MemoryBuffer, CKObjectArray* ckarray, CK_LOAD_FLAGS LoadFlags) {
	JUMP(0x24035926);
}

NAKED CKERROR CKContext::LoadAnimationOnCharacter(CKSTRING FileName, CKObjectArray* liste, CKCharacter* carac, CKGUID* ReaderGuid, BOOL AsDynamicObjects) {
	JUMP(0x240359E5);
}

NAKED CKERROR CKContext::LoadAnimationOnCharacter(int BufferSize, void* MemoryBuffer, CKObjectArray* ckarray, CKCharacter* carac, BOOL AsDynamicObjects) {
	JUMP(0x24035980);
}

NAKED CKERROR CKContext::Save(CKSTRING FileName, CKObjectArray* liste, CKDWORD SaveFlags, CKDependencies* dependencies, CKGUID* ReaderGuid) {
	JUMP(0x24035A10);
}

NAKED void CKContext::SetLastCmoLoaded(CKSTRING str) {
	JUMP(0x24035B57);
}

NAKED int CKContext::GetCompressionLevel() {
	JUMP(0x240351C6);
}

NAKED CK_FILE_WRITEMODE CKContext::GetFileWriteMode() {
	JUMP(0x24035C38);
}

NAKED CKBitmapProperties* CKContext::GetGlobalImagesSaveFormat() {
	JUMP(0x240351FF);
}

NAKED CK_TEXTURE_SAVEOPTIONS CKContext::GetGlobalImagesSaveOptions() {
	JUMP(0x240351CD);
}

NAKED CK_SOUND_SAVEOPTIONS CKContext::GetGlobalSoundsSaveOptions() {
	JUMP(0x240351E6);
}

NAKED void CKContext::SetCompressionLevel(int level) {
	JUMP(0x240351B0);
}

NAKED void CKContext::SetFileWriteMode(CK_FILE_WRITEMODE mode) {
	JUMP(0x24035C2B);
}

NAKED void CKContext::SetGlobalImagesSaveFormat(CKBitmapProperties* Format) {
	JUMP(0x24035206);
}

NAKED void CKContext::SetGlobalImagesSaveOptions(CK_TEXTURE_SAVEOPTIONS Options) {
	JUMP(0x240351D4);
}

NAKED void CKContext::SetGlobalSoundsSaveOptions(CK_SOUND_SAVEOPTIONS Options) {
	JUMP(0x240351ED);
}

NAKED int CKContext::GetSelectedRenderEngine() {
	JUMP(0x240361B0);
}

NAKED CKDWORD CKContext::GetStartOptions() {
	JUMP(0x240361A9);
}

NAKED CKParameterIn* CKContext::CreateCKParameterIn(CKSTRING Name, CKParameterType type, CKBOOL Dynamic) {
	JUMP(0x2403627A);
}

NAKED CKParameterIn* CKContext::CreateCKParameterIn(CKSTRING Name, CKGUID guid, CKBOOL Dynamic) {
	JUMP(0x240362C6);
}

NAKED CKParameterIn* CKContext::CreateCKParameterIn(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic) {
	JUMP(0x240362F0);
}

NAKED CKParameterLocal* CKContext::CreateCKParameterLocal(CKSTRING Name, CKParameterType type, CKBOOL Dynamic) {
	JUMP(0x240363E7);
}

NAKED CKParameterLocal* CKContext::CreateCKParameterLocal(CKSTRING Name, CKGUID guid, CKBOOL Dynamic) {
	JUMP(0x2403642F);
}

NAKED CKParameterLocal* CKContext::CreateCKParameterLocal(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic) {
	JUMP(0x240363C1);
}

NAKED CKParameterOperation* CKContext::CreateCKParameterOperation(CKSTRING Name, CKGUID opguid, CKGUID ResGuid, CKGUID p1Guid, CKGUID p2Guid) {
	JUMP(0x24036459);
}

NAKED CKParameterOut* CKContext::CreateCKParameterOut(CKSTRING Name, CKParameterType type, CKBOOL Dynamic) {
	JUMP(0x24036316);
}

NAKED CKParameterOut* CKContext::CreateCKParameterOut(CKSTRING Name, CKGUID guid, CKBOOL Dynamic) {
	JUMP(0x24036371);
}

NAKED CKParameterOut* CKContext::CreateCKParameterOut(CKSTRING Name, CKSTRING TypeName, CKBOOL Dynamic) {
	JUMP(0x2403639B);
}

NAKED WIN_HANDLE CKContext::GetMainWindow() {
	JUMP(0x2403649D);
}

NAKED CKGUID CKContext::GetSecureGuid() {
	JUMP(0x240361F1);
}

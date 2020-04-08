#include "CKGlobals.h"

NAKED CKERROR CKStartUp() {
	JUMP(0x2403813F);
}

NAKED CKERROR CKShutdown() {
	JUMP(0x2403871A);
}

NAKED CKContext* GetCKContext(int pos) {
	JUMP(0x240387B1);
}

NAKED CKObject* CKGetObject(CKContext* iCtx, CK_ID iID) {
	JUMP(0x24038131);
}

NAKED CKERROR CKCreateContext(CKContext** iContext, WIN_HANDLE iWin, const char* iConfigFile) {
	JUMP(0x240387D0);
}

NAKED CKERROR CKCloseContext(CKContext*) {
	JUMP(0x2403887D);
}

NAKED CKSTRING CKGetStartPath() {
	JUMP(0x2403902A);
}

NAKED CKSTRING CKGetPluginsPath() {
	JUMP(0x24039039);
}

NAKED void CKDestroyObject(CKObject* o, DWORD Flags, CKDependencies* dep) {
	JUMP(0x240396CE);
}

NAKED CKDWORD CKGetVersion() {
	JUMP(0x2403978E);
}

NAKED void CKBuildClassHierarchyTable() {
	JUMP(0x24038D58);
}

NAKED CKPluginManager* CKGetPluginManager() {
	JUMP(0x240396C8);
}

NAKED int CKGetPrototypeDeclarationCount() {
	JUMP(0x24038B85);
}

NAKED CKObjectDeclaration* CKGetPrototypeDeclaration(int n) {
	JUMP(0x24038B47);
}

NAKED XObjDeclHashTableIt CKGetPrototypeDeclarationStartIterator() {
	JUMP(0x24038B25);
}

NAKED XObjDeclHashTableIt CKGetPrototypeDeclarationEndIterator() {
	JUMP(0x24038B38);
}

NAKED CKObjectDeclaration* CKGetObjectDeclarationFromGuid(CKGUID guid) {
	JUMP(0x24038B8B);
}

NAKED CKBehaviorPrototype* CKGetPrototypeFromGuid(CKGUID guid) {
	JUMP(0x240389A0);
}

NAKED CKERROR CKRemovePrototypeDeclaration(CKObjectDeclaration* objdecl) {
	JUMP(0x24038A26);
}

NAKED CKObjectDeclaration* CreateCKObjectDeclaration(CKSTRING Name) {
	JUMP(0x240388BF);
}

NAKED CKBehaviorPrototype* CreateCKBehaviorPrototype(CKSTRING Name) {
	JUMP(0x2403896B);
}

NAKED CKBehaviorPrototype* CreateCKBehaviorPrototypeRunTime(CKSTRING Name) {
	JUMP(0x240388F4);
}

NAKED int CKGetClassCount() {
	JUMP(0x24038CBC);
}

NAKED CKClassDesc* CKGetClassDesc(CK_CLASSID cid) {
	JUMP(0x24038CCE);
}

NAKED CKSTRING CKClassIDToString(CK_CLASSID cid) {
	JUMP(0x24038CDC);
}

NAKED CK_CLASSID CKStringToClassID(CKSTRING classname) {
	JUMP(0x24038D13);
}

NAKED CKBOOL CKIsChildClassOf(CK_CLASSID child, CK_CLASSID parent) {
	JUMP(0x24038BF6);
}

NAKED CKBOOL CKIsChildClassOf(CKObject* obj, CK_CLASSID parent) {
	JUMP(0x24038C3A);
}

NAKED CK_CLASSID CKGetParentClassID(CK_CLASSID child) {
	JUMP(0x24038C75);
}

NAKED CK_CLASSID CKGetParentClassID(CKObject* obj) {
	JUMP(0x24038CA4);
}

NAKED CK_CLASSID CKGetCommonParent(CK_CLASSID cid1, CK_CLASSID cid2) {
	JUMP(0x24038BB9);
}

NAKED CKObjectArray* CreateCKObjectArray() {
	JUMP(0x24038FDE);
}

NAKED void DeleteCKObjectArray(CKObjectArray* obj) {
	JUMP(0x24039011);
}

NAKED CKStateChunk* CreateCKStateChunk(CK_CLASSID id, CKFile* file) {
	JUMP(0x24021AC8);
}

NAKED CKStateChunk* CreateCKStateChunk(CKStateChunk* chunk) {
	JUMP(0x24021B00);
}

NAKED void DeleteCKStateChunk(CKStateChunk* chunk) {
	JUMP(0x24021B35);
}

NAKED CKStateChunk* CKSaveObjectState(CKObject* obj, CKDWORD Flags) {
	JUMP(0x240396E8);
}

NAKED CKERROR CKReadObjectState(CKObject* obj, CKStateChunk* chunk) {
	JUMP(0x240396FF);
}

NAKED BITMAP_HANDLE CKLoadBitmap(CKSTRING filename) {
	JUMP(0x240391FD);
}

NAKED CKBOOL CKSaveBitmap(CKSTRING filename, BITMAP_HANDLE bm) {
	JUMP(0x240390FE);
}

NAKED CKBOOL CKSaveBitmap(CKSTRING filename, VxImageDescEx& desc) {
	JUMP(0x240392D8);
}

NAKED void CKConvertEndianArray32(void* buf, int DwordCount) {
	JUMP(0x2402141A);
}

NAKED void CKConvertEndianArray16(void* buf, int DwordCount) {
	JUMP(0x2402141A);
}

NAKED CKDWORD CKConvertEndian32(CKDWORD dw) {
	JUMP(0x2403944A);
}

NAKED CKWORD CKConvertEndian16(CKWORD w) {
	JUMP(0x2403944F);
}

NAKED CKDWORD CKComputeDataCRC(char* data, int size, DWORD PreviousCRC) {
	JUMP(0x240390E9);
}

NAKED char* CKPackData(char* Data, int size, int& NewSize, int compressionlevel) {
	JUMP(0x24039048);
}

NAKED char* CKUnPackData(int DestSize, char* SrcBuffer, int SrcSize) {
	JUMP(0x240390AB);
}

NAKED CKSTRING CKStrdup(CKSTRING string) {
	JUMP(0x24039717);
}

NAKED CKSTRING CKStrndup(CKSTRING iString, int iLength) {
	UNDEFINED;
}

NAKED void CKStrdelete(CKSTRING str) {
	UNDEFINED;
}

NAKED CKSTRING CKStrupr(CKSTRING string) {
	JUMP(0x24039743);
}

NAKED CKSTRING CKStrlwr(CKSTRING string) {
	JUMP(0x24039766);
}

NAKED CKBitmapProperties* CKCopyBitmapProperties(CKBitmapProperties* bp) {
	JUMP(0x24039694);
}

NAKED void CKCopyDefaultClassDependencies(CKDependencies& d, CK_DEPENDENCIES_OPMODE mode) {
	JUMP(0x240397C2);
}

NAKED CKDependencies* CKGetDefaultClassDependencies(CK_DEPENDENCIES_OPMODE mode) {
	JUMP(0x24039794);
}

NAKED void CKDeletePointer(void* ptr) {
	JUMP(0x24039789);
}

NAKED CKERROR CKCopyAllAttributes(CKBeObject* Src, CKBeObject* Dest) {
	JUMP(0x24039C60);
}

NAKED CKERROR CKMoveAllScripts(CKBeObject* Src, CKBeObject* Dest) {
	JUMP(0x24039EC9);
}

NAKED CKERROR CKMoveScript(CKBeObject* Src, CKBeObject* Dest, CKBehavior* Beh) {
	JUMP(0x24039CDA);
}

NAKED void CKRemapObjectParameterValue(CKContext* ckContext, CK_ID oldID, CK_ID newID, CK_CLASSID cid, CKBOOL derived) {
	JUMP(0x24039F2C);
}

NAKED void CKStoreDeclaration(XObjectDeclarationArray* reg, CKObjectDeclaration* a) {
	JUMP(0x24039834);
}

NAKED void CKClassNeedNotificationFrom(CK_CLASSID Cid1, CK_CLASSID Cid2) {
	JUMP(0x24039A10);
}

NAKED void CKClassRegisterAssociatedParameter(CK_CLASSID Cid, CKGUID pguid) {
	JUMP(0x24039A32);
}

NAKED void CKClassRegisterDefaultDependencies(CK_CLASSID Cid, CKDWORD depend_Mask, int mode) {
	JUMP(0x24039A56);
}

NAKED void CKClassRegisterDefaultOptions(CK_CLASSID Cid, CKDWORD options_Mask) {
	JUMP(0x24039ABC);
}

NAKED CK_CLASSID CKClassGetNewIdentifier() {
	JUMP(0x24039843);
}

NAKED void CKClassRegister(CK_CLASSID Cid, CK_CLASSID Parent_Cid,
	CKCLASSREGISTERFCT registerfct, CKCLASSCREATIONFCT creafct, CKCLASSRELEASEFCT relfct,
	CKCLASSNAMEFCT NameFct, CKCLASSDEPENDENCIESFCT DependsFct,
	CKCLASSDEPENDENCIESCOUNTFCT DependsCountFct) {
	JUMP(0x2403986E);
}

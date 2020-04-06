#include "CKLevel.h"

NAKED CKERROR AddObject(CKObject* obj) {
	JUMP(0x2402C49A);
}

NAKED CKERROR RemoveObject(CKObject* obj) {
	JUMP(0x2402C4DF);
}

NAKED CKERROR RemoveObject(CK_ID obj) {
	JUMP(0x2402C516);
}

NAKED void BeginAddSequence(CKBOOL Begin) {
	JUMP(0x2402C559);
}

NAKED void BeginRemoveSequence(CKBOOL Begin) {
	JUMP(0x2402C56B);
}

NAKED const XObjectPointerArray& ComputeObjectList(CK_CLASSID cid, CKBOOL derived) {
	JUMP(0x2402C57D);
}

NAKED CKERROR AddPlace(CKPlace* pl) {
	JUMP(0x2402C5B0);
}

NAKED CKERROR RemovePlace(CKPlace* pl) {
	JUMP(0x2402C66A);
}

NAKED CKPlace* RemovePlace(int pos) {
	JUMP(0x2402C65A);
}

NAKED CKPlace* GetPlace(int pos) {
	JUMP(0x2402C5D9);
}

NAKED int GetPlaceCount() {
	JUMP(0x2402C623);
}

NAKED CKERROR AddScene(CKScene* scn) {
	JUMP(0x2402C6FB);
}

NAKED CKERROR RemoveScene(CKScene* scn) {
	JUMP(0x2402C6B5);
}

NAKED CKScene* RemoveScene(int pos) {
	JUMP(0x2402C693);
}

NAKED CKScene* GetScene(int pos) {
	JUMP(0x2402C779);
}

NAKED int GetSceneCount() {
	JUMP(0x2402735A);
}

NAKED CKERROR SetNextActiveScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active, CK_SCENEOBJECTRESET_FLAGS Reset) {
	JUMP(0x2402C143);
}

NAKED CKERROR LaunchScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active, CK_SCENEOBJECTRESET_FLAGS Reset) {
	JUMP(0x2402C168);
}

NAKED CKScene* GetCurrentScene() {
	JUMP(0x2402C137);
}

NAKED void AddRenderContext(CKRenderContext*, CKBOOL Main) {
	JUMP(0x2402C2F7);
}

NAKED void RemoveRenderContext(CKRenderContext*) {
	JUMP(0x2402C407);
}

NAKED int GetRenderContextCount() {
	JUMP(0x2402C472);
}

NAKED CKRenderContext* GetRenderContext(int count) {
	JUMP(0x2402C47C);
}

NAKED CKScene* GetLevelScene() {
	JUMP(0x2402C797);
}

NAKED CKERROR Merge(CKLevel* mergedLevel, CKBOOL asScene) {
	JUMP(0x2402C7A3);
}

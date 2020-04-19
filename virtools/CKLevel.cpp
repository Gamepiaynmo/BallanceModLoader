#include "CKLevel.h"

NAKED CKERROR CKLevel::AddObject(CKObject* obj) {
	JUMP(0x2402C49A);
}

NAKED CKERROR CKLevel::RemoveObject(CKObject* obj) {
	JUMP(0x2402C4DF);
}

NAKED CKERROR CKLevel::RemoveObject(CK_ID obj) {
	JUMP(0x2402C516);
}

NAKED void CKLevel::BeginAddSequence(CKBOOL Begin) {
	JUMP(0x2402C559);
}

NAKED void CKLevel::BeginRemoveSequence(CKBOOL Begin) {
	JUMP(0x2402C56B);
}

NAKED const XObjectPointerArray& CKLevel::ComputeObjectList(CK_CLASSID cid, CKBOOL derived) {
	JUMP(0x2402C57D);
}

NAKED CKERROR CKLevel::AddPlace(CKPlace* pl) {
	JUMP(0x2402C5B0);
}

NAKED CKERROR CKLevel::RemovePlace(CKPlace* pl) {
	JUMP(0x2402C66A);
}

NAKED CKPlace* CKLevel::RemovePlace(int pos) {
	JUMP(0x2402C65A);
}

NAKED CKPlace* CKLevel::GetPlace(int pos) {
	JUMP(0x2402C5D9);
}

NAKED int CKLevel::GetPlaceCount() {
	JUMP(0x2402C623);
}

NAKED CKERROR CKLevel::AddScene(CKScene* scn) {
	JUMP(0x2402C6FB);
}

NAKED CKERROR CKLevel::RemoveScene(CKScene* scn) {
	JUMP(0x2402C6B5);
}

NAKED CKScene* CKLevel::RemoveScene(int pos) {
	JUMP(0x2402C693);
}

NAKED CKScene* CKLevel::GetScene(int pos) {
	JUMP(0x2402C779);
}

NAKED int CKLevel::GetSceneCount() {
	JUMP(0x2402735A);
}

NAKED CKERROR CKLevel::SetNextActiveScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active, CK_SCENEOBJECTRESET_FLAGS Reset) {
	JUMP(0x2402C143);
}

NAKED CKERROR CKLevel::LaunchScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active, CK_SCENEOBJECTRESET_FLAGS Reset) {
	JUMP(0x2402C168);
}

NAKED CKScene* CKLevel::GetCurrentScene() {
	JUMP(0x2402C137);
}

NAKED void CKLevel::AddRenderContext(CKRenderContext*, CKBOOL Main) {
	JUMP(0x2402C2F7);
}

NAKED void CKLevel::RemoveRenderContext(CKRenderContext*) {
	JUMP(0x2402C407);
}

NAKED int CKLevel::GetRenderContextCount() {
	JUMP(0x2402C472);
}

NAKED CKRenderContext* CKLevel::GetRenderContext(int count) {
	JUMP(0x2402C47C);
}

NAKED CKScene* CKLevel::GetLevelScene() {
	JUMP(0x2402C797);
}

NAKED CKERROR CKLevel::Merge(CKLevel* mergedLevel, CKBOOL asScene) {
	JUMP(0x2402C7A3);
}

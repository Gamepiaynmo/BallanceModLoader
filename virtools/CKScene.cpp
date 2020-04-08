#include "CKScene.h"

NAKED void CKScene::AddObjectToScene(CKSceneObject* o, CKBOOL dependencies) {
	JUMP(0x2402D2D9);
}

NAKED void CKScene::RemoveObjectFromScene(CKSceneObject* o, CKBOOL dependencies) {
	JUMP(0x2402D30A);
}

NAKED CKBOOL CKScene::IsObjectHere(CKObject* o) {
	JUMP(0x2402D2B7);
}

NAKED void CKScene::BeginAddSequence(CKBOOL Begin) {
	JUMP(0x2402D33F);
}

NAKED void CKScene::BeginRemoveSequence(CKBOOL Begin) {
	JUMP(0x2402D3AE);
}

NAKED int CKScene::GetObjectCount() {
	JUMP(0x2402D41D);
}

NAKED const XObjectPointerArray& CKScene::ComputeObjectList(CK_CLASSID cid, CKBOOL derived) {
	JUMP(0x2402DE9B);
}

NAKED CKSceneObjectIterator CKScene::GetObjectIterator() {
	JUMP(0x2402D421);
}

NAKED void CKScene::Activate(CKSceneObject* o, CKBOOL Reset) {
	JUMP(0x2402D5B1);
}

NAKED void CKScene::DeActivate(CKSceneObject* o) {
	JUMP(0x2402D5F8);
}

NAKED void CKScene::SetObjectFlags(CKSceneObject* o, CK_SCENEOBJECT_FLAGS flags) {
	JUMP(0x2402D4EB);
}

NAKED CK_SCENEOBJECT_FLAGS CKScene::GetObjectFlags(CKSceneObject* o) {
	JUMP(0x2402D538);
}

NAKED CK_SCENEOBJECT_FLAGS CKScene::ModifyObjectFlags(CKSceneObject* o, CKDWORD Add, CKDWORD Remove) {
	JUMP(0x2402D509);
}

NAKED CKBOOL CKScene::SetObjectInitialValue(CKSceneObject* o, CKStateChunk* chunk) {
	JUMP(0x2402D556);
}

NAKED CKStateChunk* CKScene::GetObjectInitialValue(CKSceneObject* o) {
	JUMP(0x2402D59A);
}

NAKED CKBOOL CKScene::IsObjectActive(CKSceneObject* o) {
	JUMP(0x2402D63B);
}

NAKED void CKScene::ApplyEnvironmentSettings(XObjectPointerArray* renderlist) {
	JUMP(0x2402D736);
}

NAKED void CKScene::UseEnvironmentSettings(BOOL use) {
	JUMP(0x2402D8CB);
}

NAKED CKBOOL CKScene::EnvironmentSettings() {
	JUMP(0x2402D8DF);
}

NAKED void CKScene::SetAmbientLight(CKDWORD Color) {
	JUMP(0x2402D65C);
}

NAKED CKDWORD CKScene::GetAmbientLight() {
	JUMP(0x2402D669);
}

NAKED void CKScene::SetFogMode(VXFOG_MODE Mode) {
	JUMP(0x2402D670);
}

NAKED void CKScene::SetFogStart(float Start) {
	JUMP(0x2402D67D);
}

NAKED void CKScene::SetFogEnd(float End) {
	JUMP(0x2402D68A);
}

NAKED void CKScene::SetFogDensity(float Density) {
	JUMP(0x2402D697);
}

NAKED void CKScene::SetFogColor(CKDWORD Color) {
	JUMP(0x2402D6A4);
}

NAKED VXFOG_MODE CKScene::GetFogMode() {
	JUMP(0x2402D6B1);
}

NAKED float CKScene::GetFogStart() {
	JUMP(0x2402D6B8);
}

NAKED float CKScene::GetFogEnd() {
	JUMP(0x2402D6BF);
}

NAKED float CKScene::GetFogDensity() {
	JUMP(0x2402D6C6);
}

NAKED CKDWORD CKScene::GetFogColor() {
	JUMP(0x2402D6CD);
}

NAKED void CKScene::SetBackgroundColor(CKDWORD Color) {
	JUMP(0x2402D6D4);
}

NAKED CKDWORD CKScene::GetBackgroundColor() {
	JUMP(0x2402D6DE);
}

NAKED void CKScene::SetBackgroundTexture(CKTexture* texture) {
	JUMP(0x2402D6E2);
}

NAKED CKTexture* CKScene::GetBackgroundTexture() {
	JUMP(0x2402D6F7);
}

NAKED void CKScene::SetStartingCamera(CKCamera* camera) {
	JUMP(0x2402D703);
}

NAKED CKCamera* CKScene::GetStartingCamera() {
	JUMP(0x2402D72A);
}

NAKED CKLevel* CKScene::GetLevel() {
	JUMP(0x2402D2AB);
}

NAKED CKERROR CKScene::Merge(CKScene* mergedScene, CKLevel* fromLevel) {
	JUMP(0x2402D8E6);
}

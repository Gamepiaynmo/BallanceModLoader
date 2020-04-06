#include "CKSceneObject.h"

NAKED CKBOOL CKSceneObject::IsActiveInScene(CKScene* scene) {
	JUMP(0x24021660);
}

NAKED CKBOOL CKSceneObject::IsActiveInCurrentScene() {
	JUMP(0x2402166D);
}

NAKED CKBOOL CKSceneObject::IsInScene(CKScene* scene) {
	JUMP(0x24021688);
}

NAKED int CKSceneObject::GetSceneInCount() {
	JUMP(0x240216B2);
}

NAKED CKScene* CKSceneObject::GetSceneIn(int index) {
	JUMP(0x240216BA);
}

#include "CKGroup.h"

NAKED CKERROR CKGroup::AddObject(CKBeObject* o) {
	JUMP(0x2402B86F);
}

NAKED CKERROR CKGroup::AddObjectFront(CKBeObject* o) {
	JUMP(0x2402B8CB);
}

NAKED CKERROR CKGroup::InsertObjectAt(CKBeObject* o, int pos) {
	JUMP(0x2402B929);
}

NAKED CKBeObject* CKGroup::RemoveObject(int pos) {
	JUMP(0x2402B997);
}

NAKED void CKGroup::RemoveObject(CKBeObject* obj) {
	JUMP(0x2402B9E9);
}

NAKED void CKGroup::Clear() {
	JUMP(0x2402BAA8);
}

NAKED void CKGroup::MoveObjectUp(CKBeObject* o) {
	JUMP(0x2402BA1B);
}

NAKED void CKGroup::MoveObjectDown(CKBeObject* o) {
	JUMP(0x2402BA4F);
}

NAKED CKBeObject* CKGroup::GetObject(int pos) {
	JUMP(0x2402BA85);
}

NAKED int CKGroup::GetObjectCount() {
	JUMP(0x2402735A);
}

NAKED CK_CLASSID CKGroup::GetCommonClassID() {
	JUMP(0x2402BADA);
}

#include "CKBehaviorManager.h"

NAKED CKERROR CKBehaviorManager::Execute(float delta) {
	JUMP(0x2400C40C);
}

NAKED CKERROR CKBehaviorManager::AddObject(CKBeObject* b) {
	UNDEFINED;
}

NAKED CKERROR CKBehaviorManager::RemoveObject(CKBeObject* b) {
	UNDEFINED;
}

NAKED int CKBehaviorManager::GetObjectsCount() {
	JUMP(0x24002E87);
}

NAKED CKERROR CKBehaviorManager::RemoveAllObjects() {
	UNDEFINED;
}

NAKED CKBeObject* CKBehaviorManager::GetObject(int pos) {
	JUMP(0x2400C5D9);
}

NAKED CKERROR CKBehaviorManager::AddObjectNextFrame(CKBeObject* b) {
	UNDEFINED;
}

NAKED CKERROR CKBehaviorManager::RemoveObjectNextFrame(CKBeObject* b) {
	UNDEFINED;
}

NAKED int CKBehaviorManager::GetBehaviorMaxIteration() {
	JUMP(0x2402D41D);
}

NAKED void CKBehaviorManager::SetBehaviorMaxIteration(int n) {
	JUMP(0x2400C6B1);
}

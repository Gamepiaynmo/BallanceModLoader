#include "CKStateObject.h"

NAKED CKBOOL CKStateObject::IsStateActive() {
	JUMP(0x2400CEFF);
}

NAKED void CKStateObject::EnterState() {
	JUMP(0x240263C9);
}

NAKED void CKStateObject::LeaveState() {
	JUMP(0x240263D1);
}

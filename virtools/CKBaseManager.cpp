#include "CKBaseManager.h"

NAKED CKGUID CKBaseManager::GetGuid() {
	JUMP(0x2403AB25);
}

NAKED CKSTRING CKBaseManager::GetName() {
	JUMP(0x2403AB37);
}
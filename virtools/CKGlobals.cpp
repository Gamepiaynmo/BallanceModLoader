#include "CKGlobals.h"

CKSTRING CKStrdup(CKSTRING string) {
	JUMP(0x24039717);
}

CKSTRING CKStrndup(CKSTRING iString, int iLength) {
	UNDEFINED;
}

void CKStrdelete(CKSTRING str) {
	UNDEFINED;
}

CKSTRING CKStrupr(CKSTRING string) {
	JUMP(0x24039743);
}

CKSTRING CKStrlwr(CKSTRING string) {
	JUMP(0x24039766);
}
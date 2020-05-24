#include "CKBehaviorIO.h"

void CKBehaviorIO::SetType(int Type) {
	GET_MEM(0xc, CKDWORD) &= ~CK_OBJECT_IOTYPEMASK;
	GET_MEM(0xc, CKDWORD) |= Type;
}

int CKBehaviorIO::GetType() {
	return GET_MEM(0xc, CKDWORD) & CK_OBJECT_IOTYPEMASK;
}

void CKBehaviorIO::Activate(CKBOOL Active) {
	if (Active)
		GET_MEM(0xc, CKDWORD) |= CK_BEHAVIORIO_ACTIVE;
	else GET_MEM(0xc, CKDWORD) &= ~CK_BEHAVIORIO_ACTIVE;
}

CKBOOL CKBehaviorIO::IsActive() {
	return (GET_MEM(0xc, CKDWORD) & CK_BEHAVIORIO_ACTIVE);
}

CKBehavior* CKBehaviorIO::GetOwner() {
	RETURN_MEM(0x1c, CKBehavior*);
}

XSObjectPointerArray* CKBehaviorIO::GetLinks() {
	RETURN_MEMPTR(0x14, XSObjectPointerArray);
}


NAKED CKERROR CKBehaviorLink::SetOutBehaviorIO(CKBehaviorIO* ckbioin) {
	JUMP(0x24006BDA);
}

NAKED CKERROR CKBehaviorLink::SetInBehaviorIO(CKBehaviorIO* ckbioout) {
	JUMP(0x24006B92);
}

CKBehaviorIO* CKBehaviorLink::GetOutBehaviorIO() {
	RETURN_MEM(0x20, CKBehaviorIO*);
}

CKBehaviorIO* CKBehaviorLink::GetInBehaviorIO() {
	RETURN_MEM(0x1c, CKBehaviorIO*);
}

int CKBehaviorLink::GetActivationDelay() {
	RETURN_MEM(0x14, short);
}

void CKBehaviorLink::SetActivationDelay(int delay) {
	SET_MEM(0x14, short, delay);
}

void CKBehaviorLink::ResetActivationDelay() {
	SET_MEM(0x14, short, GET_MEM(0x16, short));
}

void CKBehaviorLink::SetInitialActivationDelay(int delay) {
	SET_MEM(0x16, short, delay);
}

int CKBehaviorLink::GetInitialActivationDelay() {
	RETURN_MEM(0x16, short);
}
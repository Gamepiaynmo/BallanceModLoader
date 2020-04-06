#include "CKParameterIn.h"
#include "CKParameter.h"

CKERROR CKParameterIn::GetValue(void* buf) {
	CKParameter* p = GetRealSource();
	if (!p) return CKERR_NOTINITIALIZED;
	return p->GetValue(buf);
}

void* CKParameterIn::GetReadDataPtr() {
	CKParameter* p = GetRealSource();
	if (!p) return NULL;
	return p->GetReadDataPtr();
}

CKParameterIn* CKParameterIn::GetSharedSource() {
	return (!(GET_MEM(0xc, CKDWORD) & CK_PARAMETERIN_SHARED)) ? NULL : GET_MEM(0x18, CKParameterIn*);
}

CKParameter* CKParameterIn::GetRealSource() {
	if (GET_MEM(0xc, CKDWORD) & CK_PARAMETERIN_SHARED) {
		if (GET_MEM(0x18, CKParameterIn*)) return GET_MEM(0x18, CKParameterIn*)->GetRealSource();
	}
	else return GET_MEM(0x18, CKParameter*);

	return NULL;
}

CKParameter* CKParameterIn::GetDirectSource() {
	if (GET_MEM(0xc, CKDWORD) & CK_PARAMETERIN_SHARED) return NULL;
	return GET_MEM(0x18, CKParameter*);
}

NAKED CKERROR CKParameterIn::SetDirectSource(CKParameter* param) {
	JUMP(0x24008C7A);
}

NAKED CKERROR CKParameterIn::ShareSourceWith(CKParameterIn* param) {
	JUMP(0x24008BE6);
}

NAKED void CKParameterIn::SetType(CKParameterType type, CKBOOL UpdateSource, CKSTRING NewName) {
	JUMP(0x24008D10);
}

NAKED void CKParameterIn::SetGUID(CKGUID guid, CKBOOL UpdateSource, CKSTRING NewName) {
	JUMP(0x24008DC0);
}

CKParameterType CKParameterIn::GetType() {
	if (GET_MEM(0x1c, CKParameterTypeDesc*)) return GET_MEM(0x1c, CKParameterTypeDesc*)->Index;
	else return -1;
}

CKGUID CKParameterIn::GetGUID() {
	if (GET_MEM(0x1c, CKParameterTypeDesc*)) return GET_MEM(0x1c, CKParameterTypeDesc*)->Guid;
	else return CKGUID(0);
}

void CKParameterIn::SetOwner(CKObject* o) {
	SET_MEM(0x14, CKObject*, o);
}

CKObject* CKParameterIn::GetOwner() {
	RETURN_MEM(0x14, CKObject*);
}
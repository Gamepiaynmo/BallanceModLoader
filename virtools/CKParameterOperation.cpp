#include "CKParameterOperation.h"

CKParameterIn* CKParameterOperation::GetInParameter1() {
	RETURN_MEM(0x14, CKParameterIn*);
}

CKParameterIn* CKParameterOperation::GetInParameter2() {
	RETURN_MEM(0x18, CKParameterIn*);
}

CKParameterOut* CKParameterOperation::GetOutParameter() {
	RETURN_MEM(0x1c, CKParameterOut*);
}

CKBehavior* CKParameterOperation::GetOwner() {
	RETURN_MEM(0x20, CKBehavior*);
}

void CKParameterOperation::SetOwner(CKBehavior* beh) {
	SET_MEM(0x20, CKBehavior*, beh);
}

NAKED CKERROR CKParameterOperation::DoOperation() {
	JUMP(0x240098BB);
}

NAKED CKGUID CKParameterOperation::GetOperationGuid() {
	JUMP(0x240098A9);
}

NAKED void CKParameterOperation::Reconstruct(CKSTRING Name, CKGUID opguid, CKGUID ResGuid, CKGUID p1Guid, CKGUID p2Guid) {
	JUMP(0x240097DD);
}

NAKED CK_PARAMETEROPERATION CKParameterOperation::GetOperationFunction() {
	JUMP(0x24017AE9);
}
#include "CKParameter.h"

NAKED void CKParameter::CheckClass(CKParameterTypeDesc* iType) {
	JUMPV(0x68);
}

NAKED CKObject* CKParameter::GetOwner() {
	JUMP(0x2400CEFF);
}

NAKED void CKParameter::SetOwner(CKObject* o) {
	JUMPV(0x64);
}

NAKED CKGUID CKParameter::GetGUID() {
	JUMP(0x24008019);
}

NAKED CK_CLASSID CKParameter::GetParameterClassID() {
	JUMP(0x2400803B);
}

NAKED CKParameterType CKParameter::GetType() {
	JUMP(0x2400800B);
}

NAKED CKBOOL CKParameter::IsCompatibleWith(CKParameter* param) {
	JUMP(0x24008049);
}

NAKED void CKParameter::SetType(CKParameterType type) {
	JUMP(0x24008073);
}

NAKED void CKParameter::SetGUID(CKGUID guid) {
	JUMP(0x2400817C);
}

NAKED CKERROR CKParameter::CopyValue(CKParameter* param, CKBOOL UpdateParam) {
	JUMPV(0x50);
}

NAKED int CKParameter::GetDataSize() {
	JUMP(0x2400829A);
}

NAKED void* CKParameter::GetReadDataPtr(CKBOOL update) {
	JUMPV(0x54);
}

NAKED int CKParameter::GetStringValue(CKSTRING Value, CKBOOL update) {
	JUMPV(0x60);
}

NAKED CKERROR CKParameter::GetValue(void* buf, CKBOOL update) {
	JUMPV(0x48);
}

NAKED CKObject* CKParameter::GetValueObject(CKBOOL update) {
	JUMP(0x240081AB);
}

NAKED void* CKParameter::GetWriteDataPtr() {
	JUMPV(0x58);
}

NAKED CKERROR CKParameter::SetStringValue(CKSTRING Value) {
	JUMPV(0x5c);
}

NAKED CKERROR CKParameter::SetValue(const void* buf, int size) {
	JUMPV(0x4c);
}


NAKED void CKParameterOut::DataChanged() {
	JUMP(0x2400A4D3);
}

NAKED CKERROR CKParameterOut::AddDestination(CKParameter* param, CKBOOL CheckType) {
	JUMP(0x2400A363);
}

NAKED void CKParameterOut::RemoveDestination(CKParameter* param) {
	JUMP(0x2400A3E5);
}

NAKED int CKParameterOut::GetDestinationCount() {
	JUMP(0x24002962);
}

NAKED CKParameter* CKParameterOut::GetDestination(int pos) {
	JUMP(0x240029E3);
}

NAKED void CKParameterOut::RemoveAllDestinations() {
	JUMP(0x2400A3CF);
}
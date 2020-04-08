#include "CKParameterManager.h"

NAKED CKERROR CKParameterManager::RegisterParameterType(CKParameterTypeDesc* param_type) {
	JUMP(0x240101FD);
}

NAKED CKERROR CKParameterManager::UnRegisterParameterType(CKGUIDCONSTREF guid) {
	JUMP(0x24010417);
}

NAKED CKParameterTypeDesc* CKParameterManager::GetParameterTypeDescription(int type) {
	JUMP(0x24010079);
}

NAKED CKParameterTypeDesc* CKParameterManager::GetParameterTypeDescription(CKGUIDCONSTREF guid) {
	JUMP(0x2401009B);
}

NAKED int CKParameterManager::GetParameterSize(CKParameterType type) {
	JUMP(0x24010686);
}

NAKED int CKParameterManager::GetParameterTypesCount() {
	JUMP(0x2400278E);
}

NAKED CKERROR CKParameterManager::ChangeParametersGuid(CKGUIDCONSTREF iOldGuid, CKGUIDCONSTREF iNewGuid) {
	UNDEFINED;
}

NAKED CKParameterType CKParameterManager::ParameterGuidToType(CKGUIDCONSTREF guid) {
	JUMP(0x2401075D);
}

NAKED CKSTRING CKParameterManager::ParameterGuidToName(CKGUIDCONSTREF guid) {
	JUMP(0x24010783);
}

NAKED CKGUID CKParameterManager::ParameterTypeToGuid(CKParameterType type) {
	JUMP(0x240108CB);
}

NAKED CKSTRING CKParameterManager::ParameterTypeToName(CKParameterType type) {
	JUMP(0x24010904);
}

NAKED CKGUID CKParameterManager::ParameterNameToGuid(CKSTRING name) {
	JUMP(0x2401081F);
}

NAKED CKParameterType CKParameterManager::ParameterNameToType(CKSTRING name) {
	JUMP(0x2401079F);
}

NAKED CKBOOL CKParameterManager::IsDerivedFrom(CKGUIDCONSTREF guid1, CKGUIDCONSTREF parent) {
	JUMP(0x24010183);
}

NAKED CKBOOL CKParameterManager::IsDerivedFrom(CKParameterType child, CKParameterType parent) {
	JUMP(0x240101AF);
}

NAKED CKBOOL CKParameterManager::IsTypeCompatible(CKGUIDCONSTREF guid1, CKGUIDCONSTREF guid2) {
	JUMP(0x240100BE);
}

NAKED CKBOOL CKParameterManager::IsTypeCompatible(CKParameterType Ptype1, CKParameterType Ptype2) {
	JUMP(0x240100FF);
}

NAKED CK_CLASSID CKParameterManager::TypeToClassID(CKParameterType type) {
	JUMP(0x240106A6);
}

NAKED CK_CLASSID CKParameterManager::GuidToClassID(CKGUIDCONSTREF guid) {
	JUMP(0x240106C6);
}

NAKED CKParameterType CKParameterManager::ClassIDToType(CK_CLASSID cid) {
	JUMP(0x24010738);
}

NAKED CKGUID CKParameterManager::ClassIDToGuid(CK_CLASSID cid) {
	JUMP(0x240106EB);
}

NAKED CKERROR CKParameterManager::RegisterNewFlags(CKGUIDCONSTREF FlagsGuid, CKSTRING FlagsName, CKSTRING FlagsData) {
	JUMP(0x24011CB9);
}

NAKED CKERROR CKParameterManager::RegisterNewEnum(CKGUIDCONSTREF EnumGuid, CKSTRING EnumName, CKSTRING EnumData) {
	JUMP(0x240119E0);
}

NAKED CKERROR CKParameterManager::ChangeEnumDeclaration(CKGUIDCONSTREF EnumGuid, CKSTRING EnumData) {
	JUMP(0x240124C8);
}

NAKED CKERROR CKParameterManager::ChangeFlagsDeclaration(CKGUIDCONSTREF FlagsGuid, CKSTRING FlagsData) {
	JUMP(0x240126ED);
}

NAKED CKERROR CKParameterManager::RegisterNewStructure(CKGUIDCONSTREF StructGuid, CKSTRING StructName, CKSTRING Structdata, ...) {
	JUMP(0x24011F56);
}

NAKED CKERROR CKParameterManager::RegisterNewStructure(CKGUIDCONSTREF StructGuid, CKSTRING StructName, CKSTRING StructData, XArray<CKGUID>& ListGuid) {
	JUMP(0x2401220A);
}

NAKED int CKParameterManager::GetNbFlagDefined() {
	JUMP(0x24011937);
}

NAKED int CKParameterManager::GetNbEnumDefined() {
	JUMP(0x2402D6B1);
}

NAKED int CKParameterManager::GetNbStructDefined() {
	JUMP(0x2402D669);
}

NAKED CKFlagsStruct* CKParameterManager::GetFlagsDescByType(CKParameterType pType) {
	JUMP(0x2401193B);
}

NAKED CKEnumStruct* CKParameterManager::GetEnumDescByType(CKParameterType pType) {
	JUMP(0x2401196E);
}

NAKED CKStructStruct* CKParameterManager::GetStructDescByType(CKParameterType pType) {
	JUMP(0x240119A7);
}

NAKED CKOperationType CKParameterManager::RegisterOperationType(CKGUIDCONSTREF OpCode, CKSTRING name) {
	JUMP(0x2401092F);
}

NAKED CKERROR CKParameterManager::UnRegisterOperationType(CKGUIDCONSTREF opguid) {
	JUMP(0x24010B2F);
}

NAKED CKERROR CKParameterManager::UnRegisterOperationType(CKOperationType opcode) {
	JUMP(0x24010AA2);
}

NAKED CKERROR CKParameterManager::RegisterOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2, CK_PARAMETEROPERATION op) {
	JUMP(0x24010B4B);
}

NAKED CK_PARAMETEROPERATION CKParameterManager::GetOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2) {
	JUMP(0x24010F6D);
}

NAKED CKERROR CKParameterManager::UnRegisterOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2) {
	JUMP(0x24010EBF);
}

NAKED CKGUID CKParameterManager::OperationCodeToGuid(CKOperationType type) {
	JUMP(0x240117A1);
}

NAKED CKSTRING CKParameterManager::OperationCodeToName(CKOperationType type) {
	JUMP(0x240117D8);
}

NAKED CKOperationType CKParameterManager::OperationGuidToCode(CKGUIDCONSTREF guid) {
	JUMP(0x24011812);
}

NAKED CKSTRING CKParameterManager::OperationGuidToName(CKGUIDCONSTREF guid) {
	JUMP(0x240117F6);
}

NAKED CKGUID CKParameterManager::OperationNameToGuid(CKSTRING name) {
	JUMP(0x240118AE);
}

NAKED CKOperationType CKParameterManager::OperationNameToCode(CKSTRING name) {
	JUMP(0x24011838);
}

NAKED int CKParameterManager::GetAvailableOperationsDesc(const CKGUID& opGuid, CKParameterOut* res, CKParameterIn* p1, CKParameterIn* p2, CKOperationDesc* list) {
	JUMP(0x2401114C);
}

NAKED int CKParameterManager::GetParameterOperationCount() {
	JUMP(0x2401179D);
}

NAKED CKBOOL CKParameterManager::IsParameterTypeToBeShown(CKParameterType type) {
	JUMP(0x24012FAD);
}

NAKED CKBOOL CKParameterManager::IsParameterTypeToBeShown(CKGUIDCONSTREF guid) {
	JUMP(0x24012EBD);
}

NAKED CKBOOL CKParameterManager::CheckParamTypeValidity(CKParameterType type) {
	UNDEFINED;
}

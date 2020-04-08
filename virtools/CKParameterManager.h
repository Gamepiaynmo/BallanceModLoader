#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"
#include "CKParameter.h"

#define  CKGUIDCONSTREF CKGUID			
#define  CKGUIDREF		CKGUID&	
typedef void	(*CK_PARAMETEROPERATION)	(CKContext* context, CKParameterOut* Res, CKParameterIn* p1, CKParameterIn* p2);
typedef struct CKOperationDesc {
	CKGUID OpGuid;
	CKGUID P1Guid;
	CKGUID P2Guid;
	CKGUID ResGuid;
	CK_PARAMETEROPERATION Fct;
} CKOperationDesc;

class BML_EXPORT CKParameterManager : public CKBaseManager {
public:
	CKERROR RegisterParameterType(CKParameterTypeDesc* param_type);
	CKERROR UnRegisterParameterType(CKGUIDCONSTREF guid);
	CKParameterTypeDesc* GetParameterTypeDescription(int type);
	CKParameterTypeDesc* GetParameterTypeDescription(CKGUIDCONSTREF guid);
	int GetParameterSize(CKParameterType type);
	int GetParameterTypesCount();
	CKERROR ChangeParametersGuid(CKGUIDCONSTREF iOldGuid, CKGUIDCONSTREF iNewGuid);
	CKParameterType ParameterGuidToType(CKGUIDCONSTREF guid);
	CKSTRING ParameterGuidToName(CKGUIDCONSTREF guid);
	CKGUID ParameterTypeToGuid(CKParameterType type);
	CKSTRING ParameterTypeToName(CKParameterType type);
	CKGUID ParameterNameToGuid(CKSTRING name);
	CKParameterType ParameterNameToType(CKSTRING name);
	CKBOOL IsDerivedFrom(CKGUIDCONSTREF guid1, CKGUIDCONSTREF parent);
	CKBOOL IsDerivedFrom(CKParameterType child, CKParameterType parent);
	CKBOOL IsTypeCompatible(CKGUIDCONSTREF guid1, CKGUIDCONSTREF guid2);
	CKBOOL IsTypeCompatible(CKParameterType Ptype1, CKParameterType Ptype2);
	CK_CLASSID TypeToClassID(CKParameterType type);
	CK_CLASSID GuidToClassID(CKGUIDCONSTREF guid);
	CKParameterType ClassIDToType(CK_CLASSID cid);
	CKGUID ClassIDToGuid(CK_CLASSID cid);
	CKERROR RegisterNewFlags(CKGUIDCONSTREF FlagsGuid, CKSTRING FlagsName, CKSTRING FlagsData);
	CKERROR RegisterNewEnum(CKGUIDCONSTREF EnumGuid, CKSTRING EnumName, CKSTRING EnumData);
	CKERROR ChangeEnumDeclaration(CKGUIDCONSTREF EnumGuid, CKSTRING EnumData);
	CKERROR ChangeFlagsDeclaration(CKGUIDCONSTREF FlagsGuid, CKSTRING FlagsData);
	CKERROR RegisterNewStructure(CKGUIDCONSTREF StructGuid, CKSTRING StructName, CKSTRING Structdata, ...);
	CKERROR RegisterNewStructure(CKGUIDCONSTREF StructGuid, CKSTRING StructName, CKSTRING StructData, XArray<CKGUID>& ListGuid);
	int GetNbFlagDefined();
	int GetNbEnumDefined();
	int GetNbStructDefined();
	CKFlagsStruct* GetFlagsDescByType(CKParameterType pType);
	CKEnumStruct* GetEnumDescByType(CKParameterType pType);
	CKStructStruct* GetStructDescByType(CKParameterType pType);
	CKOperationType RegisterOperationType(CKGUIDCONSTREF OpCode, CKSTRING name);
	CKERROR UnRegisterOperationType(CKGUIDCONSTREF opguid);
	CKERROR UnRegisterOperationType(CKOperationType opcode);
	CKERROR RegisterOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2, CK_PARAMETEROPERATION op);
	CK_PARAMETEROPERATION GetOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2);
	CKERROR UnRegisterOperationFunction(CKGUIDREF operation, CKGUIDREF type_paramres, CKGUIDREF type_param1, CKGUIDREF type_param2);
	CKGUID OperationCodeToGuid(CKOperationType type);
	CKSTRING OperationCodeToName(CKOperationType type);
	CKOperationType OperationGuidToCode(CKGUIDCONSTREF guid);
	CKSTRING OperationGuidToName(CKGUIDCONSTREF guid);
	CKGUID OperationNameToGuid(CKSTRING name);
	CKOperationType OperationNameToCode(CKSTRING name);
	int GetAvailableOperationsDesc(const CKGUID& opGuid, CKParameterOut* res, CKParameterIn* p1, CKParameterIn* p2, CKOperationDesc* list);
	int GetParameterOperationCount();
	CKBOOL IsParameterTypeToBeShown(CKParameterType type);
	CKBOOL IsParameterTypeToBeShown(CKGUIDCONSTREF guid);
	CKBOOL CheckParamTypeValidity(CKParameterType type);

protected:
	CKParameterManager() {};
	~CKParameterManager() {};
};
#pragma once

#include "CKDef.h"
#include "CKObject.h"

typedef void (*CK_PARAMETEROPERATION) (CKContext* context, CKParameterOut* Res, CKParameterIn* p1, CKParameterIn* p2);

class BML_EXPORT CKParameterOperation : public CKObject {
public:
	CKParameterIn* GetInParameter1();
	CKParameterIn* GetInParameter2();
	CKParameterOut* GetOutParameter();
	CKBehavior* GetOwner();
	void SetOwner(CKBehavior* beh);

	CKERROR DoOperation();
	CKGUID GetOperationGuid();
	void Reconstruct(CKSTRING Name, CKGUID opguid, CKGUID ResGuid, CKGUID p1Guid, CKGUID p2Guid);
	CK_PARAMETEROPERATION GetOperationFunction();

protected:
	CKParameterOperation();
	~CKParameterOperation();
};
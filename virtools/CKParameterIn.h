#pragma once

#include "CKDef.h"
#include "CKObject.h"

class BML_EXPORT CKParameterIn : public CKObject {
public:
	CKERROR GetValue(void* buf);
	void* GetReadDataPtr();
	CKParameterIn* GetSharedSource();
	CKParameter* GetRealSource();
	CKParameter* GetDirectSource();
	CKERROR SetDirectSource(CKParameter* param);
	CKERROR ShareSourceWith(CKParameterIn* param);
	void SetType(CKParameterType type, CKBOOL UpdateSource = FALSE, CKSTRING NewName = NULL);
	void SetGUID(CKGUID guid, CKBOOL UpdateSource = FALSE, CKSTRING NewName = NULL);
	CKParameterType GetType();
	CKGUID GetGUID();
	void SetOwner(CKObject* o);
	CKObject* GetOwner();

protected:
	CKParameterIn() {};
	~CKParameterIn() {};
};
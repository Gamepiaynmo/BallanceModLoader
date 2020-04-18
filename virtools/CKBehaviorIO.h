#pragma once

#include "CKDef.h"
#include "CKObject.h"

class BML_EXPORT CKBehaviorIO : public CKObject {
public:
	void SetType(int Type);
	int GetType();
	void Activate(CKBOOL Active = TRUE);
	CKBOOL IsActive();
	CKBehavior* GetOwner();
	XSObjectPointerArray* GetLinks();

protected:
	CKBehaviorIO() {};
	~CKBehaviorIO() {};
};

class BML_EXPORT CKBehaviorLink : public CKObject {
public:
	CKERROR SetOutBehaviorIO(CKBehaviorIO* ckbioin);
	CKERROR SetInBehaviorIO(CKBehaviorIO* ckbioout);
	CKBehaviorIO* GetOutBehaviorIO();
	CKBehaviorIO* GetInBehaviorIO();
	int GetActivationDelay();
	void SetActivationDelay(int delay);
	void ResetActivationDelay();
	void SetInitialActivationDelay(int delay);
	int GetInitialActivationDelay();

protected:
	CKBehaviorLink() {};
	~CKBehaviorLink() {};
};
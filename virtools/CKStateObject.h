#pragma once

#include "CKDef.h"
#include "CKObject.h"

class BML_EXPORT CKStateObject : public CKObject {
public:
	CKBOOL IsStateActive();
	void EnterState();
	void LeaveState();

protected:
	CKStateObject() {};
	~CKStateObject() {};
};
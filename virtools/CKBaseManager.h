#pragma once

#include "CKDef.h"

class BML_EXPORT CKBaseManager {
public:
	CKGUID GetGuid();
	CKSTRING GetName();

protected:
	CKBaseManager() {};
	~CKBaseManager() {};
};
#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

#undef GetObject

class BML_EXPORT CKBehaviorManager : public CKBaseManager {
public:
	CKERROR Execute(float delta);
	CKERROR AddObject(CKBeObject* b);
	CKERROR RemoveObject(CKBeObject* b);
	int GetObjectsCount();
	CKERROR RemoveAllObjects();
	CKBeObject* GetObject(int pos);
	CKERROR AddObjectNextFrame(CKBeObject* b);
	CKERROR RemoveObjectNextFrame(CKBeObject* b);
	int GetBehaviorMaxIteration();
	void SetBehaviorMaxIteration(int n);

protected:
	CKBehaviorManager() {};
	~CKBehaviorManager() {};
};
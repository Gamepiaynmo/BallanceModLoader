#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

#undef GetObject

class BML_EXPORT CKGroup : public CKBeObject {
public:
	CKERROR AddObject(CKBeObject* o);
	CKERROR AddObjectFront(CKBeObject* o);
	CKERROR InsertObjectAt(CKBeObject* o, int pos);

	CKBeObject* RemoveObject(int pos);
	void RemoveObject(CKBeObject* obj);
	void Clear();

	void MoveObjectUp(CKBeObject* o);
	void MoveObjectDown(CKBeObject* o);

	CKBeObject* GetObject(int pos);
	int GetObjectCount();

	CK_CLASSID GetCommonClassID();

protected:
	CKGroup() {};
	~CKGroup() {};
};
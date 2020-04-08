#pragma once

#include "CKDef.h"

typedef int (*OBJECTARRAYCMPFCT)(CKObject* elem1, CKObject* elem2);

class BML_EXPORT CKObjectArray {
public:
	int GetCount();
	int GetCurrentPos();
	CKObject* GetData(CKContext* context);
	CK_ID GetDataId();
	CK_ID SetDataId(CK_ID id);
	CK_ID SetData(CKObject* obj);
	void Reset();
	CKBOOL PtrSeek(CKObject*);
	CKBOOL IDSeek(CK_ID id);
	CKBOOL PositionSeek(int Pos);
	CK_ID Seek(int Pos);
	void Next();
	void Previous();
	int GetPosition(CKObject* o);
	int GetPosition(CK_ID id);
	CK_ID PtrFind(CKObject*);
	CK_ID IDFind(CK_ID id);
	CK_ID PositionFind(int pos);
	void InsertFront(CKObject* obj);
	void InsertRear(CKObject* obj);
	void InsertAt(CKObject* obj);
	CKBOOL AddIfNotHere(CKObject* obj);
	CKBOOL AddIfNotHereSorted(CKObject* obj, OBJECTARRAYCMPFCT CmpFct, CKContext* context);
	void InsertFront(CK_ID id);
	void InsertRear(CK_ID id);
	void InsertAt(CK_ID id);
	CKBOOL AddIfNotHere(CK_ID id);
	CKBOOL AddIfNotHereSorted(CK_ID id, OBJECTARRAYCMPFCT CmpFct, CKContext* context);
	CKERROR Append(CKObjectArray* array);
	CK_ID RemoveFront();
	CK_ID RemoveRear();
	CK_ID RemoveAt();
	CKBOOL Remove(CKObject*);
	CKBOOL Remove(CK_ID id);
	void Clear();
	CKBOOL EndOfList();
	CKBOOL ListEmpty();
	void SwapCurrentWithNext();
	void SwapCurrentWithPrevious();
	CKBOOL Check(CKContext* context);
	void Sort(OBJECTARRAYCMPFCT CmpFct, CKContext* context);
	void InsertSorted(CKObject* o, OBJECTARRAYCMPFCT CmpFct, CKContext* context);
	void InsertSorted(CK_ID id, OBJECTARRAYCMPFCT CmpFct, CKContext* context);

protected:
	CKObjectArray() {};
	~CKObjectArray() {};
};
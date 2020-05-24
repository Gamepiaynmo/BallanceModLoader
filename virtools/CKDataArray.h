#pragma once

#include "CKDef.h"
#include "CKBeObject.h"
#include "CKGlobals.h"

typedef XSArray<CKDWORD> CKDataRow;

class BML_EXPORT CKDataArray : public CKBeObject {
public:
	void InsertColumn(int cdest, CK_ARRAYTYPE type, char* name, CKGUID paramguid = CKGUID(0, 0));
	void MoveColumn(int csrc, int cdest);
	void RemoveColumn(int c);
	void SetColumnName(int c, char* name);
	char* GetColumnName(int c);
	void SetColumnType(int c, CK_ARRAYTYPE type, CKGUID paramguid = CKGUID(0, 0));
	CK_ARRAYTYPE GetColumnType(int c);
	CKGUID GetColumnParameterGuid(int c);
	int GetKeyColumn();
	void SetKeyColumn(int c);
	int GetColumnCount();

	CKDWORD* GetElement(int i, int c);
	CKBOOL GetElementValue(int i, int c, void* value);
	CKObject* GetElementObject(int i, int c);

	CKBOOL SetElementValue(int i, int c, void* value, int size = 0);
	CKBOOL SetElementValueFromParameter(int i, int c, CKParameter* pout);
	CKBOOL SetElementObject(int i, int c, CKObject* object);

	CKBOOL PasteShortcut(int i, int c, CKParameter* pout);
	CKParameterOut* RemoveShortcut(int i, int c);

	CKBOOL SetElementStringValue(int i, int c, const char* svalue);
	int GetStringValue(CKDWORD key, int c, char* svalue);
	int GetElementStringValue(int i, int c, char* svalue);

	CKBOOL LoadElements(CKSTRING string, CKBOOL append, int column);
	CKBOOL WriteElements(CKSTRING string, int column, int number, CKBOOL iAppend = FALSE);

	int GetRowCount();
	CKDataRow* GetRow(int n);
	void AddRow();
	CKDataRow* InsertRow(int n = -1);
	CKBOOL TestRow(int row, int c, CK_COMPOPERATOR op, CKDWORD key, int size = 0);
	int FindRowIndex(int c, CK_COMPOPERATOR op, CKDWORD key, int size = 0, int startingindex = 0);
	CKDataRow* FindRow(int c, CK_COMPOPERATOR op, CKDWORD key, int size = 0, int startindex = 0);
	void RemoveRow(int n);
	void MoveRow(int rsrc, int rdst);
	void SwapRows(int i1, int i2);
	void Clear(CKBOOL Params = TRUE);

	CKBOOL GetHighest(int c, int& row);
	CKBOOL GetLowest(int c, int& row);
	CKBOOL GetNearest(int c, void* value, int& row);
	void ColumnTransform(int c, CK_BINARYOPERATOR op, CKDWORD value);
	void ColumnsOperate(int c1, CK_BINARYOPERATOR op, int c2, int cr);

	void Sort(int c, CKBOOL ascending);
	void Unique(int c);
	void RandomShuffle();
	void Reverse();

	CKDWORD Sum(int c);
	CKDWORD Product(int c);
	int GetCount(int c, CK_COMPOPERATOR op, CKDWORD key, int size = 0);
	void CreateGroup(int mc, CK_COMPOPERATOR op, CKDWORD key, int size, CKGroup* group, int ec = 0);

protected:
	CKDataArray() {};
	~CKDataArray() {};
};
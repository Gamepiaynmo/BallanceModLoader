#include "CKDataArray.h"

NAKED void CKDataArray::InsertColumn(int cdest, CK_ARRAYTYPE type, CKSTRING name, CKGUID paramguid) {
	JUMP(0x2402696F);
}

NAKED void CKDataArray::MoveColumn(int csrc, int cdest) {
	JUMP(0x24026B45);
}

NAKED void CKDataArray::RemoveColumn(int c) {
	JUMP(0x24026C3D);
}

NAKED void CKDataArray::SetColumnName(int c, CKSTRING name) {
	JUMP(0x24026D82);
}

NAKED char* CKDataArray::GetColumnName(int c) {
	JUMP(0x240272BC);
}

NAKED void CKDataArray::SetColumnType(int c, CK_ARRAYTYPE type, CKGUID paramguid) {
	JUMP(0x24026DBD);
}

NAKED CK_ARRAYTYPE CKDataArray::GetColumnType(int c) {
	JUMP(0x240272E0);
}

NAKED CKGUID CKDataArray::GetColumnParameterGuid(int c) {
	JUMP(0x24027305);
}

NAKED int CKDataArray::GetKeyColumn() {
	JUMP(0x2402733F);
}

NAKED void CKDataArray::SetKeyColumn(int c) {
	JUMP(0x24027343);
}

NAKED int CKDataArray::GetColumnCount() {
	JUMP(0x2402735A);
}

NAKED CKDWORD* CKDataArray::GetElement(int i, int c) {
	JUMP(0x24027364);
}

NAKED CKBOOL CKDataArray::GetElementValue(int i, int c, void* value) {
	JUMP(0x240273A9);
}

NAKED CKObject* CKDataArray::GetElementObject(int i, int c) {
	JUMP(0x240273EE);
}

NAKED CKBOOL CKDataArray::SetElementValue(int i, int c, const void* value, int size) {
	JUMP(0x24027410);
}

NAKED CKBOOL CKDataArray::SetElementValueFromParameter(int i, int c, CKParameter* pout) {
	JUMP(0x240274B6);
}

NAKED CKBOOL CKDataArray::SetElementObject(int i, int c, CKObject* object) {
	JUMP(0x24027585);
}

NAKED CKBOOL CKDataArray::PasteShortcut(int i, int c, CKParameter* pout) {
	JUMP(0x240275AE);
}

NAKED CKParameterOut* CKDataArray::RemoveShortcut(int i, int c) {
	JUMP(0x24027672);
}

NAKED CKBOOL CKDataArray::SetElementStringValue(int i, int c, const char* svalue) {
	JUMP(0x240278AB);
}

NAKED int CKDataArray::GetStringValue(CKDWORD key, int c, char* svalue) {
	JUMP(0x2402770F);
}

NAKED int CKDataArray::GetElementStringValue(int i, int c, char* svalue) {
	JUMP(0x240276C7);
}

NAKED CKBOOL CKDataArray::LoadElements(CKSTRING string, CKBOOL append, int column) {
	JUMP(0x24027A21);
}

NAKED CKBOOL CKDataArray::WriteElements(CKSTRING string, int column, int number, CKBOOL iAppend) {
	JUMP(0x24027C14);
}

NAKED int CKDataArray::GetRowCount() {
	JUMP(0x24028009);
}

NAKED CKDataRow* CKDataArray::GetRow(int n) {
	JUMP(0x24027F18);
}

NAKED void CKDataArray::AddRow() {
	JUMP(0x24027D6A);
}

NAKED CKDataRow* CKDataArray::InsertRow(int n) {
	JUMP(0x24027E1F);
}

NAKED CKBOOL CKDataArray::TestRow(int row, int c, CK_COMPOPERATOR op, CKDWORD key, int size) {
	JUMP(0x2402822E);
}

NAKED int CKDataArray::FindRowIndex(int c, CK_COMPOPERATOR op, CKDWORD key, int size, int startingindex) {
	JUMP(0x24028128);
}

NAKED CKDataRow* CKDataArray::FindRow(int c, CK_COMPOPERATOR op, CKDWORD key, int size, int startindex) {
	JUMP(0x240281AF);
}

NAKED void CKDataArray::RemoveRow(int n) {
	JUMP(0x24027F3A);
}

NAKED void CKDataArray::MoveRow(int rsrc, int rdst) {
	JUMP(0x2402829B);
}

NAKED void CKDataArray::SwapRows(int i1, int i2) {
	JUMP(0x24028309);
}

NAKED void CKDataArray::Clear(CKBOOL Params) {
	JUMP(0x24028013);
}

NAKED CKBOOL CKDataArray::GetHighest(int c, int& row) {
	JUMP(0x2402834D);
}

NAKED CKBOOL CKDataArray::GetLowest(int c, int& row) {
	JUMP(0x24028411);
}

NAKED CKBOOL CKDataArray::GetNearest(int c, void* value, int& row) {
	JUMP(0x240284D5);
}

NAKED void CKDataArray::ColumnTransform(int c, CK_BINARYOPERATOR op, CKDWORD value) {
	JUMP(0x24028691);
}

NAKED void CKDataArray::ColumnsOperate(int c1, CK_BINARYOPERATOR op, int c2, int cr) {
	JUMP(0x24028881);
}

NAKED void CKDataArray::Sort(int c, CKBOOL ascending) {
	JUMP(0x24028C0D);
}

NAKED void CKDataArray::Unique(int c) {
	JUMP(0x24028C69);
}

NAKED void CKDataArray::RandomShuffle() {
	JUMP(0x24028EA9);
}

NAKED void CKDataArray::Reverse() {
	JUMP(0x24028EEA);
}

NAKED CKDWORD CKDataArray::Sum(int c) {
	JUMP(0x24028D80);
}

NAKED CKDWORD CKDataArray::Product(int c) {
	JUMP(0x24028E0E);
}

NAKED int CKDataArray::GetCount(int c, CK_COMPOPERATOR op, CKDWORD key, int size) {
	JUMP(0x24028F2E);
}

NAKED void CKDataArray::CreateGroup(int mc, CK_COMPOPERATOR op, CKDWORD key, int size, CKGroup* group, int ec) {
	JUMP(0x24028F9E);
}

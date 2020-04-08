#include "CKObjectArray.h"

NAKED int CKObjectArray::GetCount() {
	JUMP(0x24035F34);
}

NAKED int CKObjectArray::GetCurrentPos() {
	JUMP(0x2402158E);
}

NAKED CKObject CKObjectArray::* GetData(CKContext* context) {
	JUMP(0x2402A58F);
}

NAKED CK_ID CKObjectArray::GetDataId() {
	JUMP(0x2402A5E1);
}

NAKED CK_ID CKObjectArray::SetDataId(CK_ID id) {
	JUMP(0x2402A5A8);
}

NAKED CK_ID CKObjectArray::SetData(CKObject* obj) {
	JUMP(0x2402A5BF);
}

NAKED void CKObjectArray::Reset() {
	JUMP(0x2402A5EE);
}

NAKED CKBOOL CKObjectArray::PtrSeek(CKObject*) {
	JUMP(0x2402A7C1);
}

NAKED CKBOOL CKObjectArray::IDSeek(CK_ID id) {
	JUMP(0x2402A7D9);
}

NAKED CKBOOL CKObjectArray::PositionSeek(int Pos) {
	JUMP(0x2402A804);
}

NAKED CK_ID CKObjectArray::Seek(int Pos) {
	JUMP(0x2402A879);
}

NAKED void CKObjectArray::Next() {
	JUMP(0x2402A997);
}

NAKED void CKObjectArray::Previous() {
	JUMP(0x2402A980);
}

NAKED int CKObjectArray::GetPosition(CKObject* o) {
	JUMP(0x2402A928);
}

NAKED int CKObjectArray::GetPosition(CK_ID id) {
	JUMP(0x2402A954);
}

NAKED CK_ID CKObjectArray::PtrFind(CKObject*) {
	JUMP(0x2402A896);
}

NAKED CK_ID CKObjectArray::IDFind(CK_ID id) {
	JUMP(0x2402A8C7);
}

NAKED CK_ID CKObjectArray::PositionFind(int pos) {
	JUMP(0x2402A8F8);
}

NAKED void CKObjectArray::InsertFront(CKObject* obj) {
	JUMP(0x2402A6E7);
}

NAKED void CKObjectArray::InsertRear(CKObject* obj) {
	JUMP(0x2402A6FA);
}

NAKED void CKObjectArray::InsertAt(CKObject* obj) {
	JUMP(0x2402A75A);
}

NAKED CKBOOL CKObjectArray::AddIfNotHere(CKObject* obj) {
	JUMP(0x2402A76D);
}

NAKED CKBOOL CKObjectArray::AddIfNotHereSorted(CKObject* obj, OBJECTARRAYCMPFCT CmpFct, CKContext* context) {
	JUMP(0x2402A793);
}

NAKED void CKObjectArray::InsertFront(CK_ID id) {
	JUMP(0x2402A5F8);
}

NAKED void CKObjectArray::InsertRear(CK_ID id) {
	JUMP(0x2402A70D);
}

NAKED void CKObjectArray::InsertAt(CK_ID id) {
	JUMP(0x2402A64A);
}

NAKED CKBOOL CKObjectArray::AddIfNotHere(CK_ID id) {
	JUMP(0x2402A693);
}

NAKED CKBOOL CKObjectArray::AddIfNotHereSorted(CK_ID id, OBJECTARRAYCMPFCT CmpFct, CKContext* context) {
	JUMP(0x2402A6B9);
}

NAKED CKERROR CKObjectArray::Append(CKObjectArray* array) {
	JUMP(0x2402AB4A);
}

NAKED CK_ID CKObjectArray::RemoveFront() {
	JUMP(0x2402A9AF);
}

NAKED CK_ID CKObjectArray::RemoveRear() {
	JUMP(0x2402A9FD);
}

NAKED CK_ID CKObjectArray::RemoveAt() {
	JUMP(0x2402AA48);
}

NAKED CKBOOL CKObjectArray::Remove(CKObject*) {
	JUMP(0x2402AA89);
}

NAKED CKBOOL CKObjectArray::Remove(CK_ID id) {
	JUMP(0x2402AAA1);
}

NAKED void CKObjectArray::Clear() {
	JUMP(0x2402AADF);
}

NAKED CKBOOL CKObjectArray::EndOfList() {
	JUMP(0x2402A57E);
}

NAKED CKBOOL CKObjectArray::ListEmpty() {
	JUMP(0x2402A586);
}

NAKED void CKObjectArray::SwapCurrentWithNext() {
	JUMP(0x2402AB95);
}

NAKED void CKObjectArray::SwapCurrentWithPrevious() {
	JUMP(0x2402ABB6);
}

NAKED CKBOOL CKObjectArray::Check(CKContext* context) {
	JUMP(0x2402ABD5);
}

NAKED void CKObjectArray::Sort(OBJECTARRAYCMPFCT CmpFct, CKContext* context) {
	JUMP(0x2402AC4A);
}

NAKED void CKObjectArray::InsertSorted(CKObject* o, OBJECTARRAYCMPFCT CmpFct, CKContext* context) {
	JUMP(0x2402ACD4);
}

NAKED void CKObjectArray::InsertSorted(CK_ID id, OBJECTARRAYCMPFCT CmpFct, CKContext* context) {
	JUMP(0x2402ACF3);
}

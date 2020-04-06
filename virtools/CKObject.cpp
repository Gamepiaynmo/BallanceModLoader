#include "CKObject.h"

NAKED CKContext* CKObject::GetCKContext() {
	JUMP(0x2403AF9D);
}

NAKED CK_CLASSID CKObject::GetClassID() {
	JUMPV(0x14);
}

NAKED CK_ID CKObject::GetID() {
	JUMP(0x2403A50C);
}

NAKED CKSTRING CKObject::GetName() {
	JUMP(0x2403A510);
}
NAKED void CKObject::SetName(CKSTRING Name, CKBOOL shared) {
	JUMP(0x24020F30);
}

NAKED int CKObject::CanBeHide() {
	JUMPV(0x8)
}

NAKED CKBOOL CKObject::IsHiddenByParent() {
	JUMPV(0x4);
}

NAKED CKBOOL CKObject::IsHierarchicallyHide() {
	JUMP(0x2403A502);
}

NAKED CKBOOL CKObject::IsVisible() {
	JUMPV(0xc);
}

NAKED void CKObject::Show(CK_OBJECT_SHOWOPTION show) {
	JUMPV(0x0);
}

NAKED void* CKObject::GetAppData() {
	JUMP(0x24020F84);
}

NAKED void CKObject::SetAppData(void* Data) {
	JUMP(0x24020F6C);
}

NAKED CKDWORD CKObject::GetObjectFlags() {
	JUMP(0x2403AB37);
}

NAKED CKBOOL CKObject::IsDynamic() {
	JUMP(0x2403A514);
}

NAKED CKBOOL CKObject::IsToBeDeleted() {
	JUMP(0x2403A526);
}

NAKED void CKObject::ModifyObjectFlags(CKDWORD add, CKDWORD remove) {
	JUMP(0x2403A52D);
}
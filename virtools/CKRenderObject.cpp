#include "CKRenderObject.h"

NAKED CKBOOL CKRenderObject::IsInRenderContext(CKRenderContext* context) {
	JUMPV(0x54);
}

NAKED CKBOOL CKRenderObject::IsRootObject() {
	JUMPV(0x58);
}

NAKED CKBOOL CKRenderObject::IsToBeRendered() {
	JUMPV(0x5c);
}

NAKED void CKRenderObject::SetZOrder(int Z) {
	JUMPV(0x60);
}

NAKED int CKRenderObject::GetZOrder() {
	JUMPV(0x64);
}

NAKED CKBOOL CKRenderObject::IsToBeRenderedLast() {
	JUMPV(0x68);
}

NAKED CKBOOL CKRenderObject::AddPreRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument, CKBOOL Temp, CKBOOL ModifyRenderPipeline) {
	JUMPV(0x6c);
}

NAKED CKBOOL CKRenderObject::RemovePreRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument) {
	JUMPV(0x70);
}

NAKED CKBOOL CKRenderObject::SetRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument) {
	JUMPV(0x74);
}

NAKED CKBOOL CKRenderObject::RemoveRenderCallBack() {
	JUMPV(0x78);
}

NAKED CKBOOL CKRenderObject::AddPostRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument, CKBOOL Temp, CKBOOL ModifyRenderPipeline) {
	JUMPV(0x7c);
}

NAKED CKBOOL CKRenderObject::RemovePostRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument) {
	JUMPV(0x80);
}

NAKED void CKRenderObject::RemoveAllCallbacks() {
	JUMPV(0x84);
}

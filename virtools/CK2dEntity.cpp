#include "CK2dEntity.h"

NAKED CKERROR CK2dEntity::GetPosition(Vx2DVector& vect, CKBOOL hom, CK2dEntity* ref) {
	JUMPV(0x88);
}

NAKED void CK2dEntity::SetPosition(const Vx2DVector& vect, CKBOOL hom, CKBOOL KeepChildren, CK2dEntity* ref) {
	JUMPV(0x8c);
}

NAKED CKERROR CK2dEntity::GetSize(Vx2DVector& vect, CKBOOL hom) {
	JUMPV(0x90);
}

NAKED void CK2dEntity::SetSize(const Vx2DVector& vect, CKBOOL hom, CKBOOL KeepChildren) {
	JUMPV(0x94);
}

NAKED void CK2dEntity::SetRect(const VxRect& rect, CKBOOL KeepChildren) {
	JUMPV(0x98);
}

NAKED void CK2dEntity::GetRect(VxRect& rect) {
	JUMPV(0x9c);
}

NAKED CKERROR CK2dEntity::SetHomogeneousRect(const VxRect& rect, CKBOOL KeepChildren) {
	JUMPV(0xa0);
}

NAKED CKERROR CK2dEntity::GetHomogeneousRect(VxRect& rect) {
	JUMPV(0xa4);
}

NAKED void CK2dEntity::SetSourceRect(const VxRect& rect) {
	JUMPV(0xa8);
}

NAKED void CK2dEntity::GetSourceRect(VxRect& rect) {
	JUMPV(0xac);
}

NAKED void CK2dEntity::UseSourceRect(CKBOOL Use) {
	JUMPV(0xb0);
}

NAKED CKBOOL CK2dEntity::IsUsingSourceRect() {
	JUMPV(0xb4);
}

NAKED void CK2dEntity::SetPickable(CKBOOL Pick) {
	JUMPV(0xb8);
}

NAKED CKBOOL CK2dEntity::IsPickable() {
	JUMPV(0xbc);
}

NAKED void CK2dEntity::SetBackground(CKBOOL back) {
	JUMPV(0xc0);
}

NAKED CKBOOL CK2dEntity::IsBackground() {
	JUMPV(0xc4);
}

NAKED void CK2dEntity::SetClipToParent(CKBOOL clip) {
	JUMPV(0xc8);
}

NAKED CKBOOL CK2dEntity::IsClipToParent() {
	JUMPV(0xcc);
}

NAKED void CK2dEntity::SetFlags(CKDWORD Flags) {
	JUMPV(0xd0);
}

NAKED void CK2dEntity::ModifyFlags(CKDWORD add, CKDWORD remove) {
	JUMPV(0xd4);
}

NAKED CKDWORD CK2dEntity::GetFlags() {
	JUMPV(0xd8);
}

NAKED void CK2dEntity::EnableRatioOffset(CKBOOL Ratio) {
	JUMPV(0xdc);
}

NAKED CKBOOL CK2dEntity::IsRatioOffset() {
	JUMPV(0xe0);
}

NAKED CKBOOL CK2dEntity::SetParent(CK2dEntity* parent) {
	JUMPV(0xe4);
}

NAKED CK2dEntity* CK2dEntity::GetParent() const {
	JUMPV(0xe8);
}

NAKED int CK2dEntity::GetChildrenCount() const {
	JUMPV(0xec);
}

NAKED CK2dEntity* CK2dEntity::GetChild(int i) const {
	JUMPV(0xf0);
}

NAKED CK2dEntity* CK2dEntity::HierarchyParser(CK2dEntity* current) const {
	JUMPV(0xf4);
}

NAKED void CK2dEntity::SetMaterial(CKMaterial* mat) {
	JUMPV(0xf8);
}

NAKED CKMaterial* CK2dEntity::GetMaterial() {
	JUMPV(0xfc);
}

NAKED void CK2dEntity::SetHomogeneousCoordinates(CKBOOL Coord) {
	JUMPV(0x100);
}

NAKED CKBOOL CK2dEntity::IsHomogeneousCoordinates() {
	JUMPV(0x104);
}

NAKED void CK2dEntity::EnableClipToCamera(CKBOOL Clip) {
	JUMPV(0x108);
}

NAKED CKBOOL CK2dEntity::IsClippedToCamera() {
	JUMPV(0x10c);
}

NAKED CKERROR CK2dEntity::Render(CKRenderContext* context) {
	JUMPV(0x110);
}

NAKED CKERROR CK2dEntity::Draw(CKRenderContext* context) {
	JUMPV(0x114);
}

NAKED void CK2dEntity::GetExtents(VxRect& srcrect, VxRect& rect) {
	JUMPV(0x118);
}

NAKED void CK2dEntity::SetExtents(const VxRect& srcrect, const VxRect& rect) {
	JUMPV(0x11c);
}

NAKED void CK2dEntity::RestoreInitialSize() {
	JUMPV(0x120);
}

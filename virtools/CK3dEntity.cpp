#include "CK3dEntity.h"

NAKED int CK3dEntity::GetChildrenCount() const {
	JUMPV(0x88);
}

NAKED CK3dEntity* CK3dEntity::GetChild(int pos) const {
	JUMPV(0x8c);
}

NAKED CKBOOL CK3dEntity::SetParent(CK3dEntity* Parent, CKBOOL KeepWorldPos) {
	JUMPV(0x90);
}

NAKED CK3dEntity* CK3dEntity::GetParent() const {
	JUMPV(0x94);
}

NAKED CKBOOL CK3dEntity::AddChild(CK3dEntity* Child, CKBOOL KeepWorldPos) {
	JUMPV(0x98);
}

NAKED CKBOOL CK3dEntity::AddChildren(const XObjectPointerArray& Children, CKBOOL KeepWorldPos) {
	JUMPV(0x9c);
}

NAKED CKBOOL CK3dEntity::RemoveChild(CK3dEntity* Mov) {
	JUMPV(0xa0);
}

NAKED CKBOOL CK3dEntity::CheckIfSameKindOfHierarchy(CK3dEntity* Mov, CKBOOL SameOrder) const {
	JUMPV(0xa4);
}

NAKED CK3dEntity* CK3dEntity::HierarchyParser(CK3dEntity* current) const {
	JUMPV(0xa8);
}

NAKED CKDWORD CK3dEntity::GetFlags() const {
	JUMPV(0xac);
}

NAKED void CK3dEntity::SetFlags(CKDWORD Flags) {
	JUMPV(0xb0);
}

NAKED void CK3dEntity::SetPickable(CKBOOL Pick) {
	JUMPV(0xb4);
}

NAKED CKBOOL CK3dEntity::IsPickable() const {
	JUMPV(0xb8);
}

NAKED CKBOOL CK3dEntity::IsInViewFrustrum(CKRenderContext* Dev, CKDWORD Flags) {
	JUMPV(0xc4);
}

NAKED CKBOOL CK3dEntity::IsInViewFrustrumHierarchic(CKRenderContext* Dev) {
	JUMPV(0xc8);
}

NAKED void CK3dEntity::IgnoreAnimations(CKBOOL ignore) {
	JUMPV(0xcc);
}

NAKED CKBOOL CK3dEntity::AreAnimationIgnored() const {
	JUMPV(0xd0);
}

NAKED CKBOOL CK3dEntity::IsAllInsideFrustrum() const {
	JUMPV(0xd4);
}

NAKED CKBOOL CK3dEntity::IsAllOutsideFrustrum() const {
	JUMPV(0xd8);
}

NAKED void CK3dEntity::SetRenderAsTransparent(CKBOOL Trans) {
	JUMPV(0xdc);
}

NAKED CKDWORD CK3dEntity::GetMoveableFlags() const {
	JUMPV(0xe0);
}

NAKED void CK3dEntity::SetMoveableFlags(CKDWORD flags) {
	JUMPV(0xe4);
}

NAKED CKDWORD CK3dEntity::ModifyMoveableFlags(CKDWORD Add, CKDWORD Remove) {
	JUMPV(0xe8);
}

NAKED CKMesh* CK3dEntity::GetCurrentMesh() const {
	JUMPV(0xec);
}

NAKED CKMesh* CK3dEntity::SetCurrentMesh(CKMesh* m, CKBOOL add_if_not_here) {
	JUMPV(0xf0);
}

NAKED int CK3dEntity::GetMeshCount() const {
	JUMPV(0xf4);
}

NAKED CKMesh* CK3dEntity::GetMesh(int pos) const {
	JUMPV(0xf8);
}

NAKED CKERROR CK3dEntity::AddMesh(CKMesh* mesh) {
	JUMPV(0xfc);
}

NAKED CKERROR CK3dEntity::RemoveMesh(CKMesh* mesh) {
	JUMPV(0x100);
}

NAKED void CK3dEntity::LookAt(const VxVector& Pos, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x104);
}

NAKED void CK3dEntity::Rotate(float X, float Y, float Z, float Angle, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x108);
}

NAKED void CK3dEntity::Rotate(const VxVector& Axis, float Angle, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x10c);
}

NAKED void CK3dEntity::Translate(float X, float Y, float Z, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x110);
}

NAKED void CK3dEntity::Translate(const VxVector& Vect, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x114);
}

NAKED void CK3dEntity::AddScale(float X, float Y, float Z, CKBOOL KeepChildren, CKBOOL Local) {
	JUMPV(0x118);
}

NAKED void CK3dEntity::AddScale(const VxVector& Scale, CKBOOL KeepChildren, CKBOOL Local) {
	JUMPV(0x11c);
}

NAKED void CK3dEntity::SetPosition(float X, float Y, float Z, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x120);
}

NAKED void CK3dEntity::SetPosition(const VxVector& Pos, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x124);
}

NAKED void CK3dEntity::GetPosition(VxVector* Pos, CK3dEntity* Ref) const {
	JUMPV(0x128);
}

NAKED void CK3dEntity::SetOrientation(const VxVector& Dir, const VxVector& Up, const VxVector* Right, CK3dEntity* Ref, CKBOOL KeepChildren) {
	JUMPV(0x12c);
}

NAKED void CK3dEntity::GetOrientation(VxVector* Dir, VxVector* Up, VxVector* Right, CK3dEntity* Ref) {
	JUMPV(0x130);
}

NAKED void CK3dEntity::SetQuaternion(const VxQuaternion& Quat, CK3dEntity* Ref, CKBOOL KeepChildren, BOOL KeepScale) {
	JUMPV(0x134);
}

NAKED void CK3dEntity::GetQuaternion(VxQuaternion* Quat, CK3dEntity* Ref) {
	JUMPV(0x138);
}

NAKED void CK3dEntity::SetScale(float X, float Y, float Z, CKBOOL KeepChildren, CKBOOL Local) {
	JUMPV(0x13c);
}

NAKED void CK3dEntity::SetScale(const VxVector& Scale, CKBOOL KeepChildren, CKBOOL Local) {
	JUMPV(0x140);
}

NAKED void CK3dEntity::GetScale(VxVector* Scale, CKBOOL Local) {
	JUMPV(0x144);
}

NAKED CKBOOL CK3dEntity::ConstructWorldMatrix(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat) {
	JUMPV(0x148);
}

NAKED CKBOOL CK3dEntity::ConstructWorldMatrixEx(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat, const VxQuaternion& Shear, float Sign) {
	JUMPV(0x14c);
}

NAKED CKBOOL CK3dEntity::ConstructLocalMatrix(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat) {
	JUMPV(0x150);
}

NAKED CKBOOL CK3dEntity::ConstructLocalMatrixEx(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat, const VxQuaternion& Shear, float Sign) {
	JUMPV(0x154);
}

NAKED CKBOOL CK3dEntity::Render(CKRenderContext* Dev, CKDWORD Flags) {
	JUMPV(0x158);
}

NAKED int CK3dEntity::RayIntersection(const VxVector& Pos1, const VxVector& Pos2, VxIntersectionDesc* Desc, CK3dEntity* Ref, CK_RAYINTERSECTION iOptions) {
	JUMPV(0x15c);
}

NAKED void CK3dEntity::GetRenderExtents(VxRect& rect) const {
	JUMPV(0x160);
}

NAKED const VxMatrix& CK3dEntity::GetLastFrameMatrix() const {
	JUMPV(0x164);
}

NAKED void CK3dEntity::SetLocalMatrix(const VxMatrix& Mat, CKBOOL KeepChildren) {
	JUMPV(0x168);
}

NAKED const VxMatrix& CK3dEntity::GetLocalMatrix() const {
	JUMPV(0x16c);
}

NAKED void CK3dEntity::SetWorldMatrix(const VxMatrix& Mat, CKBOOL KeepChildren) {
	JUMPV(0x170);
}

NAKED const VxMatrix& CK3dEntity::GetWorldMatrix() const {
	JUMPV(0x174);
}

NAKED const VxMatrix& CK3dEntity::GetInverseWorldMatrix() const {
	JUMPV(0x178);
}

NAKED void CK3dEntity::Transform(VxVector* Dest, const VxVector& Src, CK3dEntity* Ref) const {
	JUMPV(0x17c);
}

NAKED void CK3dEntity::InverseTransform(VxVector* Dest, const VxVector& Src, CK3dEntity* Ref) const {
	JUMPV(0x180);
}

NAKED void CK3dEntity::TransformVector(VxVector* Dest, const VxVector& Src, CK3dEntity* Ref) const {
	JUMPV(0x184);
}

NAKED void CK3dEntity::InverseTransformVector(VxVector* Dest, const VxVector& Src, CK3dEntity* Ref) const {
	JUMPV(0x188);
}

NAKED void CK3dEntity::TransformMany(VxVector* Dest, const VxVector& Src, int count, CK3dEntity* Ref) const {
	JUMPV(0x18c);
}

NAKED void CK3dEntity::InverseTransformMany(VxVector* Dest, const VxVector& Src, int count, CK3dEntity* Ref) const {
	JUMPV(0x190);
}

NAKED void CK3dEntity::ChangeReferential(CK3dEntity* Ref) {
	JUMPV(0x194);
}

NAKED CKPlace* CK3dEntity::GetReferencePlace() const {
	JUMPV(0x198);
}

NAKED void CK3dEntity::AddObjectAnimation(CKObjectAnimation* anim) {
	JUMPV(0x19c);
}

NAKED void CK3dEntity::RemoveObjectAnimation(CKObjectAnimation* anim) {
	JUMPV(0x1a0);
}

NAKED CKObjectAnimation* CK3dEntity::GetObjectAnimation(int index) const {
	JUMPV(0x1a4);
}

NAKED int CK3dEntity::GetObjectAnimationCount() const {
	JUMPV(0x1a8);
}

NAKED CKSkin* CK3dEntity::CreateSkin() {
	JUMPV(0x1ac);
}

NAKED CKBOOL CK3dEntity::DestroySkin() {
	JUMPV(0x1b0);
}

NAKED CKBOOL CK3dEntity::UpdateSkin() {
	JUMPV(0x1b4);
}

NAKED CKSkin* CK3dEntity::GetSkin() const {
	JUMPV(0x1b8);
}

NAKED void CK3dEntity::UpdateBox(CKBOOL World) {
	JUMPV(0x1bc);
}

NAKED const VxBbox& CK3dEntity::GetBoundingBox(CKBOOL Local) {
	JUMPV(0x1c0);
}

NAKED CKBOOL CK3dEntity::SetBoundingBox(const VxBbox& BBox, CKBOOL Local) {
	JUMPV(0x1c4);
}

NAKED const VxBbox& CK3dEntity::GetHierarchicalBox(CKBOOL Local) {
	JUMPV(0x1c8);
}

NAKED CKBOOL CK3dEntity::GetBaryCenter(VxVector* Pos) {
	JUMPV(0x1cc);
}

NAKED float CK3dEntity::GetRadius() {
	JUMPV(0x1d0);
}

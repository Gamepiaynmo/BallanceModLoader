#include "CKSprite3D.h"

NAKED void CKSprite3D::SetMaterial(CKMaterial* Mat) {
	JUMPV(0x1d4);
}

NAKED CKMaterial* CKSprite3D::GetMaterial() {
	JUMPV(0x1d8);
}

NAKED void CKSprite3D::SetSize(Vx2DVector& vect) {
	JUMPV(0x1dc);
}

NAKED void CKSprite3D::GetSize(Vx2DVector& vect) {
	JUMPV(0x1e0);
}

NAKED void CKSprite3D::SetOffset(Vx2DVector& vect) {
	JUMPV(0x1e4);
}

NAKED void CKSprite3D::GetOffset(Vx2DVector& vect) {
	JUMPV(0x1e8);
}

NAKED void CKSprite3D::SetUVMapping(VxRect& rect) {
	JUMPV(0x1ec);
}

NAKED void CKSprite3D::GetUVMapping(VxRect& rect) {
	JUMPV(0x1f0);
}

NAKED void CKSprite3D::SetMode(VXSPRITE3D_TYPE Mode) {
	JUMPV(0x1f4);
}

NAKED VXSPRITE3D_TYPE CKSprite3D::GetMode() {
	JUMPV(0x1f8);
}

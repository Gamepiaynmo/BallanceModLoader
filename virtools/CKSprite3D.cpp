#include "CKSprite3D.h"

void CKSprite3D::SetMaterial(CKMaterial* Mat) {
	JUMPV(0x1d4);
}

CKMaterial* CKSprite3D::GetMaterial() {
	JUMPV(0x1d8);
}

void CKSprite3D::SetSize(Vx2DVector& vect) {
	JUMPV(0x1dc);
}

void CKSprite3D::GetSize(Vx2DVector& vect) {
	JUMPV(0x1e0);
}

void CKSprite3D::SetOffset(Vx2DVector& vect) {
	JUMPV(0x1e4);
}

void CKSprite3D::GetOffset(Vx2DVector& vect) {
	JUMPV(0x1e8);
}

void CKSprite3D::SetUVMapping(VxRect& rect) {
	JUMPV(0x1ec);
}

void CKSprite3D::GetUVMapping(VxRect& rect) {
	JUMPV(0x1f0);
}

void CKSprite3D::SetMode(VXSPRITE3D_TYPE Mode) {
	JUMPV(0x1f4);
}

VXSPRITE3D_TYPE CKSprite3D::GetMode() {
	JUMPV(0x1f8);
}

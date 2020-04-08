#pragma once

#include "CKDef.h"
#include "CK3dEntity.h"

class BML_EXPORT CKSprite3D : public CK3dEntity {
public:
	void SetMaterial(CKMaterial* Mat);
	CKMaterial* GetMaterial();
	void SetSize(Vx2DVector& vect);
	void GetSize(Vx2DVector& vect);
	void SetOffset(Vx2DVector& vect);
	void GetOffset(Vx2DVector& vect);
	void SetUVMapping(VxRect& rect);
	void GetUVMapping(VxRect& rect);
	void SetMode(VXSPRITE3D_TYPE Mode);
	VXSPRITE3D_TYPE GetMode();

protected:
	CKSprite3D() {};
	~CKSprite3D() {};
};
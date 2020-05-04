#pragma once

#include "CKDef.h"
#include "CKRenderObject.h"

class BML_EXPORT CK2dEntity : public CKRenderObject {
public:
	CKERROR GetPosition(Vx2DVector& vect, CKBOOL hom = FALSE, CK2dEntity* ref = NULL);
	void SetPosition(const Vx2DVector& vect, CKBOOL hom = FALSE, CKBOOL KeepChildren = FALSE, CK2dEntity* ref = NULL);
	CKERROR GetSize(Vx2DVector& vect, CKBOOL hom = FALSE);
	void SetSize(const Vx2DVector& vect, CKBOOL hom = FALSE, CKBOOL KeepChildren = FALSE);
	void SetRect(const VxRect& rect, CKBOOL KeepChildren = FALSE);
	void GetRect(VxRect& rect);
	CKERROR SetHomogeneousRect(const VxRect& rect, CKBOOL KeepChildren = FALSE);
	CKERROR GetHomogeneousRect(VxRect& rect);
	void SetSourceRect(const VxRect& rect);
	void GetSourceRect(VxRect& rect);
	void UseSourceRect(CKBOOL Use = TRUE);
	CKBOOL IsUsingSourceRect();
	void SetPickable(CKBOOL Pick = TRUE);
	CKBOOL IsPickable();
	void SetBackground(CKBOOL back = TRUE);
	CKBOOL IsBackground();
	void SetClipToParent(CKBOOL clip = TRUE);
	CKBOOL IsClipToParent();
	void SetFlags(CKDWORD Flags);
	void ModifyFlags(CKDWORD add, CKDWORD remove = 0);
	CKDWORD GetFlags();
	void EnableRatioOffset(CKBOOL Ratio = TRUE);
	CKBOOL IsRatioOffset();
	CKBOOL SetParent(CK2dEntity* parent);
	CK2dEntity* GetParent() const;
	int GetChildrenCount() const;
	CK2dEntity* GetChild(int i) const;
	CK2dEntity* HierarchyParser(CK2dEntity* current) const;
	void SetMaterial(CKMaterial* mat);
	CKMaterial* GetMaterial();
	void SetHomogeneousCoordinates(CKBOOL Coord = TRUE);
	CKBOOL IsHomogeneousCoordinates();
	void EnableClipToCamera(CKBOOL Clip = TRUE);
	CKBOOL IsClippedToCamera();
	CKERROR Render(CKRenderContext* context);
	CKERROR Draw(CKRenderContext* context);
	void GetExtents(VxRect& srcrect, VxRect& rect);
	void SetExtents(const VxRect& srcrect, const VxRect& rect);
	void RestoreInitialSize();
};
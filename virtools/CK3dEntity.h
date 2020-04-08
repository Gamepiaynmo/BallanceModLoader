#pragma once

#include "CKDef.h"
#include "CKRenderObject.h"

class CKSkin;

#define CKRENDER_UPDATEEXTENTS 0x00000FF
#define CKRENDER_DONTSETMATRIX 0x0000100

struct VxIntersectionDesc {
	CK3dEntity* Object;
	CK2dEntity* Sprite;
	VxVector IntersectionPoint;
	VxVector IntersectionNormal;
	float TexU;
	float TexV;
	float Distance;
	int FaceIndex;
};

class BML_EXPORT CK3dEntity : public CKRenderObject {
public:
	int GetChildrenCount() const;
	CK3dEntity* GetChild(int pos) const;
	CKBOOL SetParent(CK3dEntity* Parent, CKBOOL KeepWorldPos = TRUE);
	CK3dEntity* GetParent() const;
	CKBOOL AddChild(CK3dEntity* Child, CKBOOL KeepWorldPos = TRUE);
	CKBOOL AddChildren(const XObjectPointerArray& Children, CKBOOL KeepWorldPos = TRUE);
	CKBOOL RemoveChild(CK3dEntity* Mov);
	CKBOOL CheckIfSameKindOfHierarchy(CK3dEntity* Mov, CKBOOL SameOrder = FALSE) const;
	CK3dEntity* HierarchyParser(CK3dEntity* current) const;
	CKDWORD GetFlags() const;
	void SetFlags(CKDWORD Flags);
	void SetPickable(CKBOOL Pick = TRUE);
	CKBOOL IsPickable() const;
	CKBOOL IsInViewFrustrum(CKRenderContext* Dev, CKDWORD Flags = 0);
	CKBOOL IsInViewFrustrumHierarchic(CKRenderContext* Dev);
	void IgnoreAnimations(CKBOOL ignore = TRUE);
	CKBOOL AreAnimationIgnored() const;
	CKBOOL IsAllInsideFrustrum() const;
	CKBOOL IsAllOutsideFrustrum() const;
	void SetRenderAsTransparent(CKBOOL Trans = TRUE);
	CKDWORD GetMoveableFlags() const;
	void SetMoveableFlags(CKDWORD flags);
	CKDWORD ModifyMoveableFlags(CKDWORD Add, CKDWORD Remove);
	CKMesh* GetCurrentMesh() const;
	CKMesh* SetCurrentMesh(CKMesh* m, CKBOOL add_if_not_here = TRUE);
	int GetMeshCount() const;
	CKMesh* GetMesh(int pos) const;
	CKERROR AddMesh(CKMesh* mesh);
	CKERROR RemoveMesh(CKMesh* mesh);
	void LookAt(const VxVector* Pos, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void Rotate(const VxVector* Axis, float Angle, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void Rotate(float X, float Y, float Z, float Angle, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void Translate(const VxVector* Vect, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void Translate(float X, float Y, float Z, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void AddScale(const VxVector* Scale, CKBOOL KeepChildren = FALSE, CKBOOL Local = TRUE);
	void AddScale(float X, float Y, float Z, CKBOOL KeepChildren = FALSE, CKBOOL Local = TRUE);
	void SetPosition(const VxVector* Pos, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void SetPosition(float X, float Y, float Z, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void GetPosition(VxVector* Pos, CK3dEntity* Ref = NULL) const;
	void SetOrientation(const VxVector* Dir, const VxVector* Up, const VxVector* Right = NULL, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE);
	void GetOrientation(VxVector* Dir, VxVector* Up, VxVector* Right = NULL, CK3dEntity* Ref = NULL);
	void SetQuaternion(const VxQuaternion* Quat, CK3dEntity* Ref = NULL, CKBOOL KeepChildren = FALSE, BOOL KeepScale = FALSE);
	void GetQuaternion(VxQuaternion* Quat, CK3dEntity* Ref = NULL);
	void SetScale(const VxVector* Scale, CKBOOL KeepChildren = FALSE, CKBOOL Local = TRUE);
	void SetScale(float X, float Y, float Z, CKBOOL KeepChildren = FALSE, CKBOOL Local = TRUE);
	void GetScale(VxVector* Scale, CKBOOL Local = TRUE);
	CKBOOL ConstructWorldMatrix(const VxVector* Pos, const VxVector* Scale, const VxQuaternion* Quat);
	CKBOOL ConstructWorldMatrixEx(const VxVector* Pos, const VxVector* Scale, const VxQuaternion* Quat, const VxQuaternion* Shear, float Sign);
	CKBOOL ConstructLocalMatrix(const VxVector* Pos, const VxVector* Scale, const VxQuaternion* Quat);
	CKBOOL ConstructLocalMatrixEx(const VxVector* Pos, const VxVector* Scale, const VxQuaternion* Quat, const VxQuaternion* Shear, float Sign);
	CKBOOL Render(CKRenderContext* Dev, CKDWORD Flags = CKRENDER_UPDATEEXTENTS);
	int RayIntersection(const VxVector* Pos1, const VxVector* Pos2, VxIntersectionDesc* Desc, CK3dEntity* Ref, CK_RAYINTERSECTION iOptions = CKRAYINTERSECTION_DEFAULT);
	void GetRenderExtents(VxRect& rect) const;
	const VxMatrix& GetLastFrameMatrix() const;
	void SetLocalMatrix(const VxMatrix& Mat, CKBOOL KeepChildren = FALSE);
	const VxMatrix& GetLocalMatrix() const;
	void SetWorldMatrix(const VxMatrix& Mat, CKBOOL KeepChildren = FALSE);
	const VxMatrix& GetWorldMatrix() const;
	const VxMatrix& GetInverseWorldMatrix() const;
	void Transform(VxVector* Dest, const VxVector* Src, CK3dEntity* Ref = NULL) const;
	void InverseTransform(VxVector* Dest, const VxVector* Src, CK3dEntity* Ref = NULL) const;
	void TransformVector(VxVector* Dest, const VxVector* Src, CK3dEntity* Ref = NULL) const;
	void InverseTransformVector(VxVector* Dest, const VxVector* Src, CK3dEntity* Ref = NULL) const;
	void TransformMany(VxVector* Dest, const VxVector* Src, int count, CK3dEntity* Ref = NULL) const;
	void InverseTransformMany(VxVector* Dest, const VxVector* Src, int count, CK3dEntity* Ref = NULL) const;
	void ChangeReferential(CK3dEntity* Ref = NULL);
	CKPlace* GetReferencePlace() const;
	void AddObjectAnimation(CKObjectAnimation* anim);
	void RemoveObjectAnimation(CKObjectAnimation* anim);
	CKObjectAnimation* GetObjectAnimation(int index) const;
	int GetObjectAnimationCount() const;
	CKSkin* CreateSkin();
	CKBOOL DestroySkin();
	CKBOOL UpdateSkin();
	CKSkin* GetSkin() const;
	void UpdateBox(CKBOOL World = TRUE);
	const VxBbox& GetBoundingBox(CKBOOL Local = FALSE);
	CKBOOL SetBoundingBox(const VxBbox* BBox, CKBOOL Local = FALSE);
	const VxBbox& GetHierarchicalBox(CKBOOL Local = FALSE);
	CKBOOL GetBaryCenter(VxVector* Pos);
	float GetRadius();

protected:
	CK3dEntity() {};
	~CK3dEntity() {};
};

class BML_EXPORT CK3dObject : public CK3dEntity {
protected:
	CK3dObject() {};
	~CK3dObject() {};
};
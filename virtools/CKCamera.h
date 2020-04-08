#pragma once

#include "CKDef.h"
#include "CK3dEntity.h"

#define CK_PERSPECTIVEPROJECTION 1
#define CK_ORTHOGRAPHICPROJECTION 2

class BML_EXPORT CKCamera : public CK3dEntity {
public:
	float GetFrontPlane();
	void SetFrontPlane(float front);
	float GetBackPlane();
	void SetBackPlane(float back);
	float GetFov();
	void SetFov(float fov);
	int GetProjectionType();
	void SetProjectionType(int proj);
	void SetOrthographicZoom(float zoom);
	float GetOrthographicZoom();
	void SetAspectRatio(int width, int height);
	void GetAspectRatio(int& width, int& height);
	void ComputeProjectionMatrix(VxMatrix& mat);
	void ResetRoll();
	void Roll(float angle);
	CK3dEntity* GetTarget();
	void SetTarget(CK3dEntity* target);

protected:
	CKCamera() {};
	~CKCamera() {};
};

class BML_EXPORT CKTargetCamera : public CKCamera {
protected:
	CKTargetCamera() {};
	~CKTargetCamera() {};
};
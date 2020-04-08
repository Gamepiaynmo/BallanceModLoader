#include "CKCamera.h"

NAKED float CKCamera::GetFrontPlane() {
	JUMPV(0x1d4);
}

NAKED void CKCamera::SetFrontPlane(float front) {
	JUMPV(0x1d8);
}

NAKED float CKCamera::GetBackPlane() {
	JUMPV(0x1dc);
}

NAKED void CKCamera::SetBackPlane(float back) {
	JUMPV(0x1e0);
}

NAKED float CKCamera::GetFov() {
	JUMPV(0x1e4);
}

NAKED void CKCamera::SetFov(float fov) {
	JUMPV(0x1e8);
}

NAKED int CKCamera::GetProjectionType() {
	JUMPV(0x1ec);
}

NAKED void CKCamera::SetProjectionType(int proj) {
	JUMPV(0x1f0);
}

NAKED void CKCamera::SetOrthographicZoom(float zoom) {
	JUMPV(0x1f4);
}

NAKED float CKCamera::GetOrthographicZoom() {
	JUMPV(0x1f8);
}

NAKED void CKCamera::SetAspectRatio(int width, int height) {
	JUMPV(0x1fc);
}

NAKED void CKCamera::GetAspectRatio(int& width, int& height) {
	JUMPV(0x200);
}

NAKED void CKCamera::ComputeProjectionMatrix(VxMatrix& mat) {
	JUMPV(0x204);
}

NAKED void CKCamera::ResetRoll() {
	JUMPV(0x208);
}

NAKED void CKCamera::Roll(float angle) {
	JUMPV(0x20c);
}

NAKED CK3dEntity* CKCamera::GetTarget() {
	JUMPV(0x210);
}

NAKED void CKCamera::SetTarget(CK3dEntity* target) {
	JUMPV(0x214);
}

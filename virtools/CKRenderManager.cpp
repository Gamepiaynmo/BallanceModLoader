#include "CKRenderManager.h"

NAKED int CKRenderManager::GetRenderDriverCount() {
	JUMPV(0x78);
}

NAKED VxDriverDesc* CKRenderManager::GetRenderDriverDescription(int Driver) {
	JUMPV(0x7c);
}

NAKED void CKRenderManager::GetDesiredTexturesVideoFormat(VxImageDescEx& VideoFormat) {
	JUMPV(0x80);
}

NAKED void CKRenderManager::SetDesiredTexturesVideoFormat(VxImageDescEx& VideoFormat) {
	JUMPV(0x84);
}

NAKED CKRenderContext* CKRenderManager::GetRenderContext(int pos) {
	JUMPV(0x88);
}

NAKED CKRenderContext* CKRenderManager::GetRenderContextFromPoint(CKPOINT& pt) {
	JUMPV(0x8c);
}

NAKED int CKRenderManager::GetRenderContextCount() {
	JUMPV(0x90);
}

NAKED void CKRenderManager::Process() {
	JUMPV(0x94);
}

NAKED void CKRenderManager::FlushTextures() {
	JUMPV(0x98);
}

NAKED CKRenderContext* CKRenderManager::CreateRenderContext(void* Window, int Driver, CKRECT* rect, CKBOOL Fullscreen, int Bpp, int Zbpp, int StencilBpp, int RefreshRate) {
	JUMPV(0x9c);
}

NAKED CKERROR CKRenderManager::DestroyRenderContext(CKRenderContext* context) {
	JUMPV(0xa0);
}

NAKED void CKRenderManager::RemoveRenderContext(CKRenderContext* context) {
	JUMPV(0xa4);
}

NAKED CKVertexBuffer* CKRenderManager::CreateVertexBuffer() {
	JUMPV(0xa8);
}

NAKED void CKRenderManager::DestroyVertexBuffer(CKVertexBuffer* VB) {
	JUMPV(0xac);
}

NAKED void CKRenderManager::SetRenderOptions(CKSTRING RenderOptionString, DWORD Value) {
	JUMPV(0xb0);
}

NAKED const VxEffectDescription& CKRenderManager::GetEffectDescription(int EffectIndex) {
	JUMPV(0xb4);
}

NAKED int CKRenderManager::GetEffectCount() {
	JUMPV(0xb8);
}

NAKED int CKRenderManager::AddEffect(const VxEffectDescription& NewEffect) {
	JUMPV(0xbc);
}

NAKED void CKRenderManager::DrawAABB(CKRenderContext* iRC, const VxBbox& iBox, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xc0);
}

NAKED void CKRenderManager::DrawNormal(CKRenderContext* iRC, const VxRay& iRay, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xc4);
}

NAKED void CKRenderManager::DrawPoint(CKRenderContext* iRC, const VxVector& iPoint, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xc8);
}

NAKED void CKRenderManager::DrawPlane(CKRenderContext* iRC, const VxPlane& iPlane, const VxVector& iPoint, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xcc);
}

NAKED void CKRenderManager::DrawFrustum(CKRenderContext* iRC, const VxFrustum& iFrustum, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xd0);
}

NAKED void CKRenderManager::DrawSphere(CKRenderContext* iRC, const VxSphere& iSphere, const CKDWORD iColor, const VxMatrix* iTransform, const int iSubdivisions) {
	JUMPV(0xd4);
}

NAKED void CKRenderManager::DrawParabolic(CKRenderContext* iRC, const VxVector& iStartPos, const VxVector& iSpeed, const VxVector& iAcceleration, float iDrawingTime, const int iSubdivisions, const CKDWORD iColor, const VxMatrix* iTransform) {
	JUMPV(0xd8);
}

NAKED void CKRenderManager::DrawPoint2D(CKRenderContext* iRC, const Vx2DVector& iPoint, const CKDWORD iColor) {
	JUMPV(0xdc);
}

NAKED void CKRenderManager::DrawRectangle(CKRenderContext* iRC, const VxRect& iRect, const CKDWORD iColor) {
	JUMPV(0xe0);
}

NAKED void CKRenderManager::DrawFillRectangle(CKRenderContext* iRC, const VxRect& iRect, const CKDWORD iColor) {
	JUMPV(0xe4);
}

NAKED void CKRenderManager::DrawText(CKRenderContext* iRC, const Vx2DVector& iPoint, const char* iText, const CKDWORD iColor) {
	JUMPV(0xe8);
}

NAKED void CKRenderManager::RegisterAABB(const VxBbox& iBox, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0xec);
}

NAKED void CKRenderManager::RegisterNormal(const VxRay& iRay, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0xf0);
}

NAKED void CKRenderManager::RegisterPoint(const VxVector& iPoint, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0xf4);
}

NAKED void CKRenderManager::RegisterPlane(const VxPlane& iPlane, const VxVector& iPoint, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0xf8);
}

NAKED void CKRenderManager::RegisterFrustum(const VxFrustum& iFrustum, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0xfc);
}

NAKED void CKRenderManager::RegisterSphere(const VxSphere& iSphere, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform, const int iSubdivisions) {
	JUMPV(0x100);
}

NAKED void CKRenderManager::RegisterParabolic(const VxVector& iStartPos, const VxVector& iSpeed, const VxVector& iAcceleration, float iDrawingTime, const int iSubdivisions, const CKDWORD iColor, float iRemainingTime, const VxMatrix* iTransform) {
	JUMPV(0x104);
}

NAKED void CKRenderManager::RegisterPoint2D(const Vx2DVector& iPoint, const CKDWORD iColor, float iRemainingTime) {
	JUMPV(0x108);
}

NAKED void CKRenderManager::RegisterRectangle(const VxRect& iRect, const CKDWORD iColor, float iRemainingTime) {
	JUMPV(0x10c);
}

NAKED void CKRenderManager::RegisterFillRectangle(const VxRect& iRect, const CKDWORD iColor, float iRemainingTime) {
	JUMPV(0x110);
}

NAKED void CKRenderManager::RegisterText(const char* iText, const CKDWORD iColor, float iRemainingTime) {
	JUMPV(0x114);
}

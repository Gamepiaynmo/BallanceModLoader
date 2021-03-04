#include "CKRenderContext.h"

NAKED void CKRenderContext::AddObject(CKRenderObject* obj) {
    JUMPV(0x48);
}

NAKED void CKRenderContext::AddObjectWithHierarchy(CKRenderObject* obj) {
    JUMPV(0x4c);
}

NAKED void CKRenderContext::RemoveObject(CKRenderObject* obj) {
    JUMPV(0x50);
}

NAKED CKBOOL CKRenderContext::IsObjectAttached(CKRenderObject* obj) {
    JUMPV(0x54);
}

NAKED const XObjectArray& CKRenderContext::Compute3dRootObjects() {
    JUMPV(0x58);
}

NAKED const XObjectArray& CKRenderContext::Compute2dRootObjects() {
    JUMPV(0x5c);
}

NAKED CK2dEntity* CKRenderContext::Get2dRoot(CKBOOL background) {
    JUMPV(0x60);
}

NAKED void CKRenderContext::DetachAll() {
    JUMPV(0x64);
}

NAKED void CKRenderContext::ForceCameraSettingsUpdate() {
    JUMPV(0x68);
}

NAKED void CKRenderContext::PrepareCameras(CK_RENDER_FLAGS Flags) {
    JUMPV(0x6c);
}

NAKED CKERROR CKRenderContext::Clear(CK_RENDER_FLAGS Flags, CKDWORD Stencil) {
    JUMPV(0x70);
}

NAKED CKERROR CKRenderContext::DrawScene(CK_RENDER_FLAGS Flags) {
    JUMPV(0x74);
}

NAKED CKERROR CKRenderContext::BackToFront(CK_RENDER_FLAGS Flags) {
    JUMPV(0x78);
}

NAKED CKERROR CKRenderContext::Render(CK_RENDER_FLAGS Flags) {
    JUMPV(0x7c);
}

NAKED void CKRenderContext::AddPreRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary) {
    JUMPV(0x80);
}

NAKED void CKRenderContext::RemovePreRenderCallBack(CK_RENDERCALLBACK Function, void* Argument) {
    JUMPV(0x84);
}

NAKED void CKRenderContext::AddPostRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary, CKBOOL BeforeTransparent) {
    JUMPV(0x88);
}

NAKED void CKRenderContext::RemovePostRenderCallBack(CK_RENDERCALLBACK Function, void* Argument) {
    JUMPV(0x8c);
}

NAKED void CKRenderContext::AddPostSpriteRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary) {
    JUMPV(0x90);
}

NAKED void CKRenderContext::RemovePostSpriteRenderCallBack(CK_RENDERCALLBACK Function, void* Argument) {
    JUMPV(0x94);
}

NAKED VxDrawPrimitiveData* CKRenderContext::GetDrawPrimitiveStructure(CKRST_DPFLAGS Flags, int VertexCount) {
    JUMPV(0x98);
}

NAKED CKWORD* CKRenderContext::GetDrawPrimitiveIndices(int IndicesCount) {
    JUMPV(0x9c);
}

NAKED void CKRenderContext::Transform(VxVector* Dest, VxVector* Src, CK3dEntity* Ref) {
    JUMPV(0xa0);
}

NAKED void CKRenderContext::TransformVertices(int VertexCount, VxTransformData* data, CK3dEntity* Ref) {
    JUMPV(0xa4);
}

NAKED CKERROR CKRenderContext::GoFullScreen(int Width, int Height, int Bpp, int Driver, int RefreshRate) {
    JUMPV(0xa8);
}

NAKED CKERROR CKRenderContext::StopFullScreen() {
    JUMPV(0xac);
}

NAKED CKBOOL CKRenderContext::IsFullScreen() {
    JUMPV(0xb0);
}

NAKED int CKRenderContext::GetDriverIndex() {
    JUMPV(0xb4);
}

NAKED CKBOOL CKRenderContext::ChangeDriver(int NewDriver) {
    JUMPV(0xb8);
}

NAKED WIN_HANDLE CKRenderContext::GetWindowHandle() {
    JUMPV(0xbc);
}

NAKED void CKRenderContext::ScreenToClient(Vx2DVector* ioPoint) {
    JUMPV(0xc0);
}

NAKED void CKRenderContext::ClientToScreen(Vx2DVector* ioPoint) {
    JUMPV(0xc4);
}

NAKED CKERROR CKRenderContext::SetWindowRect(VxRect& rect, CKDWORD Flags) {
    JUMPV(0xc8);
}

NAKED void CKRenderContext::GetWindowRect(VxRect& rect, CKBOOL ScreenRelative) {
    JUMPV(0xcc);
}

NAKED int CKRenderContext::GetHeight() {
    JUMPV(0xd0);
}

NAKED int CKRenderContext::GetWidth() {
    JUMPV(0xd4);
}

NAKED CKERROR CKRenderContext::Resize(int PosX, int PosY, int SizeX, int SizeY, CKDWORD Flags) {
    JUMPV(0xd8);
}

NAKED void CKRenderContext::SetViewRect(VxRect& rect) {
    JUMPV(0xdc);
}

NAKED void CKRenderContext::GetViewRect(VxRect& rect) {
    JUMPV(0xe0);
}

NAKED VX_PIXELFORMAT CKRenderContext::GetPixelFormat(int* Bpp, int* Zbpp, int* StencilBpp) {
    JUMPV(0xe4);
}

NAKED void CKRenderContext::SetState(VXRENDERSTATETYPE State, CKDWORD Value) {
    JUMPV(0xe8);
}

NAKED CKDWORD CKRenderContext::GetState(VXRENDERSTATETYPE State) {
    JUMPV(0xec);
}

NAKED CKBOOL CKRenderContext::SetTexture(CKTexture* tex, CKBOOL Clamped, int Stage) {
    JUMPV(0xf0);
}

NAKED CKBOOL CKRenderContext::SetTextureStageState(CKRST_TEXTURESTAGESTATETYPE State, CKDWORD Value, int Stage) {
    JUMPV(0xf4);
}

NAKED CKRasterizerContext* CKRenderContext::GetRasterizerContext() {
    JUMPV(0xf8);
}

NAKED void CKRenderContext::SetClearBackground(CKBOOL ClearBack) {
    JUMPV(0xfc);
}

NAKED CKBOOL CKRenderContext::GetClearBackground() {
    JUMPV(0x100);
}

NAKED void CKRenderContext::SetClearZBuffer(CKBOOL ClearZ) {
    JUMPV(0x104);
}

NAKED CKBOOL CKRenderContext::GetClearZBuffer() {
    JUMPV(0x108);
}

NAKED void CKRenderContext::GetGlobalRenderMode(VxShadeType* Shading, CKBOOL* Texture, CKBOOL* Wireframe) {
    JUMPV(0x10c);
}

NAKED void CKRenderContext::SetGlobalRenderMode(VxShadeType Shading, CKBOOL Texture, CKBOOL Wireframe) {
    JUMPV(0x110);
}

NAKED void CKRenderContext::SetCurrentRenderOptions(CKDWORD flags) {
    JUMPV(0x114);
}

NAKED CKDWORD CKRenderContext::GetCurrentRenderOptions() {
    JUMPV(0x118);
}

NAKED void CKRenderContext::ChangeCurrentRenderOptions(CKDWORD Add, CKDWORD Remove) {
    JUMPV(0x11c);
}

NAKED void CKRenderContext::SetCurrentExtents(VxRect& extents) {
    JUMPV(0x120);
}

NAKED void CKRenderContext::GetCurrentExtents(VxRect& extents) {
    JUMPV(0x124);
}

NAKED void CKRenderContext::SetAmbientLight(float R, float G, float B) {
    JUMPV(0x128);
}

NAKED void CKRenderContext::SetAmbientLight(CKDWORD Color) {
    JUMPV(0x12c);
}

NAKED CKDWORD CKRenderContext::GetAmbientLight() {
    JUMPV(0x130);
}

NAKED void CKRenderContext::SetFogMode(VXFOG_MODE Mode) {
    JUMPV(0x134);
}

NAKED void CKRenderContext::SetFogStart(float Start) {
    JUMPV(0x138);
}

NAKED void CKRenderContext::SetFogEnd(float End) {
    JUMPV(0x13c);
}

NAKED void CKRenderContext::SetFogDensity(float Density) {
    JUMPV(0x140);
}

NAKED void CKRenderContext::SetFogColor(CKDWORD Color) {
    JUMPV(0x144);
}

NAKED VXFOG_MODE CKRenderContext::GetFogMode() {
    JUMPV(0x148);
}

NAKED float CKRenderContext::GetFogStart() {
    JUMPV(0x14c);
}

NAKED float CKRenderContext::GetFogEnd() {
    JUMPV(0x150);
}

NAKED float CKRenderContext::GetFogDensity() {
    JUMPV(0x154);
}

NAKED CKDWORD CKRenderContext::GetFogColor() {
    JUMPV(0x158);
}

NAKED CKBOOL CKRenderContext::DrawPrimitive(VXPRIMITIVETYPE pType, CKWORD* indices, int indexcount, VxDrawPrimitiveData* data) {
    JUMPV(0x15c);
}

NAKED void CKRenderContext::SetWorldTransformationMatrix(const VxMatrix& M) {
    JUMPV(0x160);
}

NAKED void CKRenderContext::SetProjectionTransformationMatrix(const VxMatrix& M) {
    JUMPV(0x164);
}

NAKED void CKRenderContext::SetViewTransformationMatrix(const VxMatrix& M) {
    JUMPV(0x168);
}

NAKED const VxMatrix& CKRenderContext::GetWorldTransformationMatrix() {
    JUMPV(0x16c);
}

NAKED const VxMatrix& CKRenderContext::GetProjectionTransformationMatrix() {
    JUMPV(0x170);
}

NAKED const VxMatrix& CKRenderContext::GetViewTransformationMatrix() {
    JUMPV(0x174);
}

NAKED CKBOOL CKRenderContext::SetUserClipPlane(CKDWORD ClipPlaneIndex, const VxPlane& PlaneEquation) {
    JUMPV(0x178);
}

NAKED CKBOOL CKRenderContext::GetUserClipPlane(CKDWORD ClipPlaneIndex, VxPlane& PlaneEquation) {
    JUMPV(0x17c);
}

NAKED CKRenderObject* CKRenderContext::Pick(int x, int y, VxIntersectionDesc* oRes, CKBOOL iIgnoreUnpickable) {
    JUMPV(0x184);
}

NAKED CKERROR CKRenderContext::RectPick(const VxRect& r, XObjectPointerArray& oObjects, CKBOOL Intersect) {
    JUMPV(0x188);
}

NAKED void CKRenderContext::AttachViewpointToCamera(CKCamera* cam) {
    JUMPV(0x18c);
}

NAKED void CKRenderContext::DetachViewpointFromCamera() {
    JUMPV(0x190);
}

NAKED CKCamera* CKRenderContext::GetAttachedCamera() {
    JUMPV(0x194);
}

NAKED CK3dEntity* CKRenderContext::GetViewpoint() {
    JUMPV(0x198);
}

NAKED CKMaterial* CKRenderContext::GetBackgroundMaterial() {
    JUMPV(0x19c);
}

NAKED void CKRenderContext::GetBoundingBox(VxBbox* BBox) {
    JUMPV(0x1a0);
}

NAKED void CKRenderContext::GetStats(VxStats* stats) {
    JUMPV(0x1a4);
}

NAKED void CKRenderContext::SetCurrentMaterial(CKMaterial* mat, BOOL Lit) {
    JUMPV(0x1a8);
}

NAKED void CKRenderContext::Activate(CKBOOL active) {
    JUMPV(0x1ac);
}

NAKED int CKRenderContext::DumpToMemory(const VxRect& iRect, VXBUFFER_TYPE buffer, VxImageDescEx& desc) {
    JUMPV(0x1b0);
}

NAKED int CKRenderContext::CopyToVideo(const VxRect& iRect, VXBUFFER_TYPE buffer, VxImageDescEx& desc) {
    JUMPV(0x1b4);
}

NAKED CKERROR CKRenderContext::DumpToFile(CKSTRING filename, const VxRect& rect, VXBUFFER_TYPE buffer) {
    JUMPV(0x1b8);
}

NAKED VxDirectXData* CKRenderContext::GetDirectXInfo() {
    JUMPV(0x1bc);
}

NAKED void CKRenderContext::WarnEnterThread() {
    JUMPV(0x1c0);
}

NAKED void CKRenderContext::WarnExitThread() {
    JUMPV(0x1c4);
}

NAKED CK2dEntity* CKRenderContext::Pick2D(const Vx2DVector& v) {
    JUMPV(0x1c8);
}

NAKED CKBOOL CKRenderContext::SetRenderTarget(CKTexture* texture, int CubeMapFace) {
    JUMPV(0x1cc);
}

NAKED void CKRenderContext::AddRemoveSequence(CKBOOL Start) {
    JUMPV(0x1d0);
}

NAKED void CKRenderContext::SetTransparentMode(CKBOOL Trans) {
    JUMPV(0x1d4);
}

NAKED void CKRenderContext::AddDirtyRect(CKRECT* Rect) {
    JUMPV(0x1d8);
}

NAKED void CKRenderContext::RestoreScreenBackup() {
    JUMPV(0x1dc);
}

NAKED CKDWORD CKRenderContext::GetStencilFreeMask() {
    JUMPV(0x1e0);
}

NAKED void CKRenderContext::UsedStencilBits(CKDWORD stencilBits) {
    JUMPV(0x1e4);
}

NAKED int CKRenderContext::GetFirstFreeStencilBits() {
    JUMPV(0x1e8);
}

NAKED VxDrawPrimitiveData* CKRenderContext::LockCurrentVB(CKDWORD VertexCount) {
    JUMPV(0x1ec);
}

NAKED BOOL CKRenderContext::ReleaseCurrentVB() {
    JUMPV(0x1f0);
}

NAKED void CKRenderContext::SetTextureMatrix(const VxMatrix& M, int Stage) {
    JUMPV(0x1f4);
}

NAKED void CKRenderContext::SetStereoParameters(float EyeSeparation, float FocalLength) {
    JUMPV(0x1f8);
}

NAKED void CKRenderContext::GetStereoParameters(float& EyeSeparation, float& FocalLength) {
    JUMPV(0x1fc);
}

NAKED void CKRenderContext::SetViewport(const VxRect& iRect) {
    JUMPV(0x200);
}

NAKED void CKRenderContext::ScreenToViewpoint(const Vx2DVector& i2DPosition, VxVector* o3DPosition, CKBOOL iScreen) {
    JUMPV(0x204);
}

NAKED void CKRenderContext::SetOverriddenRendering(CK_OVERRIDE_RENDERING Or, CKMaterial* mat, const char* pass) {
    JUMPV(0x208);
}

NAKED void CKRenderContext::SetupLights() {
    JUMPV(0x20c);
}

NAKED void CKRenderContext::SetValuesOfUsedAutomatics(CKShader& iFx, CKMaterial* iMat, CK3dEntity* iEnt) {
    JUMPV(0x210);
}

NAKED CKBOOL CKRenderContext::IsStereoRenderingLeftEye() {
    JUMPV(0x214);
}

NAKED void CKRenderContext::SetStereoRenderMode(CK_STEREO_MODE iMode) {
    JUMPV(0x218);
}

NAKED CKBOOL CKRenderContext::IsRenderingShaderBatch() {
    JUMPV(0x21c);
}

NAKED float CKRenderContext::GetSurfacesVideoMemoryOccupation(int* NbTextures, int* NbSprites, float* TextureSize, float* SpriteSize) {
    JUMPV(0x220);
}

NAKED BOOL CKRenderContext::FlushPendingGPUCommands() {
    JUMPV(0x224);
}

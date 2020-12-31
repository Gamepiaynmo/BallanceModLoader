#include "CKTexture.h"

NAKED CKBOOL CKTexture::Create(int Width, int Height, int BPP, int Slot) {
	JUMPV(0x54);
}

NAKED CKBOOL CKTexture::LoadImage(CKSTRING Name, int Slot) {
	JUMPV(0x58);
}

NAKED CKBOOL CKTexture::LoadMovie(CKSTRING Name) {
	JUMPV(0x5c);
}

NAKED CKBOOL CKTexture::SetAsCurrent(CKRenderContext* Dev, CKBOOL Clamping, int TextureStage) {
	JUMPV(0x60);
}

NAKED CKBOOL CKTexture::Restore(CKBOOL Clamp) {
	JUMPV(0x64);
}

NAKED CKBOOL CKTexture::SystemToVideoMemory(CKRenderContext* Dev, CKBOOL Clamping) {
	JUMPV(0x68);
}

NAKED CKBOOL CKTexture::FreeVideoMemory() {
	JUMPV(0x6c);
}

NAKED CKBOOL CKTexture::IsInVideoMemory() {
	JUMPV(0x70);
}

NAKED CKBOOL CKTexture::CopyContext(CKRenderContext* ctx, VxRect* Src, VxRect* Dest, int CubeMapFace) {
	JUMPV(0x74);
}

NAKED CKBOOL CKTexture::UseMipmap(int UseMipMap) {
	JUMPV(0x78);
}

NAKED int CKTexture::GetMipmapCount() {
	JUMPV(0x7c);
}

NAKED CKBOOL CKTexture::GetVideoTextureDesc(VxImageDescEx& desc) {
	JUMPV(0x80);
}

NAKED VX_PIXELFORMAT CKTexture::GetVideoPixelFormat() {
	JUMPV(0x84);
}

NAKED CKBOOL CKTexture::GetSystemTextureDesc(VxImageDescEx& desc) {
	JUMPV(0x88);
}

NAKED void CKTexture::SetDesiredVideoFormat(VX_PIXELFORMAT pf) {
	JUMPV(0x8c);
}

NAKED VX_PIXELFORMAT CKTexture::GetDesiredVideoFormat() {
	JUMPV(0x90);
}

NAKED CKBOOL CKTexture::FlushSurfacePtr(int Slot) {
	JUMPV(0x94);
}

NAKED BOOL CKTexture::GetUserMipMapLevel(int Level, VxImageDescEx& ResultImage) {
	JUMPV(0x98);
}

NAKED int CKTexture::GetRstTextureIndex() {
	JUMPV(0x9c);
}

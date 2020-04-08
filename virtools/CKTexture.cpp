#include "CKTexture.h"

CKBOOL CKTexture::Create(int Width, int Height, int BPP, int Slot) {
	JUMPV(0x54);
}

CKBOOL CKTexture::LoadImage(CKSTRING Name, int Slot) {
	JUMPV(0x58);
}

CKBOOL CKTexture::LoadMovie(CKSTRING Name) {
	JUMPV(0x5c);
}

CKBOOL CKTexture::SetAsCurrent(CKRenderContext* Dev, CKBOOL Clamping, int TextureStage) {
	JUMPV(0x60);
}

CKBOOL CKTexture::Restore(CKBOOL Clamp) {
	JUMPV(0x64);
}

CKBOOL CKTexture::SystemToVideoMemory(CKRenderContext* Dev, CKBOOL Clamping) {
	JUMPV(0x68);
}

CKBOOL CKTexture::FreeVideoMemory() {
	JUMPV(0x6c);
}

CKBOOL CKTexture::IsInVideoMemory() {
	JUMPV(0x70);
}

CKBOOL CKTexture::CopyContext(CKRenderContext* ctx, VxRect* Src, VxRect* Dest, int CubeMapFace) {
	JUMPV(0x74);
}

CKBOOL CKTexture::UseMipmap(int UseMipMap) {
	JUMPV(0x78);
}

int CKTexture::GetMipmapCount() {
	JUMPV(0x7c);
}

CKBOOL CKTexture::GetVideoTextureDesc(VxImageDescEx& desc) {
	JUMPV(0x80);
}

VX_PIXELFORMAT CKTexture::GetVideoPixelFormat() {
	JUMPV(0x84);
}

CKBOOL CKTexture::GetSystemTextureDesc(VxImageDescEx& desc) {
	JUMPV(0x88);
}

CKBOOL CKTexture::SetUserMipMapMode(CKBOOL UserMipmap) {
	UNDEFINED;
}

BOOL CKTexture::GetUserMipMapLevel(int Level, VxImageDescEx& ResultImage) {
	UNDEFINED;
}

int CKTexture::GetRstTextureIndex() {
	UNDEFINED;
}

BOOL CKTexture::LockVideoMemory(VxImageDescEx& Surface, int MipLevel, VX_LOCKFLAGS Flags) {
	UNDEFINED;
}

void CKTexture::UnlockVideoMemory(int MipLevel) {
	UNDEFINED;
}

BOOL CKTexture::VideoToSystemMemory() {
	UNDEFINED;
}

void* CKTexture::GetRstTextureObject() {
	UNDEFINED;
}

BOOL CKTexture::EnsureVideoMemory(CKRenderContext* ctx, CKBOOL Clamping) {
	UNDEFINED;
}

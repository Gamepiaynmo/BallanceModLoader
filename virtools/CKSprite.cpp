#include "CKSprite.h"

NAKED CKBOOL CKSprite::Create(int Width, int Height, int BPP, int Slot) {
	JUMPV(0x124);
}

NAKED CKBOOL CKSprite::LoadImage(CKSTRING Name, int Slot) {
	JUMPV(0x128);
}

NAKED CKBOOL CKSprite::SaveImage(CKSTRING Name, int Slot, BOOL CKUseFormat) {
	JUMPV(0x12c);
}

NAKED CKBOOL CKSprite::LoadMovie(CKSTRING Name, int width, int height, int Bpp) {
	JUMPV(0x130);
}

NAKED CKSTRING CKSprite::GetMovieFileName() {
	JUMPV(0x134);
}

NAKED CKMovieReader* CKSprite::GetMovieReader() {
	JUMPV(0x138);
}

NAKED CKBYTE* CKSprite::LockSurfacePtr(int Slot) {
	JUMPV(0x13c);
}

NAKED CKBOOL CKSprite::ReleaseSurfacePtr(int Slot) {
	JUMPV(0x140);
}

NAKED CKSTRING CKSprite::GetSlotFileName(int Slot) {
	JUMPV(0x144);
}

NAKED CKBOOL CKSprite::SetSlotFileName(int Slot, CKSTRING Filename) {
	JUMPV(0x148);
}

NAKED int CKSprite::GetWidth() {
	JUMPV(0x14c);
}

NAKED int CKSprite::GetHeight() {
	JUMPV(0x150);
}

NAKED int CKSprite::GetSlotCount() {
	JUMPV(0x16c);
}

NAKED CKBOOL CKSprite::SetSlotCount(int Count) {
	JUMPV(0x170);
}

NAKED CKBOOL CKSprite::SetCurrentSlot(int Slot) {
	JUMPV(0x174);
}

NAKED int CKSprite::GetCurrentSlot() {
	JUMPV(0x178);
}

NAKED CKBOOL CKSprite::ReleaseSlot(int Slot) {
	JUMPV(0x17c);
}

NAKED CKBOOL CKSprite::ReleaseAllSlots() {
	JUMPV(0x180);
}

NAKED CKBOOL CKSprite::SetPixel(int x, int y, CKDWORD col, int slot) {
	JUMPV(0x184);
}

NAKED CKDWORD CKSprite::GetPixel(int x, int y, int slot) {
	JUMPV(0x188);
}

NAKED CKDWORD CKSprite::GetTransparentColor() {
	JUMPV(0x18c);
}

NAKED void CKSprite::SetTransparentColor(CKDWORD Color) {
	JUMPV(0x190);
}

NAKED void CKSprite::SetTransparent(CKBOOL Transparency) {
	JUMPV(0x194);
}

NAKED CKBOOL CKSprite::IsTransparent() {
	JUMPV(0x198);
}

NAKED CKBOOL CKSprite::Restore(CKBOOL Clamp) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::SystemToVideoMemory(CKRenderContext* Dev, CKBOOL Clamping) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::FreeVideoMemory() {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::IsInVideoMemory() {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::CopyContext(CKRenderContext* ctx, VxRect* Src, VxRect* Dest) {
	UNDEFINED;
}

NAKED CKERROR CKSprite::Draw(CKRenderContext* context) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::GetVideoTextureDesc(VxImageDescEx& desc) {
	UNDEFINED;
}

NAKED VX_PIXELFORMAT CKSprite::GetVideoPixelFormat() {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::GetSystemTextureDesc(VxImageDescEx& desc) {
	UNDEFINED;
}

NAKED void CKSprite::SetDesiredVideoFormat(VX_PIXELFORMAT pf) {
	UNDEFINED;
}

NAKED VX_PIXELFORMAT CKSprite::GetDesiredVideoFormat() {
	UNDEFINED;
}

NAKED void CKSprite::SetSystemCaching(CK_BITMAP_SYSTEMCACHING iOptions) {
	UNDEFINED;
}

NAKED CK_BITMAP_SYSTEMCACHING CKSprite::GetSystemCaching() {
	UNDEFINED;
}

NAKED CK_BITMAP_SAVEOPTIONS CKSprite::GetSaveOptions() {
	UNDEFINED;
}

NAKED void CKSprite::SetSaveOptions(CK_BITMAP_SAVEOPTIONS Options) {
	UNDEFINED;
}

NAKED CKBitmapProperties* CKSprite::GetSaveFormat() {
	UNDEFINED;
}

NAKED void CKSprite::SetSaveFormat(CKBitmapProperties* format) {
	UNDEFINED;
}

NAKED void CKSprite::SetPickThreshold(int pt) {
	UNDEFINED;
}

NAKED int CKSprite::GetPickThreshold() {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::ToRestore() {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::HasOriginalFile() {
	UNDEFINED;
}

NAKED BOOL CKSprite::LockVideoMemory(int SubSurfaceIndex, VxImageDescEx& Surface, CKRECT& SubRect, VX_LOCKFLAGS Flags) {
	UNDEFINED;
}

NAKED void CKSprite::UnlockVideoMemory(int SubSurfaceIndex) {
	UNDEFINED;
}

NAKED int CKSprite::GetVideoMemorySurfaceCount() {
	UNDEFINED;
}

NAKED void CKSprite::SetRenderOptions(const VxSpriteRenderOptions& option) {
	UNDEFINED;
}

NAKED const VxSpriteRenderOptions& CKSprite::GetRenderOptions() {
	UNDEFINED;
}

NAKED void CKSprite::SetAlphaTest(CKBOOL Enable, CKBYTE RefValue, VXCMPFUNC AlphaTestFunc) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::AlphaTestEnabled() {
	UNDEFINED;
}

NAKED CKBYTE CKSprite::GetAlphaTestRefValue() {
	UNDEFINED;
}

NAKED VXCMPFUNC CKSprite::GetAlphaTestFunc() {
	UNDEFINED;
}

NAKED void CKSprite::SetFiltering(CKBOOL Enable) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::FilteringEnabled() {
	UNDEFINED;
}

NAKED void CKSprite::SetBlending(CKBOOL Enable, VXBLEND_MODE SrcBlendMode, VXBLEND_MODE DstBlendMode) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::BlendingEnabled() {
	UNDEFINED;
}

NAKED VXBLEND_MODE CKSprite::GetSourceBlendMode() {
	UNDEFINED;
}

NAKED VXBLEND_MODE CKSprite::GetDestinationBlendMode() {
	UNDEFINED;
}

NAKED void CKSprite::SetColorModulate(CKBOOL Enable, const VxColor& color) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::ColorModulateEnabled() {
	UNDEFINED;
}

NAKED VxColor CKSprite::GetModulateColor() {
	UNDEFINED;
}

NAKED void CKSprite::SetDynamicHint(CKBOOL Dynamic) {
	UNDEFINED;
}

NAKED CKBOOL CKSprite::FlushSurfacePtr(int Slot) {
	UNDEFINED;
}

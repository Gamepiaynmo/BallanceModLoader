#include "CKBitmapData.h"

NAKED CKBOOL CKBitmapData::CreateImage(int Width, int Height, int BPP, int Slot, void* ImagePointer) {
	JUMP(0x2402FF59);
}

NAKED CKBOOL CKBitmapData::SaveImage(CKSTRING Name, int Slot, CKBOOL CKUseFormat) {
	JUMP(0x2402FBBA);
}

NAKED CKBOOL CKBitmapData::SaveImageAlpha(CKSTRING Name, int Slot) {
	JUMP(0x2402FD89);
}

NAKED CKSTRING CKBitmapData::GetMovieFileName() {
	JUMP(0x2403015B);
}

NAKED CKMovieReader* CKBitmapData::GetMovieReader() {
	JUMP(0x2403AF90);
}

NAKED CKBYTE* CKBitmapData::LockSurfacePtr(int Slot) {
	JUMP(0x24030120);
}

NAKED CKBOOL CKBitmapData::ReleaseSurfacePtr(int Slot) {
	JUMP(0x24030151);
}

NAKED CKSTRING CKBitmapData::GetSlotFileName(int Slot) {
	JUMP(0x24030170);
}

NAKED CKBOOL CKBitmapData::SetSlotFileName(int Slot, CKSTRING Filename) {
	JUMP(0x2403019C);
}

NAKED int CKBitmapData::GetWidth() {
	JUMP(0x2403AF9D);
}

NAKED int CKBitmapData::GetHeight() {
	JUMP(0x2403AFA1);
}

NAKED CKBOOL CKBitmapData::GetImageDesc(VxImageDescEx& oDesc) {
	JUMP(0x240302EC);
}

NAKED int CKBitmapData::GetSlotCount() {
	JUMP(0x240302CB);
}

NAKED CKBOOL CKBitmapData::SetSlotCount(int Count) {
	JUMP(0x24030201);
}

NAKED CKBOOL CKBitmapData::SetCurrentSlot(int Slot) {
	JUMP(0x24030462);
}

NAKED int CKBitmapData::GetCurrentSlot() {
	JUMP(0x2403051D);
}

NAKED CKBOOL CKBitmapData::ReleaseSlot(int Slot) {
	JUMP(0x2403052B);
}

NAKED CKBOOL CKBitmapData::ReleaseAllSlots() {
	JUMP(0x240305B5);
}

NAKED CKBOOL CKBitmapData::SetPixel(int x, int y, CKDWORD col, int slot) {
	JUMP(0x240300A5);
}

NAKED CKDWORD CKBitmapData::GetPixel(int x, int y, int slot) {
	JUMP(0x240300E6);
}

NAKED CKDWORD CKBitmapData::GetTransparentColor() {
	JUMP(0x2403AFC8);
}

NAKED void CKBitmapData::SetTransparentColor(CKDWORD Color) {
	JUMP(0x240301CA);
}

NAKED void CKBitmapData::SetTransparent(CKBOOL Transparency) {
	JUMP(0x240301E5);
}

NAKED CKBOOL CKBitmapData::IsTransparent() {
	JUMP(0x2403AFCC);
}

NAKED CK_BITMAP_SAVEOPTIONS CKBitmapData::GetSaveOptions() {
	JUMP(0x2403AFD3);
}

NAKED void CKBitmapData::SetSystemCaching(CK_BITMAP_SYSTEMCACHING iOptions) {
	UNDEFINED;
}

NAKED CK_BITMAP_SYSTEMCACHING CKBitmapData::GetSystemCaching() {
	UNDEFINED;
}

NAKED void CKBitmapData::SetSaveOptions(CK_BITMAP_SAVEOPTIONS Options) {
	JUMP(0x2403AFD7);
}

NAKED CKBitmapProperties* CKBitmapData::GetSaveFormat() {
	JUMP(0x2403AFE1);
}

NAKED void CKBitmapData::SetSaveFormat(CKBitmapProperties* format) {
	JUMP(0x24030088);
}

NAKED void CKBitmapData::SetPickThreshold(int pt) {
	JUMP(0x2403AFE5);
}

NAKED int CKBitmapData::GetPickThreshold() {
	JUMP(0x2403AFEF);
}

NAKED void CKBitmapData::SetCubeMap(CKBOOL CubeMap) {
	JUMP(0x2403AFF3);
}

NAKED CKBOOL CKBitmapData::IsCubeMap() {
	JUMP(0x2403B012);
}

NAKED void CKBitmapData::SetVolumeMap(CKBOOL VolumeMap) {
	UNDEFINED;
}

NAKED CKBOOL CKBitmapData::IsVolumeMap() {
	UNDEFINED;
}

NAKED CKBOOL CKBitmapData::HasOriginalFile() {
	UNDEFINED;
}

NAKED CKBOOL CKBitmapData::ResizeImages(int Width, int Height) {
	JUMP(0x2403032E);
}

NAKED void CKBitmapData::SetDynamicHint(CKBOOL Dynamic) {
	UNDEFINED;
}

NAKED CKBOOL CKBitmapData::GetDynamicHint() {
	UNDEFINED;
}

NAKED void CKBitmapData::AuthorizeConditionalNonPow2(CKBOOL iAuthorize) {
	UNDEFINED;
}

NAKED CKBOOL CKBitmapData::IsConditionalNonPow2Authorized() {
	UNDEFINED;
}

#include "CKDef.h"

NAKED void InitVxMath() {
	UNDEFINED;
}

NAKED void VxDetectProcessor() {
	UNDEFINED;
}

NAKED void InterpolateFloatArray(void* Res, void* array1, void* array2, float factor, int count) {
	JUMP(0x24282B40);
}

NAKED void InterpolateVectorArray(void* Res, void* Inarray1, void* Inarray2, float factor, int count, DWORD StrideRes, DWORD StrideIn) {
	JUMP(0x24282B80);
}

NAKED void MultiplyVectorArray(void* Res, void* Inarray1, const VxVector& factor, int count, DWORD StrideRes, DWORD StrideIn) {
	UNDEFINED;
}

NAKED void MultiplyVector2Array(void* Res, void* Inarray1, const Vx2DVector& factor, int count, DWORD StrideRes, DWORD StrideIn) {
	UNDEFINED;
}

NAKED void MultiplyVector4Array(void* Res, void* Inarray1, const VxVector4& factor, int count, DWORD StrideRes, DWORD StrideIn) {
	UNDEFINED;
}

NAKED void MultiplyAddVectorArray(void* Res, void* Inarray1, const VxVector& factor, const VxVector& offset, int count, DWORD StrideRes, DWORD StrideIn) {
	UNDEFINED;
}

NAKED void MultiplyAddVector4Array(void* Res, void* Inarray1, const VxVector4& factor, const VxVector4& offset, int count, DWORD StrideRes, DWORD StrideIn) {
	UNDEFINED;
}

NAKED BOOL VxTransformBox2D(const VxMatrix& World_ProjectionMat, const VxBbox& box, VxRect* ScreenSize, VxRect* Extents, VXCLIP_FLAGS& OrClipFlags, VXCLIP_FLAGS& AndClipFlags) {
	JUMP(0x24282C90);
}

NAKED void VxProjectBoxZExtents(const VxMatrix& World_ProjectionMat, const VxBbox& box, float& ZhMin, float& ZhMax) {
	JUMP(0x2429A570);
}

NAKED BOOL VxFillStructure(int Count, void* Dst, DWORD Stride, DWORD SizeSrc, void* Src) {
	JUMP(0x24282610);
}

NAKED BOOL VxCopyStructure(int Count, void* Dst, DWORD OutStride, DWORD SizeSrc, void* Src, DWORD InStride) {
	JUMP(0x24282770);
}

NAKED BOOL VxFillStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, void* Src) {
	JUMP(0x24282610);
}

NAKED BOOL VxCopyStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, const VxStridedData& Src) {
	JUMP(0x24282770);
}

NAKED BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, int* Indices, int IndexCount) {
	JUMP(0x242828F0);
}

NAKED BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, WORD* Indices, int IndexCount) {
	JUMP(0x242828F0);
}

NAKED void VxDoBlit(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc) {
	JUMP(0x2428FBD0);
}

NAKED void VxDoBlitUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc) {
	JUMP(0x2428FC30);
}

NAKED void VxDoBlitDeInterleaved(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First) {
	UNDEFINED;
}

NAKED void VxDoBlitDeInterleavedUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First) {
	UNDEFINED;
}

NAKED void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE AlphaValue) {
	JUMP(0x2428FC60);
}

NAKED void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE* AlphaValues) {
	JUMP(0x2428FC90);
}

NAKED void VxGetBitCounts(const VxImageDescEx& desc, DWORD& Rbits, DWORD& Gbits, DWORD& Bbits, DWORD& Abits) {
	JUMP(0x2428FD90);
}

NAKED void VxGetBitShifts(const VxImageDescEx& desc, DWORD& Rshift, DWORD& Gshift, DWORD& Bshift, DWORD& Ashift) {
	JUMP(0x2428FDE0);
}

NAKED void VxGenerateMipMap(const VxImageDescEx& src_desc, BYTE* DestBuffer) {
	JUMP(0x24282260);
}

NAKED void VxResizeImage32(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc) {
	JUMP(0x2428FC00);
}

NAKED BOOL VxConvertToNormalMap(const VxImageDescEx& image, DWORD ColorMask) {
	JUMP(0x2428F5E0);
}

NAKED BOOL VxConvertToBumpMap(const VxImageDescEx& image) {
	JUMP(0x2428F870);
}

NAKED DWORD GetBitCount(DWORD dwMask) {
	JUMP(0x2428FE30);
}

NAKED DWORD GetBitShift(DWORD dwMask) {
	JUMP(0x2428FE50);
}

NAKED VX_PIXELFORMAT VxImageDesc2PixelFormat(const VxImageDescEx& desc) {
	JUMP(0x2428FCC0);
}

NAKED void VxPixelFormat2ImageDesc(VX_PIXELFORMAT Pf, VxImageDescEx& desc) {
	JUMP(0x2428FCD0);
}

NAKED const char* VxPixelFormat2String(VX_PIXELFORMAT Pf) {
	JUMP(0x2428FCF0);
}

NAKED void VxBppToMask(VxImageDescEx& desc) {
	JUMP(0x2428FD00);
}

NAKED int GetQuantizationSamplingFactor() {
	JUMP(0x2428FE70);
}

NAKED void SetQuantizationSamplingFactor(int sf) {
	JUMP(0x2428FE80);
}

NAKED char* GetProcessorDescription() {
	JUMP(0x24299200);
}

NAKED int GetProcessorFrequency() {
	JUMP(0x24299250);
}

NAKED DWORD GetProcessorFeatures() {
	JUMP(0x24299210);
}

NAKED void ModifyProcessorFeatures(DWORD Add, DWORD Remove) {
	JUMP(0x24299220);
}

NAKED ProcessorsType GetProcessorType() {
	JUMP(0x24299240);
}

NAKED BOOL VxPtInRect(CKRECT* rect, CKPOINT* pt) {
	JUMP(0x2429A530);
}

NAKED BOOL VxComputeBestFitBBox(const BYTE* Points, const DWORD Stride, const int Count, VxMatrix& BBoxMatrix, const float AdditionnalBorder) {
	JUMP(0x2428E1A0);
}

NAKED void VxAddDirectorySeparator(XString& path) {
	UNDEFINED;
}

NAKED void VxConvertPathToSystemPath(XString& path) {
	UNDEFINED;
}

NAKED void* VxNewAligned(int size, int align) {
	JUMP(0x24299260);
}

NAKED void VxDeleteAligned(void* ptr) {
	JUMP(0x24299290);
}

NAKED BOOL VxIsAllocatedByNewAligned(void* ptr, int alignement) {
	UNDEFINED;
}
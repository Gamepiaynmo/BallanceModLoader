#pragma once

typedef XArray<void*> XVoidArray;

#include "VxMutex.h"
#include "CKGlobals.h"
struct VxImageDescEx;

void InitVxMath();
void VxDetectProcessor();

//------ Interpolation
VX_EXPORT void InterpolateFloatArray(void* Res, void* array1, void* array2, float factor, int count);
VX_EXPORT void InterpolateVectorArray(void* Res, void* Inarray1, void* Inarray2, float factor, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT void MultiplyVectorArray(void* Res, void* Inarray1, const VxVector& factor, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT void MultiplyVector2Array(void* Res, void* Inarray1, const Vx2DVector& factor, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT void MultiplyVector4Array(void* Res, void* Inarray1, const VxVector4& factor, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT void MultiplyAddVectorArray(void* Res, void* Inarray1, const VxVector& factor, const VxVector& offset, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT void MultiplyAddVector4Array(void* Res, void* Inarray1, const VxVector4& factor, const VxVector4& offset, int count, DWORD StrideRes, DWORD StrideIn);
VX_EXPORT BOOL VxTransformBox2D(const VxMatrix& World_ProjectionMat, const VxBbox& box, VxRect* ScreenSize, VxRect* Extents, VXCLIP_FLAGS& OrClipFlags, VXCLIP_FLAGS& AndClipFlags);
VX_EXPORT void VxProjectBoxZExtents(const VxMatrix& World_ProjectionMat, const VxBbox& box, float& ZhMin, float& ZhMax);

//------- Structure copying
VX_EXPORT BOOL VxFillStructure(int Count, void* Dst, DWORD Stride, DWORD SizeSrc, void* Src);
VX_EXPORT BOOL VxCopyStructure(int Count, void* Dst, DWORD OutStride, DWORD SizeSrc, void* Src, DWORD InStride);
VX_EXPORT BOOL VxFillStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, void* Src);
VX_EXPORT BOOL VxCopyStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, const VxStridedData& Src);


VX_EXPORT BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, int* Indices, int IndexCount);
VX_EXPORT BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, WORD* Indices, int IndexCount);

//---- Graphic Utilities
VX_EXPORT 	void VxDoBlit(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);
VX_EXPORT 	void VxDoBlitUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);

VX_EXPORT 	void VxDoBlitDeInterleaved(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First);
VX_EXPORT 	void VxDoBlitDeInterleavedUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First);

VX_EXPORT 	void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE AlphaValue);
VX_EXPORT 	void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE* AlphaValues);

VX_EXPORT 	void VxGetBitCounts(const VxImageDescEx& desc, DWORD& Rbits, DWORD& Gbits, DWORD& Bbits, DWORD& Abits);
VX_EXPORT 	void VxGetBitShifts(const VxImageDescEx& desc, DWORD& Rshift, DWORD& Gshift, DWORD& Bshift, DWORD& Ashift);

VX_EXPORT 	void VxGenerateMipMap(const VxImageDescEx& src_desc, BYTE* DestBuffer);
VX_EXPORT 	void VxResizeImage32(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);

VX_EXPORT	BOOL VxConvertToNormalMap(const VxImageDescEx& image, DWORD ColorMask);
VX_EXPORT	BOOL VxConvertToBumpMap(const VxImageDescEx& image);

VX_EXPORT 	DWORD GetBitCount(DWORD dwMask);
VX_EXPORT 	DWORD GetBitShift(DWORD dwMask);

VX_EXPORT 	VX_PIXELFORMAT  VxImageDesc2PixelFormat(const VxImageDescEx& desc);
VX_EXPORT 	void			VxPixelFormat2ImageDesc(VX_PIXELFORMAT Pf, VxImageDescEx& desc);
VX_EXPORT 	const char* VxPixelFormat2String(VX_PIXELFORMAT Pf);

VX_EXPORT	void	VxBppToMask(VxImageDescEx& desc);

VX_EXPORT	int		GetQuantizationSamplingFactor();
VX_EXPORT	void	SetQuantizationSamplingFactor(int sf);

//---- Processor features
VX_EXPORT	char* GetProcessorDescription();
VX_EXPORT	int				GetProcessorFrequency();
VX_EXPORT	DWORD			GetProcessorFeatures();
VX_EXPORT	void			ModifyProcessorFeatures(DWORD Add, DWORD Remove);
VX_EXPORT	ProcessorsType	GetProcessorType();

VX_EXPORT BOOL VxPtInRect(CKRECT* rect, CKPOINT* pt);

// Summary: Compute best Fit Box for a set of points
// 
VX_EXPORT BOOL VxComputeBestFitBBox(const BYTE* Points, const DWORD Stride, const int Count, VxMatrix& BBoxMatrix, const float AdditionnalBorder);

VX_EXPORT void VxAddDirectorySeparator(XString& path);
VX_EXPORT void VxConvertPathToSystemPath(XString& path);

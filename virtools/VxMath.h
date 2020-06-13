#pragma once

typedef XArray<void*> XVoidArray;

#include "VxMutex.h"
#include "CKGlobals.h"
struct VxImageDescEx;

void InitVxMath();
void VxDetectProcessor();

//------ Interpolation
BML_EXPORT void InterpolateFloatArray(void* Res, void* array1, void* array2, float factor, int count);
BML_EXPORT void InterpolateVectorArray(void* Res, void* Inarray1, void* Inarray2, float factor, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT void MultiplyVectorArray(void* Res, void* Inarray1, const VxVector& factor, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT void MultiplyVector2Array(void* Res, void* Inarray1, const Vx2DVector& factor, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT void MultiplyVector4Array(void* Res, void* Inarray1, const VxVector4& factor, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT void MultiplyAddVectorArray(void* Res, void* Inarray1, const VxVector& factor, const VxVector& offset, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT void MultiplyAddVector4Array(void* Res, void* Inarray1, const VxVector4& factor, const VxVector4& offset, int count, DWORD StrideRes, DWORD StrideIn);
BML_EXPORT BOOL VxTransformBox2D(const VxMatrix& World_ProjectionMat, const VxBbox& box, VxRect* ScreenSize, VxRect* Extents, VXCLIP_FLAGS& OrClipFlags, VXCLIP_FLAGS& AndClipFlags);
BML_EXPORT void VxProjectBoxZExtents(const VxMatrix& World_ProjectionMat, const VxBbox& box, float& ZhMin, float& ZhMax);

//------- Structure copying
BML_EXPORT BOOL VxFillStructure(int Count, void* Dst, DWORD Stride, DWORD SizeSrc, void* Src);
BML_EXPORT BOOL VxCopyStructure(int Count, void* Dst, DWORD OutStride, DWORD SizeSrc, void* Src, DWORD InStride);
BML_EXPORT BOOL VxFillStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, void* Src);
BML_EXPORT BOOL VxCopyStructure(int Count, const VxStridedData& Dst, DWORD SizeSrc, const VxStridedData& Src);


BML_EXPORT BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, int* Indices, int IndexCount);
BML_EXPORT BOOL VxIndexedCopy(const VxStridedData& Dst, const VxStridedData& Src, DWORD SizeSrc, WORD* Indices, int IndexCount);

//---- Graphic Utilities
BML_EXPORT 	void VxDoBlit(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);
BML_EXPORT 	void VxDoBlitUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);

BML_EXPORT 	void VxDoBlitDeInterleaved(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First);
BML_EXPORT 	void VxDoBlitDeInterleavedUpsideDown(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc, const BOOL iField1First);

BML_EXPORT 	void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE AlphaValue);
BML_EXPORT 	void VxDoAlphaBlit(const VxImageDescEx& dst_desc, BYTE* AlphaValues);

BML_EXPORT 	void VxGetBitCounts(const VxImageDescEx& desc, DWORD& Rbits, DWORD& Gbits, DWORD& Bbits, DWORD& Abits);
BML_EXPORT 	void VxGetBitShifts(const VxImageDescEx& desc, DWORD& Rshift, DWORD& Gshift, DWORD& Bshift, DWORD& Ashift);

BML_EXPORT 	void VxGenerateMipMap(const VxImageDescEx& src_desc, BYTE* DestBuffer);
BML_EXPORT 	void VxResizeImage32(const VxImageDescEx& src_desc, const VxImageDescEx& dst_desc);

BML_EXPORT	BOOL VxConvertToNormalMap(const VxImageDescEx& image, DWORD ColorMask);
BML_EXPORT	BOOL VxConvertToBumpMap(const VxImageDescEx& image);

BML_EXPORT 	DWORD GetBitCount(DWORD dwMask);
BML_EXPORT 	DWORD GetBitShift(DWORD dwMask);

BML_EXPORT 	VX_PIXELFORMAT  VxImageDesc2PixelFormat(const VxImageDescEx& desc);
BML_EXPORT 	void			VxPixelFormat2ImageDesc(VX_PIXELFORMAT Pf, VxImageDescEx& desc);
BML_EXPORT 	const char* VxPixelFormat2String(VX_PIXELFORMAT Pf);

BML_EXPORT	void	VxBppToMask(VxImageDescEx& desc);

BML_EXPORT	int		GetQuantizationSamplingFactor();
BML_EXPORT	void	SetQuantizationSamplingFactor(int sf);

//---- Processor features
BML_EXPORT	char* GetProcessorDescription();
BML_EXPORT	int				GetProcessorFrequency();
BML_EXPORT	DWORD			GetProcessorFeatures();
BML_EXPORT	void			ModifyProcessorFeatures(DWORD Add, DWORD Remove);
BML_EXPORT	ProcessorsType	GetProcessorType();

BML_EXPORT BOOL VxPtInRect(CKRECT* rect, CKPOINT* pt);

// Summary: Compute best Fit Box for a set of points
// 
BML_EXPORT BOOL VxComputeBestFitBBox(const BYTE* Points, const DWORD Stride, const int Count, VxMatrix& BBoxMatrix, const float AdditionnalBorder);

BML_EXPORT void VxAddDirectorySeparator(XString& path);
BML_EXPORT void VxConvertPathToSystemPath(XString& path);

#pragma once

#include "CKDef.h"
#include "CK2dEntity.h"
#include "CKMaterial.h"

#undef LoadImage

class CKMovieReader;

typedef enum VX_LOCKFLAGS {
	VX_LOCK_DEFAULT = 0x00000000,
	VX_LOCK_WRITEONLY = 0x00000001,
	VX_LOCK_READONLY = 0x00000002,
	VX_LOCK_DISCARD = 0x00000004,
} VX_LOCKFLAGS;

struct VxSpriteRenderOptions {
	DWORD ModulateColor;

	DWORD Options : 4;
	VXCMPFUNC AlphaTestFunc : 4;
	VXBLEND_MODE SrcBlendMode : 4;
	DWORD Options2 : 4;
	DWORD DstBlendMode : 8;
	DWORD AlphaRefValue : 8;
};

class BML_EXPORT CKSprite : public CK2dEntity {
public:
	CKBOOL Create(int Width, int Height, int BPP = 32, int Slot = 0);
	CKBOOL LoadImage(CKSTRING Name, int Slot = 0);
	CKBOOL SaveImage(CKSTRING Name, int Slot = 0, BOOL CKUseFormat = FALSE);
	CKBOOL LoadMovie(CKSTRING Name, int width = 0, int height = 0, int Bpp = 16);
	CKSTRING GetMovieFileName();
	CKMovieReader* GetMovieReader();
	CKBYTE* LockSurfacePtr(int Slot = -1);
	CKBOOL ReleaseSurfacePtr(int Slot = -1);
	CKSTRING GetSlotFileName(int Slot);
	CKBOOL SetSlotFileName(int Slot, CKSTRING Filename);
	int GetWidth();
	int GetHeight();
	int GetSlotCount();
	CKBOOL SetSlotCount(int Count);
	CKBOOL SetCurrentSlot(int Slot);
	int GetCurrentSlot();
	CKBOOL ReleaseSlot(int Slot);
	CKBOOL ReleaseAllSlots();
	CKBOOL SetPixel(int x, int y, CKDWORD col, int slot = -1);
	CKDWORD GetPixel(int x, int y, int slot = -1);
	CKDWORD GetTransparentColor();
	void SetTransparentColor(CKDWORD Color);
	void SetTransparent(CKBOOL Transparency);
	CKBOOL IsTransparent();
	CKBOOL Restore(CKBOOL Clamp = FALSE);
	CKBOOL SystemToVideoMemory(CKRenderContext* Dev, CKBOOL Clamping = FALSE);
	CKBOOL FreeVideoMemory();
	CKBOOL IsInVideoMemory();
	CKBOOL CopyContext(CKRenderContext* ctx, VxRect* Src, VxRect* Dest);
	CKERROR Draw(CKRenderContext* context);
	CKBOOL GetVideoTextureDesc(VxImageDescEx& desc);
	VX_PIXELFORMAT GetVideoPixelFormat();
	CKBOOL GetSystemTextureDesc(VxImageDescEx& desc);
	void SetDesiredVideoFormat(VX_PIXELFORMAT pf);
	VX_PIXELFORMAT GetDesiredVideoFormat();
	void SetSystemCaching(CK_BITMAP_SYSTEMCACHING iOptions);
	CK_BITMAP_SYSTEMCACHING GetSystemCaching();
	CK_BITMAP_SAVEOPTIONS GetSaveOptions();
	void SetSaveOptions(CK_BITMAP_SAVEOPTIONS Options);
	CKBitmapProperties* GetSaveFormat();
	void SetSaveFormat(CKBitmapProperties* format);
	void SetPickThreshold(int pt);
	int GetPickThreshold();
	CKBOOL ToRestore();
	CKBOOL HasOriginalFile();
	BOOL LockVideoMemory(int SubSurfaceIndex, VxImageDescEx& Surface, CKRECT& SubRect, VX_LOCKFLAGS Flags = VX_LOCK_DEFAULT);
	void UnlockVideoMemory(int SubSurfaceIndex);
	int GetVideoMemorySurfaceCount();
	void SetRenderOptions(const VxSpriteRenderOptions& option);
	const VxSpriteRenderOptions& GetRenderOptions();
	void SetAlphaTest(CKBOOL Enable, CKBYTE RefValue, VXCMPFUNC AlphaTestFunc);
	CKBOOL AlphaTestEnabled();
	CKBYTE GetAlphaTestRefValue();
	VXCMPFUNC GetAlphaTestFunc();
	void SetFiltering(CKBOOL Enable);
	CKBOOL FilteringEnabled();
	void SetBlending(CKBOOL Enable, VXBLEND_MODE SrcBlendMode, VXBLEND_MODE DstBlendMode);
	CKBOOL BlendingEnabled();
	VXBLEND_MODE GetSourceBlendMode();
	VXBLEND_MODE GetDestinationBlendMode();
	void SetColorModulate(CKBOOL Enable, const VxColor& color);
	CKBOOL ColorModulateEnabled();
	VxColor GetModulateColor();
	void SetDynamicHint(CKBOOL Dynamic);
	CKBOOL FlushSurfacePtr(int Slot = -1);

protected:
	CKSprite() {};
	~CKSprite() {};
};
#pragma once

#include "CKDef.h"
#include "CKBeObject.h"
#include "CKBitmapData.h"
#include "CKSprite.h"

#undef LoadImage

class BML_EXPORT CKTexture : public CKBeObject, public CKBitmapData {
public:
	CKBOOL Create(int Width, int Height, int BPP = 32, int Slot = 0);
	CKBOOL LoadImage(CKSTRING Name, int Slot = 0);
	CKBOOL LoadMovie(CKSTRING Name);
	CKBOOL SetAsCurrent(CKRenderContext* Dev, CKBOOL Clamping = FALSE, int TextureStage = 0);
	CKBOOL Restore(CKBOOL Clamp = FALSE);
	CKBOOL SystemToVideoMemory(CKRenderContext* Dev, CKBOOL Clamping = FALSE);
	CKBOOL FreeVideoMemory();
	CKBOOL IsInVideoMemory();
	CKBOOL CopyContext(CKRenderContext* ctx, VxRect* Src, VxRect* Dest, int CubeMapFace = 0);
	CKBOOL UseMipmap(int UseMipMap);
	int GetMipmapCount();
	CKBOOL GetVideoTextureDesc(VxImageDescEx& desc);
	VX_PIXELFORMAT GetVideoPixelFormat();
	CKBOOL GetSystemTextureDesc(VxImageDescEx& desc);
	void SetDesiredVideoFormat(VX_PIXELFORMAT pf);
	VX_PIXELFORMAT GetDesiredVideoFormat();
	CKBOOL FlushSurfacePtr(int Slot = -1);
	BOOL GetUserMipMapLevel(int Level, VxImageDescEx& ResultImage);
	int GetRstTextureIndex();

protected:
	CKTexture() {};
	~CKTexture() {};
};
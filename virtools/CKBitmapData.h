#pragma once

#include "CKDef.h"

#define CKBITMAPDATA_INVALID 1
#define CKBITMAPDATA_TRANSPARENT 2
#define CKBITMAPDATA_FORCERESTORE 4
#define CKBITMAPDATA_CLAMPUPTODATE 8
#define CKBITMAPDATA_CUBEMAP 16
#define CKBITMAPDATA_FREEVIDEOMEMORY 32
#define CKBITMAPDATA_DYNAMIC 64
#define CKBITMAPDATA_VOLUMEMAP 128
#define CKBITMAPDATA_CONDITIONALNONPOW2 256

class CKMovieReader;

class CKBitmapSlot {
public:
	DWORD* m_DataBuffer;
	XString m_FileName;

public:
	CKBitmapSlot() {
		m_DataBuffer = NULL;
	}

	void Allocate(int Width, int Height, int iBpp) {
		Flush();
		m_DataBuffer = (DWORD*) VxNewAligned(Width * Height * iBpp / 8, 16);
	}

	void Free() {
		Flush();
		m_FileName = "";
	}

	void Resize(VxImageDescEx& Src, VxImageDescEx& Dst) {
		DWORD* NewBuffer = (DWORD*)VxNewAligned(Dst.Width * Dst.Height * sizeof(DWORD), 16);
		if (m_DataBuffer) {
			Src.Image = (BYTE*)m_DataBuffer;
			Dst.Image = (BYTE*)NewBuffer;
			VxResizeImage32(Src, Dst);
			Flush();
		}
		else {
			DWORD* ptr = NewBuffer;
			DWORD size = Dst.Width * Dst.Height;
			for (DWORD i = 0; i < size; i++, ptr++) *ptr = 0xFF000000;
		}
		m_DataBuffer = NewBuffer;
	}

	void Flush() {
		if (VxIsAllocatedByNewAligned(m_DataBuffer, 16))
			VxDeleteAligned(m_DataBuffer);
		else delete[] m_DataBuffer;
		m_DataBuffer = NULL;
	}

	~CKBitmapSlot() {
		Flush();
	}
};

class CKMovieInfo {
public:
	XString					m_MovieFileName;
	CKMovieReader* m_MovieReader;
	int						m_MovieCurrentSlot;
};

class BML_EXPORT CKBitmapData {
public:
	CKBOOL CreateImage(int Width, int Height, int BPP = 32, int Slot = 0, void* ImagePointer = NULL);
	CKBOOL SaveImage(CKSTRING Name, int Slot = 0, CKBOOL CKUseFormat = FALSE);
	CKBOOL SaveImageAlpha(CKSTRING Name, int Slot = 0);
	CKSTRING GetMovieFileName();
	CKMovieReader* GetMovieReader();
	CKBYTE* LockSurfacePtr(int Slot = -1);
	CKBOOL ReleaseSurfacePtr(int Slot = -1);
	CKSTRING GetSlotFileName(int Slot);
	CKBOOL SetSlotFileName(int Slot, CKSTRING Filename);
	int GetWidth();
	int GetHeight();
	CKBOOL GetImageDesc(VxImageDescEx& oDesc);
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
	CK_BITMAP_SAVEOPTIONS GetSaveOptions();
	void SetSystemCaching(CK_BITMAP_SYSTEMCACHING iOptions);
	CK_BITMAP_SYSTEMCACHING GetSystemCaching();
	void SetSaveOptions(CK_BITMAP_SAVEOPTIONS Options);
	CKBitmapProperties* GetSaveFormat();
	void SetSaveFormat(CKBitmapProperties* format);
	void SetPickThreshold(int pt);
	int GetPickThreshold();
	void SetCubeMap(CKBOOL CubeMap);
	CKBOOL IsCubeMap();
	void SetVolumeMap(CKBOOL VolumeMap);
	CKBOOL IsVolumeMap();
	CKBOOL HasOriginalFile();
	CKBOOL ResizeImages(int Width, int Height);
	void SetDynamicHint(CKBOOL Dynamic);
	CKBOOL GetDynamicHint();
	void AuthorizeConditionalNonPow2(CKBOOL iAuthorize);
	CKBOOL IsConditionalNonPow2Authorized();

protected:
	CKBitmapData() {};
	~CKBitmapData() {};
};
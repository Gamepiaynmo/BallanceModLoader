#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

#undef DrawText

struct VxDriverDesc
{
	char DriverDesc[0x200];			// Driver Description
	char DriverName[0x200];			// Driver Name
	BOOL IsHardware;			// Is Driver Hardware

	int DisplayModeCount;
	VxDisplayMode* DisplayModes;		// Fullscreen display modes supported ( see  VxDisplayMode)
	XSArray<VxImageDescEx> TextureFormats;		// Texture formats supported by the driver (see VxImageDescEx)

	Vx2DCapsDesc Caps2D;		// 2d Capabilities
	Vx3DCapsDesc Caps3D;		// 3d Capabilities	
};
typedef struct VxEffectDescription {
	VX_EFFECT				EffectIndex;		// Index of this effect ( when using CKRenderManager::AddEffect the return value is the index of the newly added effect) so this member is ignored.
	XString					Summary;			// A short name that will be used for enumeration creation (eg. "Bump Map")
	XString					Description;		// A longer description that will appear in the interface to explain the effect to the user...
	XString					DescImage;			// A image file that can be use to be displayed in the interface
	int						MaxTextureCount;	// Number of textures that can be set on the material (CKMaterial::SetTexture)
	int						NeededTextureCoordsCount;	// Number of texture coordinates that must be set on the mesh  for this effect to work (this is directly related to the number of channel you should set on the mesh that will use this effect)
	XString					Tex1Description;	// A short description for texture 1
	XString					Tex2Description;	// A short description for texture 2
	XString					Tex3Description;	// A short description for texture 3
	CK_EFFECTCALLBACK		SetCallback;		// A callback function that will be called to setup the effect if NULL the effect is likely to be hardcoded in render engine
	void* CallbackArg;		// Arguments that will be given to the callback function	
	CKGUID					ParameterType;
	XString					ParameterDescription;
	XString					ParameterDefaultValue;
	VxEffectDescription() :CallbackArg(NULL), SetCallback(NULL), MaxTextureCount(0), EffectIndex(VXEFFECT_NONE), ParameterType(0, 0) {}
} VxEffectDescription;

class BML_EXPORT CKRenderManager : public CKBaseManager {
public:
	int GetRenderDriverCount();
	VxDriverDesc* GetRenderDriverDescription(int Driver);
	void GetDesiredTexturesVideoFormat(VxImageDescEx& VideoFormat);
	void SetDesiredTexturesVideoFormat(VxImageDescEx& VideoFormat);
	CKRenderContext* GetRenderContext(int pos);
	CKRenderContext* GetRenderContextFromPoint(CKPOINT& pt);
	int GetRenderContextCount();
	void Process();
	void FlushTextures();
	CKRenderContext* CreateRenderContext(void* Window, int Driver = 0, CKRECT* rect = NULL, CKBOOL Fullscreen = FALSE, int Bpp = -1, int Zbpp = -1, int StencilBpp = -1, int RefreshRate = 0);
	CKERROR DestroyRenderContext(CKRenderContext* context);
	void RemoveRenderContext(CKRenderContext* context);
	CKVertexBuffer* CreateVertexBuffer();
	void DestroyVertexBuffer(CKVertexBuffer* VB);
	void SetRenderOptions(CKSTRING RenderOptionString, DWORD Value);
	const VxEffectDescription& GetEffectDescription(int EffectIndex);
	int GetEffectCount();
	int AddEffect(const VxEffectDescription& NewEffect);

	// ====================================================

	void DrawAABB(CKRenderContext* iRC, const VxBbox& iBox, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawNormal(CKRenderContext* iRC, const VxRay& iRay, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawPoint(CKRenderContext* iRC, const VxVector& iPoint, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawPlane(CKRenderContext* iRC, const VxPlane& iPlane, const VxVector& iPoint, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawFrustum(CKRenderContext* iRC, const VxFrustum& iFrustum, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawSphere(CKRenderContext* iRC, const VxSphere& iSphere, const CKDWORD iColor, const VxMatrix* iTransform = NULL, const int iSubdivisions = 32);
	void DrawParabolic(CKRenderContext* iRC, const VxVector& iStartPos, const VxVector& iSpeed, const VxVector& iAcceleration, float iDrawingTime, const int iSubdivisions, const CKDWORD iColor, const VxMatrix* iTransform = NULL);
	void DrawPoint2D(CKRenderContext* iRC, const Vx2DVector& iPoint, const CKDWORD iColor);
	void DrawRectangle(CKRenderContext* iRC, const VxRect& iRect, const CKDWORD iColor);
	void DrawFillRectangle(CKRenderContext* iRC, const VxRect& iRect, const CKDWORD iColor);
	void DrawText(CKRenderContext* iRC, const Vx2DVector& iPoint, const char* iText, const CKDWORD iColor);
	void RegisterAABB(const VxBbox& iBox, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterNormal(const VxRay& iRay, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterPoint(const VxVector& iPoint, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterPlane(const VxPlane& iPlane, const VxVector& iPoint, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterFrustum(const VxFrustum& iFrustum, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterSphere(const VxSphere& iSphere, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL, const int iSubdivisions = 32);
	void RegisterParabolic(const VxVector& iStartPos, const VxVector& iSpeed, const VxVector& iAcceleration, float iDrawingTime, const int iSubdivisions, const CKDWORD iColor, float iRemainingTime = 0.0f, const VxMatrix* iTransform = NULL);
	void RegisterPoint2D(const Vx2DVector& iPoint, const CKDWORD iColor, float iRemainingTime = 0.0f);
	void RegisterRectangle(const VxRect& iRect, const CKDWORD iColor, float iRemainingTime = 0.0f);
	void RegisterFillRectangle(const VxRect& iRect, const CKDWORD iColor, float iRemainingTime = 0.0f);
	void RegisterText(const char* iText, const CKDWORD iColor, float iRemainingTime = 0.0f);

protected:
	CKRenderManager() {};
	~CKRenderManager() {};
};
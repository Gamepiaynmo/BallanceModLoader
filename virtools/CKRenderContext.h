#pragma once

#include "CKDef.h"
#include "CKObject.h"
#include "CK3dEntity.h"
#include "CKScene.h"

enum CK_STEREO_MODE {
    CK_STEREO_DEFAULT,
    CK_STEREO_LEFT,
    CK_STEREO_RIGHT,
};

typedef enum CKRST_DPFLAGS {
    CKRST_DP_TRANSFORM = 0x00000001UL,
    CKRST_DP_LIGHT = 0x00000002UL,
    CKRST_DP_DOCLIP = 0x00000004UL,
    CKRST_DP_DIFFUSE = 0x00000010UL,
    CKRST_DP_SPECULAR = 0x00000020UL,
    CKRST_DP_TANSPACE = 0x00000040UL,
    CKRST_DP_STAGESMASK = 0x0001FE00UL,
    CKRST_DP_STAGES0 = 0x00000200UL,
    CKRST_DP_STAGES1 = 0x00000400UL,
    CKRST_DP_STAGES2 = 0x00000800UL,
    CKRST_DP_STAGES3 = 0x00001000UL,
    CKRST_DP_STAGES4 = 0x00002000UL,
    CKRST_DP_STAGES5 = 0x00004000UL,
    CKRST_DP_STAGES6 = 0x00008000UL,
    CKRST_DP_STAGES7 = 0x00010000UL,

    CKRST_DP_WEIGHTMASK = 0x01F00000UL,
    CKRST_DP_WEIGHTS1 = 0x00100000UL,
    CKRST_DP_WEIGHTS2 = 0x00200000UL,
    CKRST_DP_WEIGHTS3 = 0x00400000UL,
    CKRST_DP_WEIGHTS4 = 0x00800000UL,
    CKRST_DP_WEIGHTS5 = 0x01000000UL,
    CKRST_DP_MATRIXPAL = 0x02000000UL,

    CKRST_DP_VBUFFER = 0x10000000UL,
    CKRST_DP_TRANSFORMW = 0x20000000UL,

    CKRST_DP_TR_CL_VNT = 0x00000207UL,
    CKRST_DP_TR_CL_VCST = 0x00000235UL,
    CKRST_DP_TR_CL_VCT = 0x00000215UL,
    CKRST_DP_TR_CL_VCS = 0x00000035UL,
    CKRST_DP_TR_CL_VC = 0x00000015UL,
    CKRST_DP_TR_CL_V = 0x00000005U,

    CKRST_DP_CL_VCST = 0x00000234UL,
    CKRST_DP_CL_VCT = 0x00000214UL,
    CKRST_DP_CL_VC = 0x00000014UL,
    CKRST_DP_CL_V = 0x00000004UL,

    CKRST_DP_TR_VNT = 0x00000203UL,
    CKRST_DP_TR_VCST = 0x00000231UL,
    CKRST_DP_TR_VCT = 0x00000211UL,
    CKRST_DP_TR_VCS = 0x00000031UL,
    CKRST_DP_TR_VC = 0x00000011UL,
    CKRST_DP_TR_V = 0x00000001UL,

    CKRST_DP_V = 0x00000000UL,
    CKRST_DP_VC = 0x00000010UL,
    CKRST_DP_VCT = 0x00000210UL,
    CKRST_DP_VCST = 0x00000230UL
} CKRST_DPFLAGS;

#define CKRST_MAX_STAGES 8

class VxUV
{
public:
    float u;
    float v;
public:
    VxUV(float _u = 0, float _v = 0) :u(_u), v(_v) {}

    void Set(float _u, float _v) {
        u = _u;
        v = _v;
    }

    VxUV& operator += (const VxUV& uv) { u += uv.u; v += uv.v; return *this; }
    VxUV& operator -= (const VxUV& uv) { u -= uv.u; v -= uv.v; return *this; }
    VxUV& operator *= (float s) { u *= s; v *= s; return *this; }
    VxUV& operator /= (float s) { u /= s; v /= s; return *this; }

    friend VxUV operator + (const VxUV& uv) { return uv; }
    friend VxUV operator - (const VxUV& uv) { return VxUV(-uv.u, -uv.v); }

    friend VxUV operator + (const VxUV& v1, const VxUV& v2) { return VxUV(v1.u + v2.u, v1.v + v2.v); }
    friend VxUV operator - (const VxUV& v1, const VxUV& v2) { return VxUV(v1.u - v2.u, v1.v - v2.v); }

    friend VxUV operator * (const VxUV& uv, float s) { return VxUV(uv.u * s, uv.v * s); }
    friend VxUV operator * (float s, const VxUV& uv) { return VxUV(uv.u * s, uv.v * s); }
    friend VxUV operator / (const VxUV& uv, float s) { return VxUV(uv.u / s, uv.v / s); }
};

struct VxDrawPrimitiveDataSimple {
    int				VertexCount;
    unsigned int	Flags;
    XPtrStrided<VxVector4>	Positions;
    XPtrStrided<VxVector>	Normals;
    XPtrStrided<DWORD>		Colors;
    XPtrStrided<DWORD>		SpecularColors;
    XPtrStrided<VxUV>		TexCoord;
};

struct VxDrawPrimitiveData : public VxDrawPrimitiveDataSimple
{
    XPtrStrided<VxUV>		TexCoords[CKRST_MAX_STAGES - 1];
    XPtrStrided<void*>		Weights;
    XPtrStrided<DWORD>		MatIndex;
};

typedef void (*CK_RENDERCALLBACK)(CKRenderContext* context, void* Argument);

typedef struct VxTransformData {
    void* InVertices;
    unsigned int InStride;
    void* OutVertices;
    unsigned int  OutStride;
    void* ScreenVertices;
    unsigned int  ScreenStride;
    unsigned int* ClipFlags;
    CKRECT m_2dExtents;
    unsigned int  m_Offscreen;
} VxTransformData;

typedef enum VXRENDERSTATETYPE {
    VXRENDERSTATE_ANTIALIAS = 2,
    VXRENDERSTATE_TEXTUREPERSPECTIVE = 4,
    VXRENDERSTATE_ZENABLE = 7,
    VXRENDERSTATE_FILLMODE = 8,
    VXRENDERSTATE_SHADEMODE = 9,
    VXRENDERSTATE_LINEPATTERN = 10,
    VXRENDERSTATE_ZWRITEENABLE = 14,
    VXRENDERSTATE_ALPHATESTENABLE = 15,
    VXRENDERSTATE_SRCBLEND = 19,
    VXRENDERSTATE_DESTBLEND = 20,
    VXRENDERSTATE_CULLMODE = 22,
    VXRENDERSTATE_ZFUNC = 23,
    VXRENDERSTATE_ALPHAREF = 24,
    VXRENDERSTATE_ALPHAFUNC = 25,
    VXRENDERSTATE_DITHERENABLE = 26,
    VXRENDERSTATE_ALPHABLENDENABLE = 27,
    VXRENDERSTATE_FOGENABLE = 28,
    VXRENDERSTATE_SPECULARENABLE = 29,
    VXRENDERSTATE_FOGCOLOR = 34,
    VXRENDERSTATE_FOGPIXELMODE = 35,
    VXRENDERSTATE_FOGSTART = 36,
    VXRENDERSTATE_FOGEND = 37,
    VXRENDERSTATE_FOGDENSITY = 38,
    VXRENDERSTATE_EDGEANTIALIAS = 40,
    VXRENDERSTATE_ZBIAS = 47,
    VXRENDERSTATE_RANGEFOGENABLE = 48,
    VXRENDERSTATE_STENCILENABLE = 52,
    VXRENDERSTATE_STENCILFAIL = 53,
    VXRENDERSTATE_STENCILZFAIL = 54,
    VXRENDERSTATE_STENCILPASS = 55,
    VXRENDERSTATE_STENCILFUNC = 56,
    VXRENDERSTATE_STENCILREF = 57,
    VXRENDERSTATE_STENCILMASK = 58,
    VXRENDERSTATE_STENCILWRITEMASK = 59,
    VXRENDERSTATE_TEXTUREFACTOR = 60,
    VXRENDERSTATE_WRAP0 = 128,
    VXRENDERSTATE_WRAP1 = 129,
    VXRENDERSTATE_WRAP2 = 130,
    VXRENDERSTATE_WRAP3 = 131,
    VXRENDERSTATE_WRAP4 = 132,
    VXRENDERSTATE_WRAP5 = 133,
    VXRENDERSTATE_WRAP6 = 134,
    VXRENDERSTATE_WRAP7 = 135,
    VXRENDERSTATE_CLIPPING = 136,
    VXRENDERSTATE_LIGHTING = 137,
    VXRENDERSTATE_AMBIENT = 139,
    VXRENDERSTATE_FOGVERTEXMODE = 140,
    VXRENDERSTATE_COLORVERTEX = 141,
    VXRENDERSTATE_LOCALVIEWER = 142,
    VXRENDERSTATE_NORMALIZENORMALS = 143,
    VXRENDERSTATE_DIFFUSEFROMVERTEX = 145,
    VXRENDERSTATE_SPECULARFROMVERTEX = 146,
    VXRENDERSTATE_AMBIENTFROMVERTEX = 147,
    VXRENDERSTATE_EMISSIVEFROMVERTEX = 148,

    VXRENDERSTATE_VERTEXBLEND = 151,
    VXRENDERSTATE_SOFTWAREVPROCESSING = 153,

    VXRENDERSTATE_POINTSIZE = 154,
    VXRENDERSTATE_POINTSIZE_MIN = 155,
    VXRENDERSTATE_POINTSIZE_MAX = 166,
    VXRENDERSTATE_POINTSPRITEENABLE = 156,

    VXRENDERSTATE_POINTSCALEENABLE = 157,

    VXRENDERSTATE_POINTSCALE_A = 158,
    VXRENDERSTATE_POINTSCALE_B = 159,
    VXRENDERSTATE_POINTSCALE_C = 160,

    VXRENDERSTATE_CLIPPLANEENABLE = 152,
    VXRENDERSTATE_INDEXVBLENDENABLE = 167,
    VXRENDERSTATE_BLENDOP = 171,

    VXRENDERSTATE_LOCKMATERIALSTATES = 252,
    VXRENDERSTATE_TEXTURETARGET = 253,
    VXRENDERSTATE_INVERSEWINDING = 254,
    VXRENDERSTATE_MAXSTATE = 256,
    VXRENDERSTATE_FORCE_DWORD = 0x7fffffff
} VXRENDERSTATETYPE;

typedef enum CKRST_TEXTURESTAGESTATETYPE {
    CKRST_TSS_OP = 1UL,
    CKRST_TSS_ARG1 = 2UL,
    CKRST_TSS_ARG2 = 3UL,
    CKRST_TSS_AOP = 4UL,
    CKRST_TSS_AARG1 = 5UL,
    CKRST_TSS_AARG2 = 6UL,
    CKRST_TSS_BUMPENVMAT00 = 7UL,
    CKRST_TSS_BUMPENVMAT01 = 8UL,
    CKRST_TSS_BUMPENVMAT10 = 9UL,
    CKRST_TSS_BUMPENVMAT11 = 10UL,
    CKRST_TSS_TEXCOORDINDEX = 11UL,
    CKRST_TSS_ADDRESS = 12UL,
    CKRST_TSS_ADDRESSU = 13UL,
    CKRST_TSS_ADDRESSV = 14UL,
    CKRST_TSS_BORDERCOLOR = 15UL,
    CKRST_TSS_MAGFILTER = 16UL,
    CKRST_TSS_MINFILTER = 17UL,

    CKRST_TSS_MIPMAPLODBIAS = 19UL,
    CKRST_TSS_MAXMIPMLEVEL = 20UL,
    CKRST_TSS_MAXANISOTROPY = 21UL,
    CKRST_TSS_BUMPENVLSCALE = 22UL,
    CKRST_TSS_BUMPENVLOFFSET = 23UL,

    CKRST_TSS_TEXTURETRANSFORMFLAGS = 24UL,

    CKRST_TSS_ADDRESW = 25UL,
    CKRST_TSS_COLORARG0 = 26UL,
    CKRST_TSS_ALPHAARG0 = 27UL,
    CKRST_TSS_RESULTARG0 = 28UL,

    CKRST_TSS_TEXTUREMAPBLEND = 39UL,
    CKRST_TSS_STAGEBLEND = 40UL,

    CKRST_TSS_MAXSTATE = 41UL
} CKRST_TEXTURESTAGESTATETYPE;

class CKRasterizerContext;

typedef enum VXPRIMITIVETYPE {
    VX_POINTLIST = 1UL,
    VX_LINELIST = 2UL,
    VX_LINESTRIP = 3UL,
    VX_TRIANGLELIST = 4UL,
    VX_TRIANGLESTRIP = 5UL,
    VX_TRIANGLEFAN = 6UL
} VXPRIMITIVETYPE;

typedef enum VXBUFFER_TYPE {
    VXBUFFER_BACKBUFFER = 0x00000001UL,
    VXBUFFER_ZBUFFER = 0x00000002UL,
    VXBUFFER_STENCILBUFFER = 0x00000004UL
} VXBUFFER_TYPE;

typedef struct VxDirectXData {
    void* DDBackBuffer;
    void* DDPrimaryBuffer;
    void* DDZBuffer;
    void* DirectDraw;
    void* Direct3D;
    void* DDClipper;
    void* D3DDevice;
    void* D3DViewport;
    DWORD			DxVersion;
} VxDirectXData;

enum CK_OVERRIDE_RENDERING {
    CK_OVERRIDE_NONE,
    CK_OVERRIDE_MATERIAL,
    CK_OVERRIDE_USECURRENT,
    CK_OVERRIDE_PASS,
};

class CKShader;

class BML_EXPORT CKRenderContext : public CKObject {
public:
    void AddObject(CKRenderObject* obj);
    void AddObjectWithHierarchy(CKRenderObject* obj);
    void RemoveObject(CKRenderObject* obj);
    CKBOOL IsObjectAttached(CKRenderObject* obj);
    const XObjectArray& Compute3dRootObjects();
    const XObjectArray& Compute2dRootObjects();
    CK2dEntity* Get2dRoot(CKBOOL background);
    void DetachAll();
    void ForceCameraSettingsUpdate();
    void PrepareCameras(CK_RENDER_FLAGS Flags = CK_RENDER_USECURRENTSETTINGS);
    CKERROR Clear(CK_RENDER_FLAGS Flags = CK_RENDER_USECURRENTSETTINGS, CKDWORD Stencil = 0);
    CKERROR DrawScene(CK_RENDER_FLAGS Flags = CK_RENDER_USECURRENTSETTINGS);
    CKERROR BackToFront(CK_RENDER_FLAGS Flags = CK_RENDER_USECURRENTSETTINGS);
    CKERROR Render(CK_RENDER_FLAGS Flags = CK_RENDER_USECURRENTSETTINGS);
    void AddPreRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary = FALSE);
    void RemovePreRenderCallBack(CK_RENDERCALLBACK Function, void* Argument);
    void AddPostRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary = FALSE, CKBOOL BeforeTransparent = FALSE);
    void RemovePostRenderCallBack(CK_RENDERCALLBACK Function, void* Argument);
    void AddPostSpriteRenderCallBack(CK_RENDERCALLBACK Function, void* Argument, CKBOOL Temporary = FALSE);
    void RemovePostSpriteRenderCallBack(CK_RENDERCALLBACK Function, void* Argument);
    VxDrawPrimitiveData* GetDrawPrimitiveStructure(CKRST_DPFLAGS Flags, int VertexCount);
    CKWORD* GetDrawPrimitiveIndices(int IndicesCount);
    void Transform(VxVector* Dest, VxVector* Src, CK3dEntity* Ref = NULL);
    void TransformVertices(int VertexCount, VxTransformData* data, CK3dEntity* Ref = NULL);
    CKERROR GoFullScreen(int Width = 640, int Height = 480, int Bpp = -1, int Driver = 0, int RefreshRate = 0);
    CKERROR StopFullScreen();
    CKBOOL IsFullScreen();
    int GetDriverIndex();
    CKBOOL ChangeDriver(int NewDriver);
    WIN_HANDLE GetWindowHandle();
    void ScreenToClient(Vx2DVector* ioPoint);
    void ClientToScreen(Vx2DVector* ioPoint);
    CKERROR SetWindowRect(VxRect& rect, CKDWORD Flags = 0);
    void GetWindowRect(VxRect& rect, CKBOOL ScreenRelative = FALSE);
    int GetHeight();
    int GetWidth();
    CKERROR Resize(int PosX = 0, int PosY = 0, int SizeX = 0, int SizeY = 0, CKDWORD Flags = 0);
    void SetViewRect(VxRect& rect);
    void GetViewRect(VxRect& rect);
    VX_PIXELFORMAT GetPixelFormat(int* Bpp = NULL, int* Zbpp = NULL, int* StencilBpp = NULL);
    void SetState(VXRENDERSTATETYPE State, CKDWORD Value);
    CKDWORD GetState(VXRENDERSTATETYPE State);
    CKBOOL SetTexture(CKTexture* tex, CKBOOL Clamped = 0, int Stage = 0);
    CKBOOL SetTextureStageState(CKRST_TEXTURESTAGESTATETYPE State, CKDWORD Value, int Stage = 0);
    CKRasterizerContext* GetRasterizerContext();
    void SetClearBackground(CKBOOL ClearBack = TRUE);
    CKBOOL GetClearBackground();
    void SetClearZBuffer(CKBOOL ClearZ = TRUE);
    CKBOOL GetClearZBuffer();
    void GetGlobalRenderMode(VxShadeType* Shading, CKBOOL* Texture, CKBOOL* Wireframe);
    void SetGlobalRenderMode(VxShadeType Shading = GouraudShading, CKBOOL Texture = TRUE, CKBOOL Wireframe = FALSE);
    void SetCurrentRenderOptions(CKDWORD flags);
    CKDWORD GetCurrentRenderOptions();
    void ChangeCurrentRenderOptions(CKDWORD Add, CKDWORD Remove);
    void SetCurrentExtents(VxRect& extents);
    void GetCurrentExtents(VxRect& extents);
    void SetAmbientLight(float R, float G, float B);
    void SetAmbientLight(CKDWORD Color);
    CKDWORD GetAmbientLight();
    void SetFogMode(VXFOG_MODE Mode);
    void SetFogStart(float Start);
    void SetFogEnd(float End);
    void SetFogDensity(float Density);
    void SetFogColor(CKDWORD Color);
    VXFOG_MODE GetFogMode();
    float GetFogStart();
    float GetFogEnd();
    float GetFogDensity();
    CKDWORD GetFogColor();
    CKBOOL DrawPrimitive(VXPRIMITIVETYPE pType, CKWORD* indices, int indexcount, VxDrawPrimitiveData* data);
    void SetWorldTransformationMatrix(const VxMatrix& M);
    void SetProjectionTransformationMatrix(const VxMatrix& M);
    void SetViewTransformationMatrix(const VxMatrix& M);
    const VxMatrix& GetWorldTransformationMatrix();
    const VxMatrix& GetProjectionTransformationMatrix();
    const VxMatrix& GetViewTransformationMatrix();
    CKBOOL SetUserClipPlane(CKDWORD ClipPlaneIndex, const VxPlane& PlaneEquation);
    CKBOOL GetUserClipPlane(CKDWORD ClipPlaneIndex, VxPlane& PlaneEquation);
    CKRenderObject* Pick(int x, int y, VxIntersectionDesc* oRes, CKBOOL iIgnoreUnpickable = FALSE);
    CKERROR RectPick(const VxRect& r, XObjectPointerArray& oObjects, CKBOOL Intersect = TRUE);
    void AttachViewpointToCamera(CKCamera* cam);
    void DetachViewpointFromCamera();
    CKCamera* GetAttachedCamera();
    CK3dEntity* GetViewpoint();
    CKMaterial* GetBackgroundMaterial();
    void GetBoundingBox(VxBbox* BBox);
    void GetStats(VxStats* stats);
    void SetCurrentMaterial(CKMaterial* mat, BOOL Lit = TRUE);
    void Activate(CKBOOL active = TRUE);
    int DumpToMemory(const VxRect* iRect, VXBUFFER_TYPE buffer, VxImageDescEx& desc);
    int CopyToVideo(const VxRect* iRect, VXBUFFER_TYPE buffer, VxImageDescEx& desc);
    CKERROR DumpToFile(CKSTRING filename, const VxRect* rect, VXBUFFER_TYPE buffer);
    VxDirectXData* GetDirectXInfo();
    void WarnEnterThread();
    void WarnExitThread();
    CK2dEntity* Pick2D(const Vx2DVector& v);
    CKBOOL SetRenderTarget(CKTexture* texture = NULL, int CubeMapFace = 0);
    void AddRemoveSequence(CKBOOL Start);
    void SetTransparentMode(CKBOOL Trans);
    void AddDirtyRect(CKRECT* Rect);
    void RestoreScreenBackup();
    CKDWORD GetStencilFreeMask();
    void UsedStencilBits(CKDWORD stencilBits);
    int GetFirstFreeStencilBits();
    VxDrawPrimitiveData* LockCurrentVB(CKDWORD VertexCount);
    BOOL ReleaseCurrentVB();
    void SetTextureMatrix(const VxMatrix& M, int Stage = 0);
    void SetStereoParameters(float EyeSeparation, float FocalLength);
    void GetStereoParameters(float& EyeSeparation, float& FocalLength);
    void SetViewport(const VxRect& iRect);
    void ScreenToViewpoint(const Vx2DVector& i2DPosition, VxVector* o3DPosition, CKBOOL iScreen = TRUE);
    void SetOverriddenRendering(CK_OVERRIDE_RENDERING Or, CKMaterial* mat = NULL, const char* pass = NULL);
    void SetupLights();
    void SetValuesOfUsedAutomatics(CKShader& iFx, CKMaterial* iMat, CK3dEntity* iEnt);
    CKBOOL IsStereoRenderingLeftEye();
    void SetStereoRenderMode(CK_STEREO_MODE iMode);
    CKBOOL IsRenderingShaderBatch();
    float GetSurfacesVideoMemoryOccupation(int* NbTextures, int* NbSprites, float* TextureSize, float* SpriteSize);
    BOOL FlushPendingGPUCommands();

protected:
	CKRenderContext() {};
	~CKRenderContext() {};
};
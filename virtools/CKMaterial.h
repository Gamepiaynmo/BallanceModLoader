#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

class CKShader;
class CKMaterialShader;

typedef enum VXTEXTURE_BLENDMODE {
	VXTEXTUREBLEND_DECAL = 1UL,
	VXTEXTUREBLEND_MODULATE = 2UL,
	VXTEXTUREBLEND_DECALALPHA = 3UL,
	VXTEXTUREBLEND_MODULATEALPHA = 4UL,
	VXTEXTUREBLEND_DECALMASK = 5UL,
	VXTEXTUREBLEND_MODULATEMASK = 6UL,
	VXTEXTUREBLEND_COPY = 7UL,
	VXTEXTUREBLEND_ADD = 8UL,
	VXTEXTUREBLEND_DOTPRODUCT3 = 9UL,
	VXTEXTUREBLEND_MAX = 10UL,
	VXTEXTUREBLEND_MASK = 0xFUL
} VXTEXTURE_BLENDMODE;

typedef enum VXTEXTURE_FILTERMODE {
	VXTEXTUREFILTER_NEAREST = 1UL,
	VXTEXTUREFILTER_LINEAR = 2UL,
	VXTEXTUREFILTER_MIPNEAREST = 3UL,
	VXTEXTUREFILTER_MIPLINEAR = 4UL,
	VXTEXTUREFILTER_LINEARMIPNEAREST = 5UL,
	VXTEXTUREFILTER_LINEARMIPLINEAR = 6UL,
	VXTEXTUREFILTER_ANISOTROPIC = 7UL,
	VXTEXTUREFILTER_MASK = 0xFUL
} VXTEXTURE_FILTERMODE;

typedef enum VXBLEND_MODE {
	VXBLEND_ZERO = 1UL,
	VXBLEND_ONE = 2UL,
	VXBLEND_SRCCOLOR = 3UL,
	VXBLEND_INVSRCCOLOR = 4UL,
	VXBLEND_SRCALPHA = 5UL,
	VXBLEND_INVSRCALPHA = 6UL,
	VXBLEND_DESTALPHA = 7UL,
	VXBLEND_INVDESTALPHA = 8UL,
	VXBLEND_DESTCOLOR = 9UL,
	VXBLEND_INVDESTCOLOR = 10UL,
	VXBLEND_SRCALPHASAT = 11UL,
	VXBLEND_BOTHSRCALPHA = 12UL,
	VXBLEND_BOTHINVSRCALPHA = 13UL,
	VXBLEND_MASK = 0xFUL
} VXBLEND_MODE;

typedef enum VXTEXTURE_ADDRESSMODE {
	VXTEXTURE_ADDRESSWRAP = 1UL,
	VXTEXTURE_ADDRESSMIRROR = 2UL,
	VXTEXTURE_ADDRESSCLAMP = 3UL,
	VXTEXTURE_ADDRESSBORDER = 4UL,
	VXTEXTURE_ADDRESSMIRRORONCE = 5UL,
	VXTEXTURE_ADDRESSMASK = 0x7UL
} VXTEXTURE_ADDRESSMODE;

typedef enum VXFILL_MODE {
	VXFILL_POINT = 1UL,
	VXFILL_WIREFRAME = 2UL,
	VXFILL_SOLID = 3UL,
	VXFILL_MASK = 3UL
}VXFILL_MODE;

typedef enum VXSHADE_MODE {
	VXSHADE_FLAT = 1UL,
	VXSHADE_GOURAUD = 2UL,
	VXSHADE_PHONG = 3UL,
	VXSHADE_MASK = 3UL
} VXSHADE_MODE;

typedef enum VXCMPFUNC {
	VXCMP_NEVER = 1UL,
	VXCMP_LESS = 2UL,
	VXCMP_EQUAL = 3UL,
	VXCMP_LESSEQUAL = 4UL,
	VXCMP_GREATER = 5UL,
	VXCMP_NOTEQUAL = 6UL,
	VXCMP_GREATEREQUAL = 7UL,
	VXCMP_ALWAYS = 8UL,
	VXCMP_MASK = 0xFUL
} VXCMPFUNC;

class BML_EXPORT CKMaterial : public CKBeObject {
public:
	float GetPower();
	void SetPower(float Value);
	const VxColor& GetAmbient();
	void SetAmbient(const VxColor& Color);
	const VxColor& GetDiffuse();
	void SetDiffuse(const VxColor& Color);
	const VxColor& GetSpecular();
	void SetSpecular(const VxColor& Color);
	const VxColor& GetEmissive();
	void SetEmissive(const VxColor& Color);
	CKTexture* GetTexture(int TexIndex = 0);
	void SetTexture(CKTexture* Tex);
	void SetTextureBlendMode(VXTEXTURE_BLENDMODE BlendMode);
	VXTEXTURE_BLENDMODE GetTextureBlendMode();
	void SetTextureMinMode(VXTEXTURE_FILTERMODE FilterMode);
	VXTEXTURE_FILTERMODE GetTextureMinMode();
	void SetTextureMagMode(VXTEXTURE_FILTERMODE FilterMode);
	VXTEXTURE_FILTERMODE GetTextureMagMode();
	void SetTextureAddressMode(VXTEXTURE_ADDRESSMODE Mode);
	VXTEXTURE_ADDRESSMODE GetTextureAddressMode();
	void SetTextureBorderColor(CKDWORD Color);
	CKDWORD GetTextureBorderColor();
	void SetSourceBlend(VXBLEND_MODE BlendMode);
	void SetDestBlend(VXBLEND_MODE BlendMode);
	VXBLEND_MODE GetSourceBlend();
	VXBLEND_MODE GetDestBlend();
	CKBOOL IsTwoSided();
	void SetTwoSided(CKBOOL TwoSided);
	CKBOOL ZWriteEnabled();
	void EnableZWrite(CKBOOL ZWrite = TRUE);
	CKBOOL AlphaBlendEnabled();
	void EnableAlphaBlend(CKBOOL Blend = TRUE);
	VXCMPFUNC GetZFunc();
	void SetZFunc(VXCMPFUNC ZFunc = VXCMP_LESSEQUAL);
	CKBOOL PerspectiveCorrectionEnabled();
	void EnablePerpectiveCorrection(CKBOOL Perspective = TRUE);
	void SetFillMode(VXFILL_MODE FillMode);
	VXFILL_MODE GetFillMode();
	void SetShadeMode(VXSHADE_MODE ShadeMode);
	VXSHADE_MODE GetShadeMode();
	CKBOOL SetAsCurrent(CKRenderContext*, BOOL Lit = TRUE, int TextureStage = 0);
	CKBOOL IsAlphaTransparent();
	CKBOOL AlphaTestEnabled();
	void EnableAlphaTest(CKBOOL Enable = TRUE);
	VXCMPFUNC GetAlphaFunc();
	void SetAlphaFunc(VXCMPFUNC AlphaFunc = VXCMP_ALWAYS);
	CKBYTE GetAlphaRef();
	void SetAlphaRef(CKBYTE AlphaRef = 0);
	void SetEffect(VX_EFFECT Effect);
	VX_EFFECT GetEffect();
	void SetTexture(int TexIndex, CKTexture* Tex);
	CKParameter* GetEffectParameter();
	CKMaterialShader* GetMaterialShader(bool LinkParams = FALSE);
	void SetShader(CKShader* shader);
	void SetShaderByName(char* iName);
	void SetShaderParamValue(char* iParamName, void* iBuffer);
	void SetShaderParamObject(char* iParamName, CKObject* iObj);
	void GetShaderParamValue(char* iParamName, void* oBuffer);
	CKObject* GetShaderParamObject(char* iParamName);
	void SetMaterialShader(CKMaterialShader* shader);
	void DestroyCKMaterialShader(CKMaterialShader*& mfx);

protected:
	CKMaterial() {};
	~CKMaterial() {};
};
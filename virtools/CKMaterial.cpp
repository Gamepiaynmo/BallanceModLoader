#include "CKMaterial.h"

NAKED float CKMaterial::GetPower() {
	JUMPV(0x54);
}

NAKED void CKMaterial::SetPower(float Value) {
	JUMPV(0x58);
}

NAKED const VxColor& CKMaterial::GetAmbient() {
	JUMPV(0x5c);
}

NAKED void CKMaterial::SetAmbient(const VxColor& Color) {
	JUMPV(0x60);
}

NAKED const VxColor& CKMaterial::GetDiffuse() {
	JUMPV(0x64);
}

NAKED void CKMaterial::SetDiffuse(const VxColor& Color) {
	JUMPV(0x68);
}

NAKED const VxColor& CKMaterial::GetSpecular() {
	JUMPV(0x6c);
}

NAKED void CKMaterial::SetSpecular(const VxColor& Color) {
	JUMPV(0x70);
}

NAKED const VxColor& CKMaterial::GetEmissive() {
	JUMPV(0x74);
}

NAKED void CKMaterial::SetEmissive(const VxColor& Color) {
	JUMPV(0x78);
}

NAKED CKTexture* CKMaterial::GetTexture(int TexIndex) {
	JUMPV(0x7c);
}

NAKED void CKMaterial::SetTexture(CKTexture* Tex) {
	JUMPV(0x84);
}

NAKED void CKMaterial::SetTextureBlendMode(VXTEXTURE_BLENDMODE BlendMode) {
	JUMPV(0x88);
}

NAKED VXTEXTURE_BLENDMODE CKMaterial::GetTextureBlendMode() {
	JUMPV(0x8c);
}

NAKED void CKMaterial::SetTextureMinMode(VXTEXTURE_FILTERMODE FilterMode) {
	JUMPV(0x90);
}

NAKED VXTEXTURE_FILTERMODE CKMaterial::GetTextureMinMode() {
	JUMPV(0x94);
}

NAKED void CKMaterial::SetTextureMagMode(VXTEXTURE_FILTERMODE FilterMode) {
	JUMPV(0x98);
}

NAKED VXTEXTURE_FILTERMODE CKMaterial::GetTextureMagMode() {
	JUMPV(0x9c);
}

NAKED void CKMaterial::SetTextureAddressMode(VXTEXTURE_ADDRESSMODE Mode) {
	JUMPV(0xa0);
}

NAKED VXTEXTURE_ADDRESSMODE CKMaterial::GetTextureAddressMode() {
	JUMPV(0xa4);
}

NAKED void CKMaterial::SetTextureBorderColor(CKDWORD Color) {
	JUMPV(0xa8);
}

NAKED CKDWORD CKMaterial::GetTextureBorderColor() {
	JUMPV(0xac);
}

NAKED void CKMaterial::SetSourceBlend(VXBLEND_MODE BlendMode) {
	JUMPV(0xb0);
}

NAKED void CKMaterial::SetDestBlend(VXBLEND_MODE BlendMode) {
	JUMPV(0xb4);
}

NAKED VXBLEND_MODE CKMaterial::GetSourceBlend() {
	JUMPV(0xb8);
}

NAKED VXBLEND_MODE CKMaterial::GetDestBlend() {
	JUMPV(0xbc);
}

NAKED CKBOOL CKMaterial::IsTwoSided() {
	JUMPV(0xc0);
}

NAKED void CKMaterial::SetTwoSided(CKBOOL TwoSided) {
	JUMPV(0xc4);
}

NAKED CKBOOL CKMaterial::ZWriteEnabled() {
	JUMPV(0xc8);
}

NAKED void CKMaterial::EnableZWrite(CKBOOL ZWrite) {
	JUMPV(0xcc);
}

NAKED CKBOOL CKMaterial::AlphaBlendEnabled() {
	JUMPV(0xd0);
}

NAKED void CKMaterial::EnableAlphaBlend(CKBOOL Blend) {
	JUMPV(0xd4);
}

NAKED VXCMPFUNC CKMaterial::GetZFunc() {
	JUMPV(0xd8);
}

NAKED void CKMaterial::SetZFunc(VXCMPFUNC ZFunc) {
	JUMPV(0xdc);
}

NAKED CKBOOL CKMaterial::PerspectiveCorrectionEnabled() {
	JUMPV(0xe0);
}

NAKED void CKMaterial::EnablePerpectiveCorrection(CKBOOL Perspective) {
	JUMPV(0xe4);
}

NAKED void CKMaterial::SetFillMode(VXFILL_MODE FillMode) {
	JUMPV(0xe8);
}

NAKED VXFILL_MODE CKMaterial::GetFillMode() {
	JUMPV(0xec);
}

NAKED void CKMaterial::SetShadeMode(VXSHADE_MODE ShadeMode) {
	JUMPV(0xf0);
}

NAKED VXSHADE_MODE CKMaterial::GetShadeMode() {
	JUMPV(0xf4);
}

NAKED CKBOOL CKMaterial::SetAsCurrent(CKRenderContext*, BOOL Lit, int TextureStage) {
	JUMPV(0xf8);
}

NAKED CKBOOL CKMaterial::IsAlphaTransparent() {
	JUMPV(0xfc);
}

NAKED CKBOOL CKMaterial::AlphaTestEnabled() {
	JUMPV(0x100);
}

NAKED void CKMaterial::EnableAlphaTest(CKBOOL Enable) {
	JUMPV(0x104);
}

NAKED VXCMPFUNC CKMaterial::GetAlphaFunc() {
	JUMPV(0x108);
}

NAKED void CKMaterial::SetAlphaFunc(VXCMPFUNC AlphaFunc) {
	JUMPV(0x10c);
}

NAKED CKBYTE CKMaterial::GetAlphaRef() {
	JUMPV(0x110);
}

NAKED void CKMaterial::SetAlphaRef(CKBYTE AlphaRef) {
	JUMPV(0x114);
}

NAKED void CKMaterial::SetEffect(VX_EFFECT Effect) {
	JUMPV(0x118);
}

NAKED VX_EFFECT CKMaterial::GetEffect() {
	JUMPV(0x11c);
}

NAKED void CKMaterial::SetTexture(int TexIndex, CKTexture* Tex) {
	JUMPV(0x120);
}

NAKED CKParameter* CKMaterial::GetEffectParameter() {
	JUMPV(0x124);
}

NAKED CKMaterialShader* CKMaterial::GetMaterialShader(bool LinkParams) {
	JUMPV(0x128);
}

NAKED void CKMaterial::SetShader(CKShader* shader) {
	JUMPV(0x12c);
}

NAKED void CKMaterial::SetShaderByName(char* iName) {
	JUMPV(0x130);
}

NAKED void CKMaterial::SetShaderParamValue(char* iParamName, void* iBuffer) {
	JUMPV(0x134);
}

NAKED void CKMaterial::SetShaderParamObject(char* iParamName, CKObject* iObj) {
	JUMPV(0x138);
}

NAKED void CKMaterial::GetShaderParamValue(char* iParamName, void* oBuffer) {
	JUMPV(0x13c);
}

NAKED CKObject* CKMaterial::GetShaderParamObject(char* iParamName) {
	JUMPV(0x140);
}

NAKED void CKMaterial::SetMaterialShader(CKMaterialShader* shader) {
	JUMPV(0x144);
}

NAKED void CKMaterial::DestroyCKMaterialShader(CKMaterialShader*& mfx) {
	JUMPV(0x148);
}

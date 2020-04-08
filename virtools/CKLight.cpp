#include "CKLight.h"

NAKED void CKLight::SetColor(const VxColor& c) {
	JUMPV(0x1d4);
}

NAKED const VxColor& CKLight::GetColor() {
	JUMPV(0x1d8);
}

NAKED void CKLight::SetConstantAttenuation(float Value) {
	JUMPV(0x1dc);
}

NAKED void CKLight::SetLinearAttenuation(float Value) {
	JUMPV(0x1e0);
}

NAKED void CKLight::SetQuadraticAttenuation(float Value) {
	JUMPV(0x1e4);
}

NAKED float CKLight::GetConstantAttenuation() {
	JUMPV(0x1e8);
}

NAKED float CKLight::GetLinearAttenuation() {
	JUMPV(0x1ec);
}

NAKED float CKLight::GetQuadraticAttenuation() {
	JUMPV(0x1f0);
}

NAKED VXLIGHT_TYPE CKLight::GetType() {
	JUMPV(0x1f4);
}

NAKED void CKLight::SetType(VXLIGHT_TYPE Type) {
	JUMPV(0x1f8);
}

NAKED float CKLight::GetRange() {
	JUMPV(0x1fc);
}

NAKED void CKLight::SetRange(float Value) {
	JUMPV(0x200);
}

NAKED float CKLight::GetHotSpot() {
	JUMPV(0x204);
}

NAKED float CKLight::GetFallOff() {
	JUMPV(0x208);
}

NAKED void CKLight::SetHotSpot(float Value) {
	JUMPV(0x20c);
}

NAKED void CKLight::SetFallOff(float Value) {
	JUMPV(0x210);
}

NAKED float CKLight::GetFallOffShape() {
	JUMPV(0x214);
}

NAKED void CKLight::SetFallOffShape(float Value) {
	JUMPV(0x218);
}

NAKED void CKLight::Active(CKBOOL Active) {
	JUMPV(0x21c);
}

NAKED CKBOOL CKLight::GetActivity() {
	JUMPV(0x220);
}

NAKED void CKLight::SetSpecularFlag(CKBOOL Specular) {
	JUMPV(0x224);
}

NAKED CKBOOL CKLight::GetSpecularFlag() {
	JUMPV(0x228);
}

NAKED CK3dEntity* CKLight::GetTarget() {
	JUMPV(0x22c);
}

NAKED void CKLight::SetTarget(CK3dEntity* target) {
	JUMPV(0x230);
}

NAKED float CKLight::GetLightPower() {
	JUMPV(0x234);
}

NAKED void CKLight::SetLightPower(float power) {
	JUMPV(0x238);
}

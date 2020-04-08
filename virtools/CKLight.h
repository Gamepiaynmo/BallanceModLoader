#pragma once

#include "CKDef.h"
#include "CK3dEntity.h"

typedef enum VXLIGHT_TYPE {
	VX_LIGHTPOINT = 1UL,
	VX_LIGHTSPOT = 2UL,
	VX_LIGHTDIREC = 3UL,
	VX_LIGHTPARA = 4UL
} VXLIGHT_TYPE;

class BML_EXPORT CKLight : public CK3dEntity {
public:
	void SetColor(const VxColor& c);
	const VxColor& GetColor();
	void SetConstantAttenuation(float Value);
	void SetLinearAttenuation(float Value);
	void SetQuadraticAttenuation(float Value);
	float GetConstantAttenuation();
	float GetLinearAttenuation();
	float GetQuadraticAttenuation();
	VXLIGHT_TYPE GetType();
	void SetType(VXLIGHT_TYPE Type);
	float GetRange();
	void SetRange(float Value);
	float GetHotSpot();
	float GetFallOff();
	void SetHotSpot(float Value);
	void SetFallOff(float Value);
	float GetFallOffShape();
	void SetFallOffShape(float Value);
	void Active(CKBOOL Active);
	CKBOOL GetActivity();
	void SetSpecularFlag(CKBOOL Specular);
	CKBOOL GetSpecularFlag();
	CK3dEntity* GetTarget();
	void SetTarget(CK3dEntity* target);
	float GetLightPower();
	void SetLightPower(float power = 1.0f);

protected:
	CKLight() {};
	~CKLight() {};
};

class BML_EXPORT CKTargetLight : public CKLight {
protected:
	CKTargetLight() {};
	~CKTargetLight() {};
};
#pragma once

#include "CKDef.h"

class BML_EXPORT CK2dCurvePoint {
public:
	CK2dCurve* GetCurve() const;
	float GetBias() const;
	void  SetBias(float b);
	float GetTension() const;
	void  SetTension(float t);
	float GetContinuity() const;
	void  SetContinuity(float c);
	CKBOOL IsLinear() const;
	void SetLinear(CKBOOL linear = FALSE);
	void UseTCB(CKBOOL use = TRUE);
	CKBOOL IsTCB() const;
	float GetLength() const;
	Vx2DVector& GetPosition();
	void SetPosition(const Vx2DVector& pos);
	Vx2DVector& GetInTangent();
	Vx2DVector& GetOutTangent();
	void SetInTangent(const Vx2DVector& in);
	void SetOutTangent(const Vx2DVector& out);
	void NotifyUpdate();
	void SetCurve(CK2dCurve* curve);
	void SetLength(float l);
	Vx2DVector& GetRCurvePos();
	void SetRCurvePos(Vx2DVector& v);
	void Read(CKStateChunk* chunk);

protected:
	CK2dCurvePoint() {};
	~CK2dCurvePoint() {};
};

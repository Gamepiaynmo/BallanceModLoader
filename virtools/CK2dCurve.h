#pragma once

#include "CKDef.h"
#include "CKObject.h"
#include "CK2dCurvePoint.h"

class BML_EXPORT CK2dCurve {
public:
	float GetLength();
	CKERROR GetPos(float step, Vx2DVector* pos);
	float GetY(float X);
	void DeleteControlPoint(CK2dCurvePoint* cpt);
	void AddControlPoint(const Vx2DVector& pos);
	int	GetControlPointCount();
	CK2dCurvePoint* GetControlPoint(int pos);
	void Update();
	CKStateChunk* Dump();
	CKERROR Read(CKStateChunk* chunk);
	void UpdatePointsAndTangents();
	int Rindex(int index);

protected:
	CK2dCurve() {};
	~CK2dCurve() {};

};

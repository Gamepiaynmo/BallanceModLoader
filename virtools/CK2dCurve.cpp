#include "CK2dCurve.h"

NAKED float CK2dCurve::GetLength() {
	JUMP(0x2403B12C);
}

NAKED CKERROR CK2dCurve::GetPos(float step, Vx2DVector* pos) {
	JUMP(0x24001DB9);
}

NAKED float CK2dCurve::GetY(float X) {
	JUMP(0x24001B36);
}

NAKED void CK2dCurve::DeleteControlPoint(CK2dCurvePoint* cpt) {
	JUMP(0x2403B234);
}

NAKED void CK2dCurve::AddControlPoint(const Vx2DVector& pos) {
	JUMP(0x24001AF5);
}

NAKED int CK2dCurve::GetControlPointCount() {
	JUMP(0x2403B27E);
}

NAKED CK2dCurvePoint* CK2dCurve::GetControlPoint(int pos) {
	JUMP(0x2403B28A);
}

NAKED void CK2dCurve::Update() {
	JUMP(0x24001084);
}

NAKED CKStateChunk* CK2dCurve::Dump() {
	JUMP(0x2400125A);
}

NAKED CKERROR CK2dCurve::Read(CKStateChunk* chunk) {
	JUMP(0x240013E4);
}

NAKED void CK2dCurve::UpdatePointsAndTangents() {
	JUMP(0x24001600);
}

NAKED int CK2dCurve::Rindex(int index) {
	JUMP(0x2403B296);
}

#include "CK2dCurvePoint.h"

NAKED CK2dCurve* CK2dCurvePoint::GetCurve() const {
	JUMP(0x2403B129);
}

NAKED float CK2dCurvePoint::GetBias() const {
	JUMP(0x2403B12C);
}

NAKED void CK2dCurvePoint::SetBias(float b) {
	JUMP(0x2403B130);
}

NAKED float CK2dCurvePoint::GetTension() const {
	JUMP(0x2403B13F);
}

NAKED void CK2dCurvePoint::SetTension(float t) {
	JUMP(0x2403B143);
}

NAKED float CK2dCurvePoint::GetContinuity() const {
	JUMP(0x2403B152);
}

NAKED void CK2dCurvePoint::SetContinuity(float c) {
	JUMP(0x2403B156);
}

NAKED CKBOOL CK2dCurvePoint::IsLinear() const {
	JUMP(0x2403B165);
}

NAKED void CK2dCurvePoint::SetLinear(CKBOOL linear) {
	JUMP(0x2403B16C);
}

NAKED void CK2dCurvePoint::UseTCB(CKBOOL use) {
	JUMP(0x2403B185);
}

NAKED CKBOOL CK2dCurvePoint::IsTCB() const {
	JUMP(0x2403B199);
}

NAKED float CK2dCurvePoint::GetLength() const {
	JUMP(0x2403B1A2);
}

NAKED Vx2DVector& CK2dCurvePoint::GetPosition() {
	JUMP(0x2403B1A6);
}

NAKED void CK2dCurvePoint::SetPosition(const Vx2DVector& pos) {
	JUMP(0x2403B1AA);
}

NAKED Vx2DVector& CK2dCurvePoint::GetInTangent() {
	JUMP(0x2403B1C1);
}

NAKED Vx2DVector& CK2dCurvePoint::GetOutTangent() {
	JUMP(0x2403B1C5);
}

NAKED void CK2dCurvePoint::SetInTangent(const Vx2DVector& in) {
	JUMP(0x2403B1C9);
}

NAKED void CK2dCurvePoint::SetOutTangent(const Vx2DVector& out) {
	JUMP(0x2403B1E0);
}

NAKED void CK2dCurvePoint::NotifyUpdate() {
	JUMP(0x2400263F);
}

NAKED void CK2dCurvePoint::SetCurve(CK2dCurve* curve) {
	JUMP(0x2403B1F7);
}

NAKED void CK2dCurvePoint::SetLength(float l) {
	JUMP(0x2403B200);
}

NAKED Vx2DVector& CK2dCurvePoint::GetRCurvePos() {
	JUMP(0x2403B20A);
}

NAKED void CK2dCurvePoint::SetRCurvePos(Vx2DVector& v) {
	JUMP(0x2403B20E);
}

NAKED void CK2dCurvePoint::Read(CKStateChunk* chunk) {
	JUMP(0x24002646);
}

#include "CKDef.h"
#include "VxQuaternion.h"

NAKED VxQuaternion Vx3DQuaternionSnuggle(VxQuaternion* Quat, VxVector* Scale) {
	JUMP(0x2429CAE0);
}

NAKED VxQuaternion Vx3DQuaternionFromMatrix(const VxMatrix& Mat) {
	JUMP(0x2429D530);
}

NAKED VxQuaternion Vx3DQuaternionConjugate(const VxQuaternion& Quat) {
	JUMP(0x2429D590);
}

NAKED VxQuaternion Vx3DQuaternionMultiply(const VxQuaternion& QuatL, const VxQuaternion& QuatR) {
	JUMP(0x2429D5C0);
}

NAKED VxQuaternion Vx3DQuaternionDivide(const VxQuaternion& P, const VxQuaternion& Q) {
	JUMP(0x2429D650);
}

NAKED VxQuaternion Slerp(float Theta, const VxQuaternion& Quat1, const VxQuaternion& Quat2) {
	JUMP(0x2429C8F0);
}

NAKED VxQuaternion Squad(float Theta, const VxQuaternion& Quat1, const VxQuaternion& Quat1Out, const VxQuaternion& Quat2In, const VxQuaternion& Quat2) {
	JUMP(0x2429CA70);
}

NAKED VxQuaternion LnDif(const VxQuaternion& P, const VxQuaternion& Q) {
	JUMP(0x2429C6E0);
}

NAKED VxQuaternion Ln(const VxQuaternion& Quat) {
	JUMP(0x2429C650);
}

NAKED VxQuaternion Exp(const VxQuaternion& Quat) {
	JUMP(0x2429C720);
}

NAKED void VxQuaternion::FromMatrix(const VxMatrix& Mat, BOOL MatIsUnit, BOOL RestoreMat) {
	JUMP(0x2429C420);
}

NAKED void VxQuaternion::ToMatrix(VxMatrix& Mat) const {
	JUMP(0x242836E0);
}

NAKED void VxQuaternion::Multiply(const VxQuaternion& Quat) {
	JUMP(0x2429C7B0);
}

NAKED void VxQuaternion::FromRotation(const VxVector& Vector, float Angle) {
	JUMP(0x2429C840);
}

NAKED void VxQuaternion::ToRotation(VxVector& Vector, float& Angle) {
	UNDEFINED;
}

NAKED void VxQuaternion::FromEulerAngles(float eax, float eay, float eaz) {
	JUMP(0x2429C880);
}

NAKED void VxQuaternion::ToEulerAngles(float* eax, float* eay, float* eaz) const {
	JUMP(0x2429C8C0);
}

NAKED void VxQuaternion::Normalize() {
	JUMP(0x2429D6E0);
}

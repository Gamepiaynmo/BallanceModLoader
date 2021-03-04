#include "CKDef.h"
#include "VxMatrix.h"

NAKED void Vx3DMatrixIdentity(VxMatrix& Mat) {
	JUMP(0x2429A990);
}

NAKED void Vx3DMultiplyMatrixVector(VxVector* ResultVector, const VxMatrix& Mat, const VxVector& Vector) {
	JUMP(0x242838F0);
}

NAKED void Vx3DMultiplyMatrixVectorMany(VxVector* ResultVectors, const VxMatrix& Mat, const VxVector& Vectors, int count, int stride) {
	JUMP(0x242839B0);
}

NAKED void Vx3DMultiplyMatrixVector4(VxVector4* ResultVector, const VxMatrix& Mat, const VxVector4* Vector) {
	JUMP(0x24283B70);
}

NAKED void Vx3DMultiplyMatrixVector4(VxVector4* ResultVector, const VxMatrix& Mat, const VxVector& Vector) {
	JUMP(0x24283C60);
}

NAKED void Vx3DRotateVector(VxVector* ResultVector, const VxMatrix& Mat, const VxVector& Vector) {
	JUMP(0x24283E80);
}

NAKED void Vx3DRotateVectorMany(VxVector* ResultVector, const VxMatrix& Mat, const VxVector& Vector, int count, int stride) {
	JUMP(0x24283F30);
}

NAKED void Vx3DMultiplyMatrix(VxMatrix& ResultMat, const VxMatrix& MatA, const VxMatrix& MatB) {
	JUMP(0x242840C0);
}

NAKED void Vx3DMultiplyMatrix4(VxMatrix& ResultMat, const VxMatrix& MatA, const VxMatrix& MatB) {
	JUMP(0x24284480);
}

NAKED void Vx3DInverseMatrix(VxMatrix& InverseMat, const VxMatrix& Mat) {
	JUMP(0x2429AD50);
}

NAKED void Vx3DInverseMatrix44(VxMatrix& InverseMat, const VxMatrix& Mat) {
	UNDEFINED;
}

NAKED float Vx3DMatrixDeterminant(const VxMatrix& Mat) {
	JUMP(0x2429AD10);
}

NAKED void Vx3DMatrixFromRotation(VxMatrix& ResultMat, const VxVector& Vector, float Angle) {
	JUMP(0x2429AF90);
}

NAKED void Vx3DMatrixFromRotationAndOrigin(VxMatrix& ResultMat, const VxVector& Vector, const VxVector& Origin, float Angle) {
	JUMP(0x2429B0E0);
}

NAKED void Vx3DMatrixFromEulerAngles(VxMatrix& Mat, float eax, float eay, float eaz) {
	JUMP(0x2429B280);
}

NAKED void Vx3DMatrixToEulerAngles(const VxMatrix& Mat, float* eax, float* eay, float* eaz) {
	JUMP(0x2429B3E0);
}

NAKED void Vx3DInterpolateMatrix(float step, VxMatrix& Res, const VxMatrix& A, const VxMatrix& B) {
	JUMP(0x2429A9B0);
}

NAKED void Vx3DInterpolateMatrixNoScale(float step, VxMatrix& Res, const VxMatrix& A, const VxMatrix& B) {
	JUMP(0x2429A9B0);
}

NAKED void Vx3DTransposeMatrix(VxMatrix& Result, const VxMatrix& A) {
	JUMP(0x2429A920);
}

NAKED void Vx3DDecomposeMatrix(const VxMatrix& A, VxQuaternion& Quat, VxVector& Pos, VxVector& Scale) {
	JUMP(0x2429BE50);
}

NAKED float Vx3DDecomposeMatrixTotal(const VxMatrix& A, VxQuaternion& Quat, VxVector& Pos, VxVector& Scale, VxQuaternion& URot) {
	JUMP(0x2429BEF0);
}

NAKED float Vx3DDecomposeMatrixTotalPtr(const VxMatrix& A, VxQuaternion* Quat, VxVector* Pos, VxVector* Scale, VxQuaternion* URot) {
	JUMP(0x2429C080);
}

NAKED void VxInverseProject(const VxMatrix& iProjection, const Vx2DVector& i2D, const float iZ, VxVector* o3D) {
	UNDEFINED;
}

NAKED const VxMatrix& VxMatrix::Identity() {
	JUMP(0x2429B460);
}

NAKED XBOOL VxMatrix::Compare(const VxMatrix& mat) const {
	UNDEFINED;
}

NAKED void VxMatrix::RecomposeMatrixEx(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat, const VxQuaternion& Shear, float Sign) {
	UNDEFINED;
}

NAKED void VxMatrix::RecomposeMatrix(const VxVector& Pos, const VxVector& Scale, const VxQuaternion& Quat) {
	UNDEFINED;
}

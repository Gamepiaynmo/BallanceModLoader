#include "CKObjectDeclaration.h"

NAKED void CKObjectDeclaration::SetDescription(CKSTRING Description) {
	JUMP(0x24021525);
}

NAKED CKSTRING CKObjectDeclaration::GetDescription() {
	JUMP(0x24021542);
}

NAKED void CKObjectDeclaration::SetGuid(CKGUID guid) {
	JUMP(0x24006F78);
}

NAKED CKGUID CKObjectDeclaration::GetGuid() {
	JUMP(0x24006F89);
}

NAKED void CKObjectDeclaration::SetType(int type) {
	JUMP(0x24021580);
}

NAKED int CKObjectDeclaration::GetType() {
	JUMP(0x2402158A);
}

NAKED void CKObjectDeclaration::NeedManager(CKGUID Manager) {
	JUMP(0x24021546);
}

NAKED void CKObjectDeclaration::SetCreationFunction(CKDLL_CREATEPROTOFUNCTION f) {
	JUMP(0x24006FA5);
}

NAKED CKDLL_CREATEPROTOFUNCTION CKObjectDeclaration::GetCreationFunction() {
	JUMP(0x2402158E);
}

NAKED void CKObjectDeclaration::SetAuthorGuid(CKGUID guid) {
	JUMP(0x24021592);
}

NAKED CKGUID CKObjectDeclaration::GetAuthorGuid() {
	JUMP(0x240098A9);
}

NAKED void CKObjectDeclaration::SetAuthorName(CKSTRING Name) {
	JUMP(0x240215A3);
}

NAKED CKSTRING CKObjectDeclaration::GetAuthorName() {
	JUMP(0x24017AE9);
}

NAKED void CKObjectDeclaration::SetVersion(CKDWORD verion) {
	JUMP(0x240081A1);
}

NAKED CKDWORD CKObjectDeclaration::GetVersion() {
	JUMP(0x2400CEFF);
}

NAKED void CKObjectDeclaration::SetCompatibleClassId(CK_CLASSID id) {
	JUMP(0x24006F9B);
}

NAKED CK_CLASSID CKObjectDeclaration::GetCompatibleClassId() {
	JUMP(0x24035F34);
}

NAKED void CKObjectDeclaration::SetCategory(CKSTRING cat) {
	JUMP(0x240215C0);
}

NAKED CKSTRING CKObjectDeclaration::GetCategory() {
	JUMP(0x2401B69E);
}

NAKED CKSTRING CKObjectDeclaration::GetName() {
	JUMP(0x2403B0F3);
}

NAKED int CKObjectDeclaration::GetPluginIndex() {
	JUMP(0x2403B119);
}

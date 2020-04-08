#include "CKAttributeManager.h"

NAKED CKAttributeType CKAttributeManager::RegisterNewAttributeType(CKSTRING Name, CKGUID ParameterType, CK_CLASSID CompatibleCid, CK_ATTRIBUT_FLAGS flags) {
	JUMP(0x2400AAD9);
}

NAKED void CKAttributeManager::UnRegisterAttribute(CKAttributeType AttribType) {
	JUMP(0x2400ACC3);
}

NAKED void CKAttributeManager::UnRegisterAttribute(CKSTRING atname) {
	JUMP(0x2400AD48);
}

NAKED CKSTRING CKAttributeManager::GetAttributeNameByType(CKAttributeType AttribType) {
	JUMP(0x2400AD93);
}

NAKED CKAttributeType CKAttributeManager::GetAttributeTypeByName(CKSTRING AttribName) {
	JUMP(0x2400ADAD);
}

NAKED void CKAttributeManager::SetAttributeNameByType(CKAttributeType AttribType, CKSTRING name) {
	JUMP(0x2400AFB2);
}

NAKED int CKAttributeManager::GetAttributeCount() {
	JUMP(0x2400E67D);
}

NAKED CKGUID CKAttributeManager::GetAttributeParameterGUID(CKAttributeType AttribType) {
	JUMP(0x2400AEBC);
}

NAKED CKParameterType CKAttributeManager::GetAttributeParameterType(CKAttributeType AttribType) {
	JUMP(0x2400AEF5);
}

NAKED CK_CLASSID CKAttributeManager::GetAttributeCompatibleClassId(CKAttributeType AttribType) {
	JUMP(0x2400AF28);
}

NAKED CKBOOL CKAttributeManager::IsAttributeIndexValid(CKAttributeType index) {
	JUMP(0x2400AFD8);
}

NAKED CKBOOL CKAttributeManager::IsCategoryIndexValid(CKAttributeCategory index) {
	JUMP(0x2400B2D4);
}

NAKED CK_ATTRIBUT_FLAGS CKAttributeManager::GetAttributeFlags(CKAttributeType AttribType) {
	JUMP(0x2400AF4A);
}

NAKED void CKAttributeManager::SetAttributeCallbackFunction(CKAttributeType AttribType, CKATTRIBUTECALLBACK fct, void* arg) {
	JUMP(0x2400AD60);
}

NAKED void CKAttributeManager::SetAttributeDefaultValue(CKAttributeType AttribType, CKSTRING DefaultVal) {
	JUMP(0x2400AE29);
}

NAKED CKSTRING CKAttributeManager::GetAttributeDefaultValue(CKAttributeType AttribType) {
	JUMP(0x2400AE9B);
}

NAKED const XObjectPointerArray& CKAttributeManager::GetAttributeListPtr(CKAttributeType AttribType) {
	JUMP(0x2400B3CE);
}

NAKED const XObjectPointerArray& CKAttributeManager::GetGlobalAttributeListPtr(CKAttributeType AttribType) {
	JUMP(0x2400B416);
}

NAKED const XObjectPointerArray& CKAttributeManager::FillListByAttributes(CKAttributeType* ListAttrib, int AttribCount) {
	JUMP(0x2400B2F5);
}

NAKED const XObjectPointerArray& CKAttributeManager::FillListByGlobalAttributes(CKAttributeType* ListAttrib, int AttribCount) {
	JUMP(0x2400B37B);
}

NAKED int CKAttributeManager::GetCategoriesCount() {
	JUMP(0x2401B69E);
}

NAKED CKSTRING CKAttributeManager::GetCategoryName(CKAttributeCategory index) {
	JUMP(0x2400B07E);
}

NAKED CKAttributeCategory CKAttributeManager::GetCategoryByName(CKSTRING Name) {
	JUMP(0x2400B03F);
}

NAKED void CKAttributeManager::SetCategoryName(CKAttributeCategory catType, CKSTRING name) {
	JUMP(0x2400B27E);
}

NAKED CKAttributeCategory CKAttributeManager::AddCategory(CKSTRING Category, CKDWORD flags) {
	JUMP(0x2400B0D6);
}

NAKED void CKAttributeManager::RemoveCategory(CKSTRING Category) {
	JUMP(0x2400B19C);
}

NAKED CKDWORD CKAttributeManager::GetCategoryFlags(CKAttributeCategory cat) {
	JUMP(0x2400AFF9);
}

NAKED CKDWORD CKAttributeManager::GetCategoryFlags(CKSTRING cat) {
	JUMP(0x2400B01A);
}

NAKED void CKAttributeManager::SetAttributeCategory(CKAttributeType AttribType, CKSTRING Category) {
	JUMP(0x2400B09E);
}

NAKED CKSTRING CKAttributeManager::GetAttributeCategory(CKAttributeType AttribType) {
	JUMP(0x2400AF6B);
}

NAKED CKAttributeCategory CKAttributeManager::GetAttributeCategoryIndex(CKAttributeType AttribType) {
	JUMP(0x2400AF91);
}

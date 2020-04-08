#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

typedef void (*CKATTRIBUTECALLBACK) (CKAttributeType AttribType, CKBOOL Set, CKBeObject* obj, void* arg);

class BML_EXPORT CKAttributeManager : public CKBaseManager {
public:
	CKAttributeType RegisterNewAttributeType(CKSTRING Name, CKGUID ParameterType, CK_CLASSID CompatibleCid = CKCID_BEOBJECT, CK_ATTRIBUT_FLAGS flags = CK_ATTRIBUT_SYSTEM);
	void UnRegisterAttribute(CKAttributeType AttribType);
	void UnRegisterAttribute(CKSTRING atname);
	CKSTRING GetAttributeNameByType(CKAttributeType AttribType);
	CKAttributeType GetAttributeTypeByName(CKSTRING AttribName);
	void SetAttributeNameByType(CKAttributeType AttribType, CKSTRING name);
	int GetAttributeCount();
	CKGUID GetAttributeParameterGUID(CKAttributeType AttribType);
	CKParameterType GetAttributeParameterType(CKAttributeType AttribType);
	CK_CLASSID GetAttributeCompatibleClassId(CKAttributeType AttribType);
	CKBOOL IsAttributeIndexValid(CKAttributeType index);
	CKBOOL IsCategoryIndexValid(CKAttributeCategory index);
	CK_ATTRIBUT_FLAGS GetAttributeFlags(CKAttributeType AttribType);
	void SetAttributeCallbackFunction(CKAttributeType AttribType, CKATTRIBUTECALLBACK fct, void* arg);
	void SetAttributeDefaultValue(CKAttributeType AttribType, CKSTRING DefaultVal);
	CKSTRING GetAttributeDefaultValue(CKAttributeType AttribType);
	const XObjectPointerArray& GetAttributeListPtr(CKAttributeType AttribType);
	const XObjectPointerArray& GetGlobalAttributeListPtr(CKAttributeType AttribType);
	const XObjectPointerArray& FillListByAttributes(CKAttributeType* ListAttrib, int AttribCount);
	const XObjectPointerArray& FillListByGlobalAttributes(CKAttributeType* ListAttrib, int AttribCount);
	int GetCategoriesCount();
	CKSTRING GetCategoryName(CKAttributeCategory index);
	CKAttributeCategory GetCategoryByName(CKSTRING Name);
	void SetCategoryName(CKAttributeCategory catType, CKSTRING name);
	CKAttributeCategory AddCategory(CKSTRING Category, CKDWORD flags = 0);
	void RemoveCategory(CKSTRING Category);
	CKDWORD GetCategoryFlags(CKAttributeCategory cat);
	CKDWORD GetCategoryFlags(CKSTRING cat);
	void SetAttributeCategory(CKAttributeType AttribType, CKSTRING Category);
	CKSTRING GetAttributeCategory(CKAttributeType AttribType);
	CKAttributeCategory GetAttributeCategoryIndex(CKAttributeType AttribType);

protected:
	CKAttributeManager() {};
	~CKAttributeManager() {};
};
#pragma once

#include "CKDef.h"

typedef CKERROR(*CKDLL_CREATEPROTOFUNCTION) (CKBehaviorPrototype**);

class BML_EXPORT CKObjectDeclaration {
public:
	void SetDescription(CKSTRING Description);
	CKSTRING GetDescription();
	void SetGuid(CKGUID guid);
	CKGUID GetGuid();
	void SetType(int type);
	int GetType();
	void NeedManager(CKGUID Manager);
	void SetCreationFunction(CKDLL_CREATEPROTOFUNCTION f);
	CKDLL_CREATEPROTOFUNCTION GetCreationFunction();
	void SetAuthorGuid(CKGUID guid);
	CKGUID GetAuthorGuid();
	void SetAuthorName(CKSTRING Name);
	CKSTRING GetAuthorName();
	void SetVersion(CKDWORD verion);
	CKDWORD GetVersion();
	void SetCompatibleClassId(CK_CLASSID id);
	CK_CLASSID GetCompatibleClassId();
	void SetCategory(CKSTRING cat);
	CKSTRING GetCategory();
	CKSTRING GetName();
	int GetPluginIndex();

protected:
	CKObjectDeclaration() {};
	~CKObjectDeclaration() {};
};
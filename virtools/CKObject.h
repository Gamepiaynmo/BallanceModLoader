#pragma once

#include "CKDef.h"
#include "CKContext.h"

typedef enum CK_OBJECT_SHOWOPTION {
	CKHIDE = 0,
	CKSHOW = 1,
	CKHIERARCHICALHIDE = 2
} CK_OBJECT_SHOWOPTION;

class BML_EXPORT CKObject {
public:
	CKContext* GetCKContext();
	CK_CLASSID GetClassID();
	CK_ID GetID();

	CKSTRING GetName();
	void SetName(CKSTRING Name, CKBOOL shared = FALSE);

	int CanBeHide();
	CKBOOL IsHiddenByParent();
	CKBOOL IsHierarchicallyHide();
	CKBOOL IsVisible();
	void Show(CK_OBJECT_SHOWOPTION show = CKSHOW);

	void* GetAppData();
	void SetAppData(void* Data);

	CKDWORD GetObjectFlags();
	CKBOOL IsDynamic();
	CKBOOL IsToBeDeleted();
	void ModifyObjectFlags(CKDWORD add, CKDWORD remove);
	
protected:
	CKObject() {};
	~CKObject() {};
};
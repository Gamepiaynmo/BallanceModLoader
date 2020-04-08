#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

typedef CKBOOL(*CK_RENDEROBJECT_CALLBACK)(CKRenderContext* Dev, CKRenderObject* ent, void* Argument);

class BML_EXPORT CKRenderObject : public CKBeObject {
public:
	CKBOOL IsInRenderContext(CKRenderContext* context);
	CKBOOL IsRootObject();
	CKBOOL IsToBeRendered();
	void SetZOrder(int Z);
	int GetZOrder();
	CKBOOL IsToBeRenderedLast();
	CKBOOL AddPreRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument, CKBOOL Temp = FALSE, CKBOOL ModifyRenderPipeline = TRUE);
	CKBOOL RemovePreRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument);
	CKBOOL SetRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument);
	CKBOOL RemoveRenderCallBack();
	CKBOOL AddPostRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument, CKBOOL Temp = FALSE, CKBOOL ModifyRenderPipeline = TRUE);
	CKBOOL RemovePostRenderCallBack(CK_RENDEROBJECT_CALLBACK Function, void* Argument);
	void RemoveAllCallbacks();

protected:
	CKRenderObject() {};
	~CKRenderObject() {};
};
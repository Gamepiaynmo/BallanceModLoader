#pragma once

#include "CKDef.h"

typedef int (*CKBEHAVIORFCT) (const CKBehaviorContext& context);
typedef CKERROR(*CKBEHAVIORCALLBACKFCT) (const CKBehaviorContext& context);

class BML_EXPORT CKBehaviorPrototype {
public:
	int DeclareInput(CKSTRING name);
	int DeclareOutput(CKSTRING name);
	int DeclareInParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval = NULL);
	int DeclareInParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize);
	int DeclareOutParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval = NULL);
	int DeclareOutParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize);
	int DeclareLocalParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval = NULL);
	int DeclareLocalParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize);
	int DeclareSetting(CKSTRING name, CKGUID guid_type, CKSTRING defaultval = NULL);
	int DeclareSetting(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize);
	void SetGuid(CKGUID guid);
	CKGUID GetGuid();
	void SetFlags(CK_BEHAVIORPROTOTYPE_FLAGS flags);
	CK_BEHAVIORPROTOTYPE_FLAGS GetFlags();
	void SetApplyToClassID(CK_CLASSID cid);
	CK_CLASSID GetApplyToClassID();
	void SetFunction(CKBEHAVIORFCT fct);
	CKBEHAVIORFCT GetFunction();
	void SetBehaviorCallbackFct(CKBEHAVIORCALLBACKFCT fct, CKDWORD CallbackMask = CKCB_BEHAVIORALL, void* param = NULL);
	CKBEHAVIORCALLBACKFCT GetBehaviorCallbackFct();
	void SetBehaviorFlags(CK_BEHAVIOR_FLAGS flags);
	CK_BEHAVIOR_FLAGS GetBehaviorFlags();
	CKSTRING GetName();

protected:
	CKBehaviorPrototype() {};
	~CKBehaviorPrototype() {};
};
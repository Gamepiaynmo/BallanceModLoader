#pragma once

#include "CKDef.h"
#include "CKSceneObject.h"

struct BML_EXPORT CKAttributeVal {
	CKAttributeType AttribType;
	CK_ID Parameter;
};

class BML_EXPORT CKBeObject : public CKSceneObject {
public:
	void ExecuteBehaviors(float delta);

	CKBOOL IsInGroup(CKGroup* group);

	CKBOOL HasAttribute(CKAttributeType AttribType);
	CKBOOL SetAttribute(CKAttributeType AttribType, CK_ID parameter = 0);
	CKBOOL RemoveAttribute(CKAttributeType AttribType);
	CKParameterOut* GetAttributeParameter(CKAttributeType AttribType);

	int GetAttributeCount();
	int GetAttributeType(int index);
	CKParameterOut* GetAttributeParameterByIndex(int index);
	void GetAttributeList(CKAttributeVal* liste);
	void RemoveAllAttributes();

	CKERROR AddScript(CKBehavior* ckb);
	CKBehavior* RemoveScript(CK_ID id);
	CKBehavior* RemoveScript(int pos);
	CKERROR RemoveAllScripts();
	CKBehavior* GetScript(int pos);
	int GetScriptCount();

	int GetPriority();
	void SetPriority(int priority);

	int GetLastFrameMessageCount();
	CKMessage* GetLastFrameMessage(int pos);

	void SetAsWaitingForMessages(CKBOOL wait = TRUE);
	CKBOOL IsWaitingForMessages();
	int CallBehaviorCallbackFunction(CKDWORD Message, CKGUID* behguid = NULL);
	float GetLastExecutionTime();

protected:
	CKBeObject() {};
	~CKBeObject() {};

private:
	BYTE placeholder[0x4f];
};
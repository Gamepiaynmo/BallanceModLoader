#pragma once

#include "CKDef.h"

typedef enum CK_MESSAGE_SENDINGTYPE {
	CK_MESSAGE_BROADCAST = 1,
	CK_MESSAGE_SINGLE = 2,
	CK_MESSAGE_GROUP = 3,
} CK_MESSAGE_SENDINGTYPE;

class BML_EXPORT CKMessage {
public:
	CKERROR SetBroadcastObjectType(CK_CLASSID type = CKCID_BEOBJECT);
	CKERROR AddParameter(CKParameter*, CKBOOL DeleteParameterWithMessage = FALSE);
	CKERROR RemoveParameter(CKParameter*);
	int GetParameterCount();
	CKParameter* GetParameter(int pos);
	void SetSender(CKBeObject* obj);
	CKBeObject* GetSender();
	void SetRecipient(CKObject* recipient);
	CKObject* GetRecipient();
	CK_MESSAGE_SENDINGTYPE GetSendingType();
	void SetSendingType(CK_MESSAGE_SENDINGTYPE Type);
	void SetMsgType(CKMessageType type);
	CKMessageType GetMsgType();

protected:
	CKMessage() {};
	~CKMessage() {};
};
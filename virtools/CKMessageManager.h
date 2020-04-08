#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

#undef SendMessage

class BML_EXPORT CKMessageManager : public CKBaseManager {
public:
	CKMessageType AddMessageType(CKSTRING MsgName);
	CKSTRING GetMessageTypeName(CKMessageType MsgType);
	int GetMessageTypeCount();
	void RenameMessageType(CKMessageType MsgType, CKSTRING NewName);
	void RenameMessageType(CKSTRING OldName, CKSTRING NewName);
	CKERROR SendMessage(CKMessage* msg);
	CKMessage* SendMessageSingle(CKMessageType MsgType, CKBeObject* dest, CKBeObject* sender = NULL);
	CKMessage* SendMessageGroup(CKMessageType MsgType, CKGroup* group, CKBeObject* sender = NULL);
	CKMessage* SendMessageBroadcast(CKMessageType MsgType, CK_CLASSID id = CKCID_BEOBJECT, CKBeObject* sender = NULL);
	CKERROR RegisterWait(CKMessageType MsgType, CKBehavior* behav, int OutputToActivate, CKBeObject* obj);
	CKERROR RegisterWait(CKSTRING MsgName, CKBehavior* behav, int OutputToActivate, CKBeObject* obj);
	CKERROR UnRegisterWait(CKMessageType MsgType, CKBehavior* behav, int OutputToActivate);
	CKERROR UnRegisterWait(CKSTRING MsgName, CKBehavior* behav, int OutputToActivate);
	CKERROR RegisterDefaultMessages();

protected:
	CKMessageManager() {};
	~CKMessageManager() {};
};
#include "CKMessageManager.h"

NAKED CKMessageType CKMessageManager::AddMessageType(CKSTRING MsgName) {
	JUMP(0x2400D85B);
}

NAKED CKSTRING CKMessageManager::GetMessageTypeName(CKMessageType MsgType) {
	JUMP(0x2400D924);
}

NAKED int CKMessageManager::GetMessageTypeCount() {
	JUMP(0x2400D951);
}

NAKED void CKMessageManager::RenameMessageType(CKMessageType MsgType, CKSTRING NewName) {
	JUMP(0x2400D95B);
}

NAKED void CKMessageManager::RenameMessageType(CKSTRING OldName, CKSTRING NewName) {
	JUMP(0x2400D983);
}

NAKED CKERROR CKMessageManager::SendMessage(CKMessage* msg) {
	JUMP(0x2400DF0B);
}

NAKED CKMessage* CKMessageManager::SendMessageSingle(CKMessageType MsgType, CKBeObject* dest, CKBeObject* sender) {
	JUMP(0x2400D211);
}

NAKED CKMessage* CKMessageManager::SendMessageGroup(CKMessageType MsgType, CKGroup* group, CKBeObject* sender) {
	JUMP(0x2400D248);
}

NAKED CKMessage* CKMessageManager::SendMessageBroadcast(CKMessageType MsgType, CK_CLASSID id, CKBeObject* sender) {
	JUMP(0x2400D28A);
}

NAKED CKERROR CKMessageManager::RegisterWait(CKMessageType MsgType, CKBehavior* behav, int OutputToActivate, CKBeObject* obj) {
	JUMP(0x2400D99F);
}

NAKED CKERROR CKMessageManager::RegisterWait(CKSTRING MsgName, CKBehavior* behav, int OutputToActivate, CKBeObject* obj) {
	JUMP(0x2400DA82);
}

NAKED CKERROR CKMessageManager::UnRegisterWait(CKMessageType MsgType, CKBehavior* behav, int OutputToActivate) {
	JUMP(0x2400DAA6);
}

NAKED CKERROR CKMessageManager::UnRegisterWait(CKSTRING MsgName, CKBehavior* behav, int OutputToActivate) {
	JUMP(0x2400DB39);
}

NAKED CKERROR CKMessageManager::RegisterDefaultMessages() {
	JUMP(0x2400D83E);
}

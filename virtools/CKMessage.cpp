#include "CKMessage.h"
#include "CKBeObject.h"

NAKED CKERROR CKMessage::SetBroadcastObjectType(CK_CLASSID type) {
	JUMP(0x24007FE6);
}

NAKED CKERROR CKMessage::AddParameter(CKParameter*, CKBOOL DeleteParameterWithMessage) {
	JUMP(0x24007EFE);
}

NAKED CKERROR CKMessage::RemoveParameter(CKParameter*) {
	JUMP(0x24007F6B);
}

NAKED int CKMessage::GetParameterCount() {
	JUMP(0x24007FB8);
}

NAKED CKParameter* CKMessage::GetParameter(int pos) {
	JUMP(0x24007FCB);
}

void CKMessage::SetSender(CKBeObject* obj) {
	SET_MEM(0x10, CK_ID, CKOBJID(obj));
}

CKBeObject* CKMessage::GetSender() {
	return static_cast<CKBeObject*>(GET_MEM(0x18, CKContext*)->GetObject(GET_MEM(0x10, CK_ID)));
}

void CKMessage::SetRecipient(CKObject* recipient) {
	SET_MEM(0x14, CK_ID, CKOBJID(recipient));
}

CKObject* CKMessage::GetRecipient() {
	return GET_MEM(0x18, CKContext*)->GetObject(GET_MEM(0x14, CK_ID));
}

CK_MESSAGE_SENDINGTYPE CKMessage::GetSendingType() {
	RETURN_MEM(0xc, CK_MESSAGE_SENDINGTYPE);
}

void CKMessage::SetSendingType(CK_MESSAGE_SENDINGTYPE Type) {
	SET_MEM(0xc, CK_MESSAGE_SENDINGTYPE, Type);
}

void CKMessage::SetMsgType(CKMessageType type) {
	SET_MEM(0x4, CKMessageType, type);
}

CKMessageType CKMessage::GetMsgType() {
	RETURN_MEM(0x4, CKMessageType);
}

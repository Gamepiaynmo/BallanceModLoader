#include "CKBeObject.h"

NAKED void CKBeObject::ExecuteBehaviors(float delta) {
	JUMP(0x2401AF67);
}

NAKED CKBOOL CKBeObject::IsInGroup(CKGroup* group) {
	JUMP(0x2401B0C6);
}

NAKED CKBOOL CKBeObject::HasAttribute(CKAttributeType AttribType) {
	JUMP(0x2401B39A);
}

NAKED CKBOOL CKBeObject::SetAttribute(CKAttributeType AttribType, CK_ID parameter) {
	JUMP(0x2401B3BC);
}

NAKED CKBOOL CKBeObject::RemoveAttribute(CKAttributeType AttribType) {
	JUMP(0x2401B4FF);
}

NAKED CKParameterOut* CKBeObject::GetAttributeParameter(CKAttributeType AttribType) {
	JUMP(0x2401B5C5);
}

NAKED int CKBeObject::GetAttributeCount() {
	JUMP(0x2401B5FB);
}

NAKED int CKBeObject::GetAttributeType(int index) {
	JUMP(0x2401B5FF);
}

NAKED CKParameterOut* CKBeObject::GetAttributeParameterByIndex(int index) {
	JUMP(0x2401B572);
}

NAKED void CKBeObject::GetAttributeList(CKAttributeVal* liste) {
	JUMP(0x2401B4C3);
}

NAKED void CKBeObject::RemoveAllAttributes() {
	JUMP(0x2401B646);
}

NAKED CKERROR CKBeObject::AddScript(CKBehavior* ckb) {
	JUMP(0x2401B126);
}

NAKED CKBehavior* CKBeObject::RemoveScript(CK_ID id) {
	JUMP(0x2401B2A7);
}

NAKED CKBehavior* CKBeObject::RemoveScript(int pos) {
	JUMP(0x2401B21B);
}

NAKED CKERROR CKBeObject::RemoveAllScripts() {
	JUMP(0x2401B2F1);
}

NAKED CKBehavior* CKBeObject::GetScript(int pos) {
	JUMP(0x2401B0F0);
}

NAKED int CKBeObject::GetScriptCount() {
	JUMP(0x2401B113);
}

NAKED int CKBeObject::GetPriority() {
	JUMP(0x2401B69E);
}

NAKED void CKBeObject::SetPriority(int priority) {
	JUMP(0x2401B6A2);
}

NAKED int CKBeObject::GetLastFrameMessageCount() {
	JUMP(0x2401B33D);
}

NAKED CKMessage* CKBeObject::GetLastFrameMessage(int pos) {
	JUMP(0x2401B350);
}

NAKED void CKBeObject::SetAsWaitingForMessages(CKBOOL wait) {
	JUMP(0x2401B379);
}

NAKED CKBOOL CKBeObject::IsWaitingForMessages() {
	JUMP(0x2401B391);
}

NAKED int CKBeObject::CallBehaviorCallbackFunction(CKDWORD Message, CKGUID* behguid) {
	JUMP(0x2401B06F);
}

NAKED float CKBeObject::GetLastExecutionTime() {
	JUMP(0x2401AF63);
}

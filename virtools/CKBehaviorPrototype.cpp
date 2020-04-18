#include "CKBehaviorPrototype.h"

NAKED int CKBehaviorPrototype::DeclareInput(CKSTRING name) {
	JUMPV(0x00);
}

NAKED int CKBehaviorPrototype::DeclareOutput(CKSTRING name) {
	JUMPV(0x04);
}

NAKED int CKBehaviorPrototype::DeclareInParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval) {
	JUMPV(0x08);
}

NAKED int CKBehaviorPrototype::DeclareInParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize) {
	JUMPV(0x0c);
}

NAKED int CKBehaviorPrototype::DeclareOutParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval) {
	JUMPV(0x10);
}

NAKED int CKBehaviorPrototype::DeclareOutParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize) {
	JUMPV(0x14);
}

NAKED int CKBehaviorPrototype::DeclareLocalParameter(CKSTRING name, CKGUID guid_type, CKSTRING defaultval) {
	JUMP(0x240075F9);
}

NAKED int CKBehaviorPrototype::DeclareLocalParameter(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize) {
	JUMP(0x24007717);
}

NAKED int CKBehaviorPrototype::DeclareSetting(CKSTRING name, CKGUID guid_type, CKSTRING defaultval) {
	JUMP(0x24007841);
}

NAKED int CKBehaviorPrototype::DeclareSetting(CKSTRING name, CKGUID guid_type, void* defaultval, int valsize) {
	JUMP(0x24007962);
}

NAKED void CKBehaviorPrototype::SetGuid(CKGUID guid) {
	JUMP(0x24006F78);
}

NAKED CKGUID CKBehaviorPrototype::GetGuid() {
	JUMP(0x24006F89);
}

NAKED void CKBehaviorPrototype::SetFlags(CK_BEHAVIORPROTOTYPE_FLAGS flags) {
	JUMP(0x24006F9B);
}

NAKED CK_BEHAVIORPROTOTYPE_FLAGS CKBehaviorPrototype::GetFlags() {
	JUMP(0x24035F34);
}

NAKED void CKBehaviorPrototype::SetApplyToClassID(CK_CLASSID cid) {
	JUMP(0x240081A1);
}

NAKED CK_CLASSID CKBehaviorPrototype::GetApplyToClassID() {
	JUMP(0x2400CEFF);
}

NAKED void CKBehaviorPrototype::SetFunction(CKBEHAVIORFCT fct) {
	JUMP(0x24006FAF);
}

NAKED CKBEHAVIORFCT CKBehaviorPrototype::GetFunction() {
	JUMP(0x24021542);
}

NAKED void CKBehaviorPrototype::SetBehaviorCallbackFct(CKBEHAVIORCALLBACKFCT fct, CKDWORD CallbackMask, void* param) {
	JUMP(0x24006FB9);
}

NAKED CKBEHAVIORCALLBACKFCT CKBehaviorPrototype::GetBehaviorCallbackFct() {
	JUMP(0x2400829A);
}

NAKED void CKBehaviorPrototype::SetBehaviorFlags(CK_BEHAVIOR_FLAGS flags) {
	JUMP(0x24006FA5);
}

NAKED CK_BEHAVIOR_FLAGS CKBehaviorPrototype::GetBehaviorFlags() {
	JUMP(0x2402158E);
}

NAKED CKSTRING CKBehaviorPrototype::GetName() {
	JUMP(0x2403B100);
}

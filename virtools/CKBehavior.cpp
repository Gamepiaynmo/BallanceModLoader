#include "CKBehavior.h"

NAKED CK_BEHAVIOR_TYPE CKBehavior::GetType() {
	JUMP(0x24003B1B);
}

NAKED void CKBehavior::SetType(CK_BEHAVIOR_TYPE) {
	JUMP(0x24003B31);
}

NAKED void CKBehavior::SetFlags(CK_BEHAVIOR_FLAGS) {
	JUMP(0x24018678);
}

NAKED CK_BEHAVIOR_FLAGS CKBehavior::GetFlags() {
	JUMP(0x24003B62);
}

NAKED CK_BEHAVIOR_FLAGS CKBehavior::ModifyFlags(CKDWORD Add, CKDWORD Remove) {
	JUMP(0x24003B4D);
}

NAKED void CKBehavior::UseGraph() {
	JUMP(0x24003BC2);
}

NAKED void CKBehavior::UseFunction() {
	JUMP(0x24003B66);
}

NAKED int CKBehavior::IsUsingFunction() {
	JUMP(0x24003BBB);
}

NAKED CKBOOL CKBehavior::IsTargetable() {
	JUMP(0x240037DC);
}

NAKED CKBeObject* CKBehavior::GetTarget() {
	JUMP(0x240035CE);
}

NAKED CKERROR CKBehavior::UseTarget(CKBOOL Use) {
	JUMP(0x24003654);
}

NAKED CKBOOL CKBehavior::IsUsingTarget() {
	JUMP(0x24003788);
}

NAKED CKParameterIn* CKBehavior::GetTargetParameter() {
	JUMP(0x2402C137);
}

NAKED void CKBehavior::SetAsTargetable(CKBOOL target) {
	JUMP(0x240037E5);
}

NAKED CKParameterIn* CKBehavior::ReplaceTargetParameter(CKParameterIn* targetParam) {
	JUMP(0x24003791);
}

NAKED CKParameterIn* CKBehavior::RemoveTargetParameter() {
	JUMP(0x240037CB);
}

NAKED CK_CLASSID CKBehavior::GetCompatibleClassID() {
	JUMP(0x24003B3F);
}

NAKED void CKBehavior::SetCompatibleClassID(CK_CLASSID) {
	JUMP(0x24003B43);
}

NAKED void CKBehavior::SetFunction(CKBEHAVIORFCT fct) {
	JUMP(0x24003C1B);
}

NAKED CKBEHAVIORFCT CKBehavior::GetFunction() {
	JUMP(0x24003C2C);
}

NAKED void CKBehavior::SetCallbackFunction(CKBEHAVIORCALLBACKFCT fct) {
	JUMP(0x24003C38);
}

NAKED int CKBehavior::CallCallbackFunction(CKDWORD Message) {
	JUMP(0x240049AE);
}

NAKED int CKBehavior::CallSubBehaviorsCallbackFunction(CKDWORD Message, CKGUID* behguid) {
	JUMP(0x24004A41);
}

NAKED CKBOOL CKBehavior::IsActive() {
	JUMP(0x24003983);
}

NAKED int CKBehavior::Execute(float deltat) {
	JUMP(0x24003806);
}

NAKED CKBOOL CKBehavior::IsParentScriptActiveInScene(CKScene* scn) {
	JUMP(0x2400398A);
}

NAKED int CKBehavior::GetShortestDelay(CKBehavior* beh) {
	JUMP(0x24003AD1);
}

NAKED CKBeObject* CKBehavior::GetOwner() {
	JUMP(0x240035C2);
}

NAKED CKBehavior* CKBehavior::GetParent() {
	JUMP(0x240033F3);
}

NAKED CKBehavior* CKBehavior::GetOwnerScript() {
	JUMP(0x240033FF);
}

NAKED CKERROR CKBehavior::InitFromPrototype(CKBehaviorPrototype* proto) {
	JUMP(0x24003D9C);
}

NAKED CKERROR CKBehavior::InitFromGuid(CKGUID Guid) {
	JUMP(0x24003CB3);
}

NAKED CKERROR CKBehavior::InitFctPtrFromGuid(CKGUID Guid) {
	JUMP(0x24003CDD);
}

NAKED CKERROR CKBehavior::InitFctPtrFromPrototype(CKBehaviorPrototype* proto) {
	JUMP(0x24003CFA);
}

NAKED CKGUID CKBehavior::GetPrototypeGuid() {
	JUMP(0x24003C49);
}

NAKED CKBehaviorPrototype* CKBehavior::GetPrototype() {
	JUMP(0x24003C81);
}

NAKED CKSTRING CKBehavior::GetPrototypeName() {
	JUMP(0x24003C68);
}

NAKED CKDWORD CKBehavior::GetVersion() {
	JUMP(0x24003C96);
}

NAKED void CKBehavior::SetVersion(CKDWORD version) {
	JUMP(0x24003CA2);
}

NAKED void CKBehavior::ActivateOutput(int pos, CKBOOL active) {
	JUMP(0x2400270C);
}

NAKED CKBOOL CKBehavior::IsOutputActive(int pos) {
	JUMP(0x2400273E);
}

NAKED CKBehaviorIO* CKBehavior::RemoveOutput(int pos) {
	JUMP(0x24002798);
}

NAKED CKERROR CKBehavior::DeleteOutput(int pos) {
	JUMP(0x240027D0);
}

NAKED CKBehaviorIO* CKBehavior::GetOutput(int pos) {
	JUMP(0x240027F8);
}

NAKED int CKBehavior::GetOutputCount() {
	JUMP(0x2400278E);
}

NAKED int CKBehavior::GetOutputPosition(CKBehaviorIO* pbio) {
	JUMP(0x24002877);
}

NAKED int CKBehavior::AddOutput(CKSTRING name) {
	JUMP(0x2400276B);
}

NAKED CKBehaviorIO* CKBehavior::ReplaceOutput(int pos, CKBehaviorIO* io) {
	JUMP(0x240028A3);
}

NAKED CKBehaviorIO* CKBehavior::CreateOutput(CKSTRING name) {
	JUMP(0x24002815);
}

NAKED void CKBehavior::InsertOutput(int pos, CKBehaviorIO* io) {
	UNDEFINED;
}

NAKED void CKBehavior::ActivateInput(int pos, CKBOOL active) {
	JUMP(0x240028B8);
}

NAKED CKBOOL CKBehavior::IsInputActive(int pos) {
	JUMP(0x240028EA);
}

NAKED CKBehaviorIO* CKBehavior::RemoveInput(int pos) {
	JUMP(0x24002A2C);
}

NAKED CKERROR CKBehavior::DeleteInput(int pos) {
	JUMP(0x2400293A);
}

NAKED CKBehaviorIO* CKBehavior::GetInput(int pos) {
	JUMP(0x240029E3);
}

NAKED int CKBehavior::GetInputCount() {
	JUMP(0x24002962);
}

NAKED int CKBehavior::GetInputPosition(CKBehaviorIO* pbio) {
	JUMP(0x24002A00);
}

NAKED int CKBehavior::AddInput(CKSTRING name) {
	JUMP(0x24002917);
}

NAKED CKBehaviorIO* CKBehavior::ReplaceInput(int pos, CKBehaviorIO* io) {
	JUMP(0x2400296C);
}

NAKED CKBehaviorIO* CKBehavior::CreateInput(CKSTRING name) {
	JUMP(0x24002981);
}

NAKED void CKBehavior::InsertInput(int pos, CKBehaviorIO* io) {
	UNDEFINED;
}

NAKED CKERROR CKBehavior::ExportInputParameter(CKParameterIn* p) {
	JUMP(0x24002DE7);
}

NAKED CKParameterIn* CKBehavior::CreateInputParameter(CKSTRING name, CKParameterType type) {
	JUMP(0x24002D03);
}

NAKED CKParameterIn* CKBehavior::CreateInputParameter(CKSTRING name, CKGUID guid) {
	JUMP(0x24002D2E);
}

NAKED CKParameterIn* CKBehavior::InsertInputParameter(int pos, CKSTRING name, CKParameterType type) {
	JUMP(0x24002D9E);
}

NAKED void CKBehavior::InsertInputParameter(int pos, CKParameterIn* in) {
	UNDEFINED;
}

NAKED void CKBehavior::AddInputParameter(CKParameterIn* in) {
	JUMP(0x24002D58);
}

NAKED int CKBehavior::GetInputParameterPosition(CKParameterIn*) {
	JUMP(0x24002E0E);
}

NAKED CKParameterIn* CKBehavior::GetInputParameter(int pos) {
	JUMP(0x24002E3A);
}

NAKED CKParameterIn* CKBehavior::RemoveInputParameter(int pos) {
	JUMP(0x24002E57);
}

NAKED CKParameterIn* CKBehavior::ReplaceInputParameter(int pos, CKParameterIn* param) {
	JUMP(0x24002D81);
}

NAKED int CKBehavior::GetInputParameterCount() {
	JUMP(0x24002E87);
}

NAKED CKERROR CKBehavior::GetInputParameterValue(int pos, void* buf) {
	JUMP(0x24002E91);
}

NAKED void* CKBehavior::GetInputParameterReadDataPtr(int pos) {
	JUMP(0x24002F01);
}

NAKED CKObject* CKBehavior::GetInputParameterObject(int pos) {
	JUMP(0x24002EC3);
}

NAKED CKBOOL CKBehavior::IsInputParameterEnabled(int pos) {
	JUMP(0x24002CDC);
}

NAKED void CKBehavior::EnableInputParameter(int pos, CKBOOL enable) {
	JUMP(0x24002CBB);
}

NAKED CKERROR CKBehavior::ExportOutputParameter(CKParameterOut* p) {
	JUMP(0x240030BF);
}

NAKED CKParameterOut* CKBehavior::CreateOutputParameter(CKSTRING name, CKParameterType type) {
	JUMP(0x24002F78);
}

NAKED CKParameterOut* CKBehavior::CreateOutputParameter(CKSTRING name, CKGUID guid) {
	JUMP(0x24002F4E);
}

NAKED CKParameterOut* CKBehavior::InsertOutputParameter(int pos, CKSTRING name, CKParameterType type) {
	JUMP(0x24003054);
}

NAKED void CKBehavior::InsertOutputParameter(int pos, CKParameterOut* p) {
	UNDEFINED;
}

NAKED CKParameterOut* CKBehavior::GetOutputParameter(int pos) {
	JUMP(0x24002FD1);
}

NAKED int CKBehavior::GetOutputParameterPosition(CKParameterOut*) {
	JUMP(0x24002FEE);
}

NAKED CKParameterOut* CKBehavior::ReplaceOutputParameter(int pos, CKParameterOut* p) {
	JUMP(0x240030A2);
}

NAKED CKParameterOut* CKBehavior::RemoveOutputParameter(int pos) {
	JUMP(0x2400301A);
}

NAKED void CKBehavior::AddOutputParameter(CKParameterOut* out) {
	JUMP(0x24002FA3);
}

NAKED int CKBehavior::GetOutputParameterCount() {
	JUMP(0x2400304A);
}

NAKED CKERROR CKBehavior::GetOutputParameterValue(int pos, void* buf) {
	JUMP(0x2400310A);
}

NAKED CKERROR CKBehavior::SetOutputParameterValue(int pos, const void* buf, int size) {
	JUMP(0x240030E6);
}

NAKED void* CKBehavior::GetOutputParameterWriteDataPtr(int pos) {
	JUMP(0x2400312C);
}

NAKED CKERROR CKBehavior::SetOutputParameterObject(int pos, CKObject* obj) {
	JUMP(0x24003176);
}

NAKED CKObject* CKBehavior::GetOutputParameterObject(int pos) {
	JUMP(0x24003143);
}

NAKED CKBOOL CKBehavior::IsOutputParameterEnabled(int pos) {
	JUMP(0x24002F33);
}

NAKED void CKBehavior::EnableOutputParameter(int pos, CKBOOL enable) {
	JUMP(0x24002F18);
}

NAKED void CKBehavior::SetInputParameterDefaultValue(CKParameterIn* pin, CKParameter* plink) {
	JUMP(0x24004456);
}

NAKED CKParameterLocal* CKBehavior::CreateLocalParameter(CKSTRING name, CKParameterType type) {
	JUMP(0x24002AD6);
}

NAKED CKParameterLocal* CKBehavior::CreateLocalParameter(CKSTRING name, CKGUID guid) {
	JUMP(0x24002B01);
}

NAKED CKParameterLocal* CKBehavior::GetLocalParameter(int pos) {
	JUMP(0x24002B59);
}

NAKED CKParameterLocal* CKBehavior::RemoveLocalParameter(int pos) {
	JUMP(0x24002BA2);
}

NAKED void CKBehavior::AddLocalParameter(CKParameterLocal* loc) {
	JUMP(0x24002B2B);
}

NAKED int CKBehavior::GetLocalParameterPosition(CKParameterLocal*) {
	JUMP(0x24002B76);
}

NAKED int CKBehavior::GetLocalParameterCount() {
	JUMP(0x24002BD2);
}

NAKED CKERROR CKBehavior::GetLocalParameterValue(int pos, void* buf) {
	JUMP(0x24002C00);
}

NAKED CKERROR CKBehavior::SetLocalParameterValue(int pos, const void* buf, int size) {
	JUMP(0x24002BDC);
}

NAKED void* CKBehavior::GetLocalParameterWriteDataPtr(int pos) {
	JUMP(0x24002CA4);
}

NAKED void* CKBehavior::GetLocalParameterReadDataPtr(int pos) {
	JUMP(0x24002C8B);
}

NAKED CKObject* CKBehavior::GetLocalParameterObject(int pos) {
	JUMP(0x24002C58);
}

NAKED CKERROR CKBehavior::SetLocalParameterObject(int pos, CKObject* obj) {
	JUMP(0x24002C22);
}

NAKED CKBOOL CKBehavior::IsLocalParameterSetting(int pos) {
	JUMP(0x24002A64);
}

NAKED CKParameterLocal* CKBehavior::InsertLocalParameter(int pos, CKSTRING name, CKParameterType type) {
	UNDEFINED;
}

NAKED void CKBehavior::InsertLocalParameter(int pos, CKParameterLocal* p) {
	UNDEFINED;
}

NAKED void CKBehavior::Activate(CKBOOL Active, CKBOOL breset) {
	JUMP(0x24003957);
}

NAKED CKERROR CKBehavior::AddSubBehavior(CKBehavior* cbk) {
	JUMP(0x240031AC);
}

NAKED CKBehavior* CKBehavior::RemoveSubBehavior(CKBehavior* cbk) {
	JUMP(0x2400337C);
}

NAKED CKBehavior* CKBehavior::RemoveSubBehavior(int pos) {
	JUMP(0x240032A5);
}

NAKED CKBehavior* CKBehavior::GetSubBehavior(int pos) {
	JUMP(0x240033BB);
}

NAKED int CKBehavior::GetSubBehaviorCount() {
	JUMP(0x240033DF);
}

NAKED CKERROR CKBehavior::AddSubBehaviorLink(CKBehaviorLink* cbkl) {
	JUMP(0x24003425);
}

NAKED CKBehaviorLink* CKBehavior::RemoveSubBehaviorLink(CKBehaviorLink* cbkl) {
	JUMP(0x2400344D);
}

NAKED CKBehaviorLink* CKBehavior::RemoveSubBehaviorLink(int pos) {
	JUMP(0x2400348F);
}

NAKED CKBehaviorLink* CKBehavior::GetSubBehaviorLink(int pos) {
	JUMP(0x240034D3);
}

NAKED int CKBehavior::GetSubBehaviorLinkCount() {
	JUMP(0x240034F7);
}

NAKED CKERROR CKBehavior::AddParameterOperation(CKParameterOperation* op) {
	JUMP(0x2400350B);
}

NAKED CKParameterOperation* CKBehavior::GetParameterOperation(int pos) {
	JUMP(0x2400358C);
}

NAKED CKParameterOperation* CKBehavior::RemoveParameterOperation(int pos) {
	JUMP(0x24003533);
}

NAKED CKParameterOperation* CKBehavior::RemoveParameterOperation(CKParameterOperation* op) {
	JUMP(0x2400355B);
}

NAKED int CKBehavior::GetParameterOperationCount() {
	JUMP(0x240035AF);
}

NAKED int CKBehavior::GetPriority() {
	JUMP(0x2402DC3B);
}

NAKED void CKBehavior::SetPriority(int priority) {
	JUMP(0x2400390F);
}

NAKED float CKBehavior::GetLastExecutionTime() {
	JUMP(0x24002708);
}

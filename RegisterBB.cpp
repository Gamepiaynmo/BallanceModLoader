#include "RegisterBB.h"
#include "ModLoader.h"

const CKGUID g_bmlGuid(0x3a086b4d, 0x2f4a4f01);

#define CKDLL_BEHAVIORPROTOTYPE 4
#define PLACEHOLDER 0xcdcdcdcd

CKObjectDeclaration* BBBuilder::Build() {
	CKObjectDeclaration* od = CreateCKObjectDeclaration(m_name.c_str());
	od->SetDescription(m_desc.c_str());
	od->SetCategory(m_cate.c_str());
	od->SetType(CKDLL_BEHAVIORPROTOTYPE);
	od->SetGuid(m_guid);
	od->SetAuthorGuid(m_authorGuid);
	od->SetAuthorName(m_author.c_str());
	od->SetVersion(m_version);
	od->SetCreationFunction(BuildProto());
	od->SetCompatibleClassId(m_classid);
	return od;
}

CKBehaviorPrototype* CreatePrototype(BBBuilder* builder) {
	CKBehaviorPrototype* proto = CreateCKBehaviorPrototypeRunTime(builder->m_name.c_str());
	
	for (auto& name : builder->m_ins)
		proto->DeclareInput(name.c_str());
	for (auto& name : builder->m_outs)
		proto->DeclareOutput(name.c_str());

	for (auto& pair : builder->m_pins)
		proto->DeclareInParameter(pair.first.c_str(), pair.second);
	for (auto& pair : builder->m_pouts)
		proto->DeclareOutParameter(pair.first.c_str(), pair.second);

	if (builder->m_bflags != 0)
		proto->SetBehaviorFlags(static_cast<CK_BEHAVIOR_FLAGS>(builder->m_bflags));
	proto->SetFlags(builder->m_flags);

	if (builder->m_callback != nullptr)
		proto->SetBehaviorCallbackFct(builder->m_callback, builder->m_callbackMask, builder->m_callbackParam);
	proto->SetFunction(builder->BuildFunction());

	return proto;
}

void* AllocateFunction(void* function, int size, void* replace) {
	BYTE* buffer = new BYTE[size];
	memcpy(buffer, function, size);
	for (int i = 0; i < size; i++) {
		DWORD& value = *reinterpret_cast<DWORD*>(buffer + i);
		if (value == PLACEHOLDER) {
			value = reinterpret_cast<DWORD>(replace);
			break;
		}
	}

	DWORD flags;
	VirtualProtect(buffer, size, PAGE_EXECUTE_READWRITE, &flags);
	return buffer;
}

CKBehaviorPrototype* (*CreatePrototypeAddr)(BBBuilder*) = &CreatePrototype;

NAKED CKERROR CallCreatePrototype(CKBehaviorPrototype** pproto) {
	__asm {
		push ebp;
		mov ebp, esp;
		push PLACEHOLDER;
		call CreatePrototypeAddr;
		add esp, 4;
		mov ecx, [ebp + 8];
		mov [ecx], eax;
		xor eax, eax;
		pop ebp;
		ret;
	}
	// *pproto = CreatePrototypeAddr(reinterpret_cast<BBBuilder*>(PLACEHOLDER));
	// return CK_OK;
}

CKDLL_CREATEPROTOFUNCTION BBBuilder::BuildProto() {
	return reinterpret_cast<CKDLL_CREATEPROTOFUNCTION>(AllocateFunction(&CallCreatePrototype, 0x1a, this));
}

int HookFunction(const CKBehaviorContext& behcontext, HookBuilder* builder) {
	CKBehavior* beh = behcontext.Behavior;

	for (size_t pos = 0; pos < builder->m_outpos.size(); pos++)
		beh->GetOutputParameter(pos)->CopyValue(beh->GetInputParameter(builder->m_outpos[pos])->GetRealSource());
	HookParams params(beh);
	bool cancelled = builder->m_procFunc(&params) && beh->GetOutputCount() > 1;

	beh->ActivateInput(0, FALSE);
	beh->ActivateOutput(cancelled ? 1 : 0);
	return CKBR_OK;
}

int (* HookFunctionAddr)(const CKBehaviorContext &, HookBuilder*) = &HookFunction;

NAKED int CallHookFunction(const CKBehaviorContext* behcontext) {
	__asm {
		push ebp;
		mov ebp, esp;
		push PLACEHOLDER;
		push [ebp + 8];
		call HookFunctionAddr;
		add esp, 8;
		pop ebp;
		ret;
	}
	// return HookFunctionAddr(*behcontext, reinterpret_cast<HookBuilder*>(PLACEHOLDER));
} // size 0x16

CKBEHAVIORFCT HookBuilder::BuildFunction() {
	return reinterpret_cast<CKBEHAVIORFCT>(AllocateFunction(&CallHookFunction, 0x16, this));
}

void RegisterCallback(XObjectDeclarationArray* reg, CKSTRING name, CKSTRING desc, CKGUID guid, std::function<void()> callback) {
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName(name)
		->SetDescription(desc)
		->SetGuid(guid)
		->SetProcessFunction([callback](HookParams* params) {
			callback();
			return false;
			})->Build());
}

void RegisterBBs(XObjectDeclarationArray* reg) {
	RegisterCallback(reg, "BML OnPreStartMenu", "PreStartMenu Hook.", BML_ONPRESTARTMENU_GUID, []() { ModLoader::m_instance->OnPreStartMenu(); });
	RegisterCallback(reg, "BML OnPostStartMenu", "PostStartMenu Hook.", BML_ONPOSTSTARTMENU_GUID, []() { ModLoader::m_instance->OnPostStartMenu(); });
	RegisterCallback(reg, "BML OnExitGame", "ExitGame Hook.", BML_ONEXITGAME_GUID, []() { ModLoader::m_instance->OnExitGame(); });
	RegisterCallback(reg, "BML OnPreLoadLevel", "PreLoadLevel Hook.", BML_ONPRELOADLEVEL_GUID, []() { ModLoader::m_instance->OnPreLoadLevel(); });
	RegisterCallback(reg, "BML OnPostLoadLevel", "PostLoadLevel Hook.", BML_ONPOSTLOADLEVEL_GUID, []() { ModLoader::m_instance->OnPostLoadLevel(); });
	RegisterCallback(reg, "BML OnStartLevel", "StartLevel Hook.", BML_ONSTARTLEVEL_GUID, []() { ModLoader::m_instance->OnStartLevel(); });
	RegisterCallback(reg, "BML OnPreResetLevel", "PreResetLevel Hook.", BML_ONPRERESETLEVEL_GUID, []() { ModLoader::m_instance->OnPreResetLevel(); });
	RegisterCallback(reg, "BML OnPostResetLevel", "PostResetLevel Hook.", BML_ONPOSTRESETLEVEL_GUID, []() { ModLoader::m_instance->OnPostResetLevel(); });
	RegisterCallback(reg, "BML OnPauseLevel", "PauseLevel Hook.", BML_ONPAUSELEVEL_GUID, []() { ModLoader::m_instance->OnPauseLevel(); });
	RegisterCallback(reg, "BML OnUnpauseLevel", "UnpauseLevel Hook.", BML_ONUNPAUSELEVEL_GUID, []() { ModLoader::m_instance->OnUnpauseLevel(); });
	RegisterCallback(reg, "BML OnPreExitLevel", "PreExitLevel Hook.", BML_ONPREEXITLEVEL_GUID, []() { ModLoader::m_instance->OnPreExitLevel(); });
	RegisterCallback(reg, "BML OnPostExitLevel", "PostExitLevel Hook.", BML_ONPOSTEXITLEVEL_GUID, []() { ModLoader::m_instance->OnPostExitLevel(); });
	RegisterCallback(reg, "BML OnPreNextLevel", "PreNextLevel Hook.", BML_ONPRENEXTLEVEL_GUID, []() { ModLoader::m_instance->OnPreNextLevel(); });
	RegisterCallback(reg, "BML OnPostNextLevel", "PostNextLevel Hook.", BML_ONPOSTNEXTLEVEL_GUID, []() { ModLoader::m_instance->OnPostNextLevel(); });
	RegisterCallback(reg, "BML OnDead", "Dead Hook.", BML_ONDEAD_GUID, []() { ModLoader::m_instance->OnDead(); });
	RegisterCallback(reg, "BML OnPreEndLevel", "PreEndLevel Hook.", BML_ONPREENDLEVEL_GUID, []() { ModLoader::m_instance->OnPreEndLevel(); });
	RegisterCallback(reg, "BML OnPostEndLevel", "PostEndLevel Hook.", BML_ONPOSTENDLEVEL_GUID, []() { ModLoader::m_instance->OnPostEndLevel(); });

	RegisterCallback(reg, "BML OnCounterActive", "CounterActive Hook.", BML_ONCOUNTERACTIVE_GUID, []() { ModLoader::m_instance->OnCounterActive(); });
	RegisterCallback(reg, "BML OnCounterInactive", "CounterInactive Hook.", BML_ONCOUNTERINACTIVE_GUID, []() { ModLoader::m_instance->OnCounterInactive(); });
	RegisterCallback(reg, "BML OnBallNavActive", "BallNavActive Hook.", BML_ONBALLNAVACTIVE_GUID, []() { ModLoader::m_instance->OnBallNavActive(); });
	RegisterCallback(reg, "BML OnBallNavInactive", "BallNavInactive Hook.", BML_ONBALLNAVINACTIVE_GUID, []() { ModLoader::m_instance->OnBallNavInactive(); });
	RegisterCallback(reg, "BML OnCamNavActive", "CamNavActive Hook.", BML_ONCAMNAVACTIVE_GUID, []() { ModLoader::m_instance->OnCamNavActive(); });
	RegisterCallback(reg, "BML OnCamNavInactive", "CamNavInactive Hook.", BML_ONCAMNAVINACTIVE_GUID, []() { ModLoader::m_instance->OnCamNavInactive(); });
	RegisterCallback(reg, "BML OnBallOff", "BallOff Hook.", BML_ONBALLOFF_GUID, []() { ModLoader::m_instance->OnBallOff(); });
	RegisterCallback(reg, "BML OnPreCheckpoint", "PreCheckpoint Hook.", BML_ONPRECHECKPOINT_GUID, []() { ModLoader::m_instance->OnPreCheckpointReached(); });
	RegisterCallback(reg, "BML OnPostCheckpoint", "PostCheckpoint Hook.", BML_ONPOSTCHECKPOINT_GUID, []() { ModLoader::m_instance->OnPostCheckpointReached(); });
	RegisterCallback(reg, "BML OnLevelFinish", "LevelFinish Hook.", BML_ONLEVELFINISH_GUID, []() { ModLoader::m_instance->OnLevelFinish(); });
	RegisterCallback(reg, "BML OnGameOver", "GameOver Hook.", BML_ONGAMEOVER_GUID, []() { ModLoader::m_instance->OnGameOver(); });
	RegisterCallback(reg, "BML OnExtraPoint", "ExtraPoint Hook.", BML_ONEXTRAPOINT_GUID, []() { ModLoader::m_instance->OnExtraPoint(); });
	RegisterCallback(reg, "BML OnPreSubLife", "PreSubLife Hook.", BML_ONPRESUBLIFE_GUID, []() { ModLoader::m_instance->OnPreSubLife(); });
	RegisterCallback(reg, "BML ONPostSubLife", "PostSubLife Hook.", BML_ONPOSTSUBLIFE_GUID, []() { ModLoader::m_instance->OnPostSubLife(); });
	RegisterCallback(reg, "BML OnPreLifeUp", "PreLifeUp Hook.", BML_ONPRELIFEUP_GUID, []() { ModLoader::m_instance->OnPreLifeUp(); });
	RegisterCallback(reg, "BML OnPostLifeUp", "PostLifeUp Hook.", BML_ONPOSTLIFEUP_GUID, []() { ModLoader::m_instance->OnPostLifeUp(); });

	RegisterCallback(reg, "BML ModsMenu", "Show BML Mods Menu.", BML_MODSMENU_GUID, []() { ModLoader::m_instance->OpenModsMenu(); });
}
#include "RegisterBB.h"
#include "ModLoader.h"
#include <functional>

const CKGUID g_bmlGuid(0x3a086b4d, 0x2f4a4f01);

#define CKDLL_BEHAVIORPROTOTYPE 4
#define PLACEHOLDER 0xcdcdcdcd

class HookParams {
public:
	HookParams(CKBehavior* beh) : m_beh(beh) {}

private:
	CKBehavior* m_beh;
};

class BBBuilder {
public:
	BBBuilder* SetName(CKSTRING name) { m_name = name; return this; }
	BBBuilder* SetDescription(CKSTRING desc) { m_desc = desc; return this; }
	BBBuilder* SetCategory(CKSTRING cate) { m_cate = std::string("BML/") + cate; return this; }
	BBBuilder* SetGuid(CKGUID guid) { m_guid = guid; return this; }

	BBBuilder* SetAuthor(CKSTRING author) { m_author = author; return this; }
	BBBuilder* SetAuthorGuid(CKGUID guid) { m_authorGuid = guid; return this; }
	BBBuilder* SetVersion(CKDWORD version) { m_version = version; return this; }
	BBBuilder* SetClassID(CK_CLASSID id) { m_classid = id; return this; }

	BBBuilder* SetBehaviorFlags(CKDWORD flags) { m_bflags = flags; return this; }
	BBBuilder* SetFlags(CK_BEHAVIORPROTOTYPE_FLAGS flags) { m_flags = flags; return this; }
	BBBuilder* SetFunction(CKBEHAVIORFCT function) { m_function = function; return this; }
	BBBuilder* SetCallback(CKBEHAVIORCALLBACKFCT fct, CKDWORD CallbackMask = CKCB_BEHAVIORALL, void* param = NULL)
		{ m_callback = fct; m_callbackMask = CallbackMask; m_callbackParam = param; return this; }

	BBBuilder* AddInput(CKSTRING name) { m_ins.push_back(name); return this; }
	BBBuilder* AddOutput(CKSTRING name) { m_outs.push_back(name); return this; }
	BBBuilder* AddInputParam(CKSTRING name, CKGUID type) { m_pins.push_back({ name, type }); return this; }
	BBBuilder* AddOutputParam(CKSTRING name, CKGUID type) { m_pouts.push_back({ name, type }); return this; }

	CKObjectDeclaration* Build();
	CKDLL_CREATEPROTOFUNCTION BuildProto();
	virtual CKBEHAVIORFCT BuildFunction() { return m_function; }

	std::string m_name, m_desc, m_cate, m_author = "Gamepiaynmo";
	CKGUID m_guid, m_authorGuid = g_bmlGuid;
	CKDWORD m_version = BML_MAJOR_VER << 16 | BML_MINOR_VER;
	CK_CLASSID m_classid = CKCID_BEOBJECT;
	std::vector<std::string> m_ins, m_outs;
	std::vector<std::pair<std::string, CKGUID>> m_pins, m_pouts;
	CKDWORD m_bflags = 0; CK_BEHAVIORPROTOTYPE_FLAGS m_flags = CK_BEHAVIORPROTOTYPE_NORMAL;
	CKBEHAVIORCALLBACKFCT m_callback = nullptr; CKDWORD m_callbackMask; void* m_callbackParam;
	CKBEHAVIORFCT m_function = nullptr;
};

class HookBuilder : public BBBuilder {
public:
	HookBuilder() {
		AddInput("In");
		AddOutput("Out");
		SetCategory("Hook");
	}

	HookBuilder* SetName(CKSTRING name) { m_name = name; return this; }
	HookBuilder* SetDescription(CKSTRING desc) { m_desc = desc; return this; }
	HookBuilder* SetCategory(CKSTRING cate) { m_cate = std::string("BML/") + cate; return this; }
	HookBuilder* SetGuid(CKGUID guid) { m_guid = guid; return this; }

	HookBuilder* SetCancellable() { AddOutput("Cancelled"); return this; }
	HookBuilder* AddInputParam(CKSTRING name, CKGUID type) { m_pins.push_back({ name, type }); return this; }
	HookBuilder* AddModifiableParam(CKSTRING name, CKGUID type) {
		m_outpos.push_back(m_pins.size());
		AddInputParam(name, type);
		AddOutputParam(name, type);
	}

	virtual CKBEHAVIORFCT BuildFunction() override;

	typedef std::function<bool(HookParams*)> ProcessFunction;
	HookBuilder* SetProcessFunction(ProcessFunction function) { m_procFunc = function; return this; }

	std::vector<int> m_outpos;
	ProcessFunction m_procFunc;
};

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

void RegisterBBs(XObjectDeclarationArray* reg) {
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnStartMenu")
		->SetDescription("BML Hook on Message Start Menu.")
		->SetGuid(BML_ONSTARTMENU_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnStartMenu();
			return false;
		})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnExitGame")
		->SetDescription("BML Hook on Message Exit Game.")
		->SetGuid(BML_ONEXITGAME_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnExitGame();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnLoadLevel")
		->SetDescription("BML Hook on Message Load Level.")
		->SetGuid(BML_ONLOADLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnLoadLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnStartLevel")
		->SetDescription("BML Hook on Message Start Level.")
		->SetGuid(BML_ONSTARTLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnStartLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnResetLevel")
		->SetDescription("BML Hook on Message Reset Level.")
		->SetGuid(BML_ONRESETLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnResetLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnPauseLevel")
		->SetDescription("BML Hook on Message Pause Level.")
		->SetGuid(BML_ONPAUSELEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnPauseLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnUnpauseLevel")
		->SetDescription("BML Hook on Message Unpause Level.")
		->SetGuid(BML_ONUNPAUSELEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnUnpauseLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnExitLevel")
		->SetDescription("BML Hook on Message Exit Level.")
		->SetGuid(BML_ONEXITLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnExitLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnNextLevel")
		->SetDescription("BML Hook on Message Next Level.")
		->SetGuid(BML_ONNEXTLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnNextLevel();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnDead")
		->SetDescription("BML Hook on Message Dead.")
		->SetGuid(BML_ONDEAD_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnDead();
			return false;
			})->Build());
	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML OnEndLevel")
		->SetDescription("BML Hook on Message End Level.")
		->SetGuid(BML_ONENDLEVEL_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OnEndLevel();
			return false;
			})->Build());

	CKStoreDeclaration(reg, (new HookBuilder())
		->SetName("BML ModsMenu")
		->SetDescription("Show BML Mods Menu.")
		->SetGuid(BML_MODSMENU_GUID)
		->SetProcessFunction([](HookParams* params) {
			ModLoader::m_instance->OpenModsMenu();
			return false;
		})->Build());
}
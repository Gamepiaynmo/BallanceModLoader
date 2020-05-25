#include "ScriptHelper.h"

namespace ScriptHelper {
	bool FindBB(CKBehavior* script, std::function<bool(CKBehavior*)> callback, CKSTRING name, bool hierarchically,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		int cnt = script->GetSubBehaviorCount();
		for (int i = 0; i < cnt; i++) {
			CKBehavior* beh = script->GetSubBehavior(i);
			if (hierarchically && beh->GetSubBehaviorCount() > 0) {
				if (!FindBB(beh, callback, name, hierarchically, inputCnt, outputCnt, inputParamCnt, outputParamCnt))
					return false;
			}

			auto res = beh->GetName();
			if ((!name || !strcmp(beh->GetName(), name))
				&& (inputCnt < 0 || beh->GetInputCount() == inputCnt)
				&& (outputCnt < 0 || beh->GetOutputCount() == outputCnt)
				&& (inputParamCnt < 0 || beh->GetInputParameterCount() == inputParamCnt)
				&& (outputParamCnt < 0 || beh->GetOutputParameterCount() == outputParamCnt))
				if (!callback(beh))
					return false;
		}

		return true;
	}

	CKBehavior* FindFirstBB(CKBehavior* script, CKSTRING name, bool hierarchically,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		CKBehavior* res = nullptr;
		FindBB(script, [&res](CKBehavior* beh) { res = beh; return false; }, name, hierarchically,
			inputCnt, outputCnt, inputParamCnt, outputParamCnt);
		return res;
	}

	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehavior* outBeh, int inPos, int outPos, int delay) {
		return CreateLink(script, inBeh->GetOutput(inPos), outBeh->GetInput(outPos), delay);
	}

	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehaviorIO* out, int inPos, int delay) {
		return CreateLink(script, inBeh->GetOutput(inPos), out, delay);
	}

	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehavior* outBeh, int outPos, int delay) {
		return CreateLink(script, in, outBeh->GetInput(outPos), delay);
	}

	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehaviorIO* out, int delay) {
		CKBehaviorLink* link = static_cast<CKBehaviorLink*>(script->GetCKContext()->CreateObject(CKCID_BEHAVIORLINK));
		link->SetInitialActivationDelay(delay);
		link->ResetActivationDelay();
		link->SetInBehaviorIO(in);
		link->SetOutBehaviorIO(out);
		script->AddSubBehaviorLink(link);
		return link;
	}

	CKBehavior* CreateBB(CKBehavior* script, CKGUID guid, bool target) {
		CKBehavior* beh = static_cast<CKBehavior*>(script->GetCKContext()->CreateObject(CKCID_BEHAVIOR));
		beh->InitFromGuid(guid);
		if (target) beh->UseTarget();
		script->AddSubBehavior(beh);
		return beh;
	}

	void InsertBB(CKBehavior* script, CKBehaviorLink* link, CKBehavior* beh, int inPos, int outPos) {
		CreateLink(script, beh, link->GetOutBehaviorIO(), outPos);
		link->SetOutBehaviorIO(beh->GetInput(inPos));
	}

	CKParameterLocal* CreateLocalParameter(CKBehavior* script, CKSTRING name, CKGUID type) {
		return script->CreateLocalParameter(name, type);
	}

	CKParameterLocal* CreateParamObject(CKBehavior* script, CKSTRING name, CKGUID guid, CKObject* value) {
		return CreateParamValue<CK_ID>(script, name, guid, CKOBJID(value));
	}

	CKParameterLocal* CreateParamString(CKBehavior* script, CKSTRING name, CKSTRING value) {
		CKParameterLocal* param = CreateLocalParameter(script, name, CKPGUID_STRING);
		param->SetStringValue(value);
		return param;
	}

	void SetParamObject(CKParameter* param, CKObject* value) {
		CK_ID obj = CKOBJID(value);
		SetParamValue(param, obj);
	}

	void SetParamString(CKParameter* param, CKSTRING value) {
		param->SetStringValue(value);
	}

	CKObject* GetParamObject(CKParameter* param) {
		return param->GetValueObject();
	}

	CKSTRING GetParamString(CKParameter* param) {
		return static_cast<CKSTRING>(param->GetReadDataPtr());
	}

	CKBehaviorLink* FindNextLink(CKBehavior* script, CKBehavior* beh, CKSTRING name, int inPos, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		int linkCnt = script->GetSubBehaviorLinkCount();
		for (int i = 0; i < linkCnt; i++) {
			CKBehaviorLink* link = script->GetSubBehaviorLink(i);
			CKBehaviorIO* in = link->GetInBehaviorIO();

			if (in->GetOwner() == beh && (inPos < 0 || beh->GetOutput(inPos) == in)) {
				CKBehaviorIO* out = link->GetOutBehaviorIO();
				CKBehavior* outBeh = out->GetOwner();

				if ((!name || !strcmp(outBeh->GetName(), name))
					&& (outPos < 0 || outBeh->GetInput(outPos) == out)
					&& (inputCnt < 0 || outBeh->GetInputCount() == inputCnt)
					&& (outputCnt < 0 || outBeh->GetOutputCount() == outputCnt)
					&& (inputParamCnt < 0 || outBeh->GetInputParameterCount() == inputParamCnt)
					&& (outputParamCnt < 0 || outBeh->GetOutputParameterCount() == outputParamCnt))
					return link;
			}
		}

		return nullptr;
	}

	CKBehaviorLink* FindPreviousLink(CKBehavior* script, CKBehavior* beh, CKSTRING name, int inPos, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		int linkCnt = script->GetSubBehaviorLinkCount();
		for (int i = 0; i < linkCnt; i++) {
			CKBehaviorLink* link = script->GetSubBehaviorLink(i);
			CKBehaviorIO* out = link->GetOutBehaviorIO();

			if (out->GetOwner() == beh && (outPos < 0 || beh->GetInput(outPos) == out)) {
				CKBehaviorIO* in = link->GetInBehaviorIO();
				CKBehavior* inBeh = in->GetOwner();

				if ((!name || !strcmp(inBeh->GetName(), name))
					&& (inPos < 0 || inBeh->GetOutput(inPos) == in)
					&& (inputCnt < 0 || inBeh->GetInputCount() == inputCnt)
					&& (outputCnt < 0 || inBeh->GetOutputCount() == outputCnt)
					&& (inputParamCnt < 0 || inBeh->GetInputParameterCount() == inputParamCnt)
					&& (outputParamCnt < 0 || inBeh->GetOutputParameterCount() == outputParamCnt))
					return link;
			}
		}

		return nullptr;
	}

	CKBehavior* FindNextBB(CKBehavior* script, CKBehavior* beh, CKSTRING name, int inPos, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		CKBehaviorLink* link = FindNextLink(script, beh, name, inPos, outPos, inputCnt, outputCnt, inputParamCnt, outputParamCnt);
		return link ? link->GetOutBehaviorIO()->GetOwner() : nullptr;
	}

	CKBehavior* FindPreviousBB(CKBehavior * script, CKBehavior * beh, CKSTRING name, int inPos, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		CKBehaviorLink* link = FindPreviousLink(script, beh, name, inPos, outPos, inputCnt, outputCnt, inputParamCnt, outputParamCnt);
		return link ? link->GetInBehaviorIO()->GetOwner() : nullptr;
	}

	CKBehaviorLink* FindNextLink(CKBehavior* script, CKBehaviorIO* io, CKSTRING name, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		int linkCnt = script->GetSubBehaviorLinkCount();
		for (int i = 0; i < linkCnt; i++) {
			CKBehaviorLink* link = script->GetSubBehaviorLink(i);
			CKBehaviorIO* in = link->GetInBehaviorIO();

			if (in == io) {
				CKBehaviorIO* out = link->GetOutBehaviorIO();
				CKBehavior* outBeh = out->GetOwner();

				if ((!name || !strcmp(outBeh->GetName(), name))
					&& (outPos < 0 || outBeh->GetInput(outPos) == out)
					&& (inputCnt < 0 || outBeh->GetInputCount() == inputCnt)
					&& (outputCnt < 0 || outBeh->GetOutputCount() == outputCnt)
					&& (inputParamCnt < 0 || outBeh->GetInputParameterCount() == inputParamCnt)
					&& (outputParamCnt < 0 || outBeh->GetOutputParameterCount() == outputParamCnt))
					return link;
			}
		}

		return nullptr;
	}

	CKBehaviorLink* FindPreviousLink(CKBehavior* script, CKBehaviorIO* io, CKSTRING name, int inPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		int linkCnt = script->GetSubBehaviorLinkCount();
		for (int i = 0; i < linkCnt; i++) {
			CKBehaviorLink* link = script->GetSubBehaviorLink(i);
			CKBehaviorIO* out = link->GetOutBehaviorIO();

			if (out == io) {
				CKBehaviorIO* in = link->GetInBehaviorIO();
				CKBehavior* inBeh = in->GetOwner();

				if ((!name || !strcmp(inBeh->GetName(), name))
					&& (inPos < 0 || inBeh->GetOutput(inPos) == in)
					&& (inputCnt < 0 || inBeh->GetInputCount() == inputCnt)
					&& (outputCnt < 0 || inBeh->GetOutputCount() == outputCnt)
					&& (inputParamCnt < 0 || inBeh->GetInputParameterCount() == inputParamCnt)
					&& (outputParamCnt < 0 || inBeh->GetOutputParameterCount() == outputParamCnt))
					return link;
			}
		}

		return nullptr;
	}

	CKBehavior* FindNextBB(CKBehavior* script, CKBehaviorIO* io, CKSTRING name, int outPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		CKBehaviorLink* link = FindNextLink(script, io, name, outPos, inputCnt, outputCnt, inputParamCnt, outputParamCnt);
		return link ? link->GetOutBehaviorIO()->GetOwner() : nullptr;
	}

	CKBehavior* FindPreviousBB(CKBehavior* script, CKBehaviorIO* io, CKSTRING name, int inPos,
		int inputCnt, int outputCnt, int inputParamCnt, int outputParamCnt) {
		CKBehaviorLink* link = FindPreviousLink(script, io, name, inPos, inputCnt, outputCnt, inputParamCnt, outputParamCnt);
		return link ? link->GetInBehaviorIO()->GetOwner() : nullptr;
	}

	CKBehavior* FindEndOfChain(CKBehavior* script, CKBehavior* beh) {
		CKBehavior* next = nullptr;
		while (true) {
			CKBehavior* next = FindNextBB(script, beh);
			if (next) beh = next;
			else break;
		};
		return beh;
	}

	void DeleteLink(CKBehavior* script, CKBehaviorLink* link) {
		static CKBehavior* nop = nullptr;
		static CKBehaviorIO* nopin = nullptr, * nopout = nullptr;
		if (!nop) {
			nop = static_cast<CKBehavior*>(script->GetCKContext()->CreateObject(CKCID_BEHAVIOR));
			nop->InitFromGuid(CKGUID(0x302561c4, 0xd282980));
			nopin = nop->GetInput(0);
			nopout = nop->GetOutput(0);
		}

		link->SetInBehaviorIO(nopout);
		link->SetOutBehaviorIO(nopin);
	}

	void DeleteBB(CKBehavior* script, CKBehavior* beh) {
		beh->Activate(false);
		int linkCnt = script->GetSubBehaviorLinkCount();
		for (int i = 0; i < linkCnt; i++) {
			CKBehaviorLink* link = script->GetSubBehaviorLink(i);
			if (link->GetInBehaviorIO()->GetOwner() == beh
				|| link->GetOutBehaviorIO()->GetOwner() == beh)
				DeleteLink(script, link);
		}
	}

}
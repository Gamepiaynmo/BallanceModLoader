#pragma once

#include "virtools/CKAll.h"
#include <functional>

namespace ScriptHelper {
	BML_EXPORT bool FindBB(CKBehavior* script, std::function<bool(CKBehavior*)> callback, CKSTRING name = nullptr, bool hierarchically = false,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	BML_EXPORT CKBehavior* FindFirstBB(CKBehavior* script, CKSTRING name = nullptr, bool hierarchically = false,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	BML_EXPORT CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehavior* outBeh, int inPos = 0, int outPos = 0, int delay = 0);
	BML_EXPORT CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehaviorIO* out, int inPos = 0, int delay = 0);
	BML_EXPORT CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehavior* outBeh, int outPos = 0, int delay = 0);
	BML_EXPORT CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehaviorIO* out, int delay = 0);

	BML_EXPORT CKBehavior* CreateBB(CKBehavior* script, CKGUID guid, bool target = false);
	BML_EXPORT void InsertBB(CKBehavior* script, CKBehaviorLink* link, CKBehavior* beh, int inPos = 0, int outPos = 0);

	BML_EXPORT CKParameterLocal* CreateLocalParameter(CKBehavior* script, CKSTRING name, CKGUID type);
	BML_EXPORT CKParameterLocal* CreateParamObject(CKBehavior* script, CKSTRING name, CKGUID guid, CKObject* value);
	BML_EXPORT CKParameterLocal* CreateParamString(CKBehavior* script, CKSTRING name, CKSTRING value);
	template<typename T>
	CKParameterLocal* CreateParamValue(CKBehavior* script, CKSTRING name, CKGUID guid, T value) {
		CKParameterLocal* param = CreateLocalParameter(script, name, guid);
		param->SetValue(&value, sizeof(T));
		return param;
	}

	BML_EXPORT void SetParamObject(CKParameter* param, CKObject* value);
	BML_EXPORT void SetParamString(CKParameter* param, CKSTRING value);
	template<typename T>
	void SetParamValue(CKParameter* param, T value) {
		param->SetValue(&value, sizeof(T));
	}

	BML_EXPORT CKObject* GetParamObject(CKParameter* param);
	BML_EXPORT CKSTRING GetParamString(CKParameter* param);
	template<typename T>
	T GetParamValue(CKParameter* param) {
		T res;
		param->GetValue(&res);
		return res;
	}

	BML_EXPORT CKBehaviorLink* FindNextLink(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	BML_EXPORT CKBehaviorLink* FindPreviousLink(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	BML_EXPORT CKBehavior* FindNextBB(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	BML_EXPORT CKBehavior* FindPreviousBB(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	BML_EXPORT CKBehaviorLink* FindNextLink(CKBehavior* script, CKBehaviorIO* io, CKSTRING name = nullptr, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	BML_EXPORT CKBehaviorLink* FindPreviousLink(CKBehavior* script, CKBehaviorIO* io, CKSTRING name = nullptr, int inPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	BML_EXPORT CKBehavior* FindNextBB(CKBehavior* script, CKBehaviorIO* io, CKSTRING name = nullptr, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	BML_EXPORT CKBehavior* FindPreviousBB(CKBehavior* script, CKBehaviorIO* io, CKSTRING name = nullptr, int inPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	BML_EXPORT CKBehavior* FindEndOfChain(CKBehavior* script, CKBehavior* beh);

	BML_EXPORT void DeleteLink(CKBehavior* script, CKBehaviorLink* link);
	BML_EXPORT void DeleteBB(CKBehavior* script, CKBehavior* beh);
};
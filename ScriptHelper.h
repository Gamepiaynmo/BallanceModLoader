#pragma once

#include "virtools/CKAll.h"
#include <functional>

namespace ScriptHelper {
	bool FindBB(CKBehavior* script, std::function<bool(CKBehavior*)> callback, CKSTRING name = nullptr, bool hierarchically = true,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	CKBehavior* FindFirstBB(CKBehavior* script, CKSTRING name = nullptr, bool hierarchically = true,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehavior* outBeh, int inPos = 0, int outPos = 0);
	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehavior* inBeh, CKBehaviorIO* out, int inPos = 0);
	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehavior* outBeh, int outPos = 0);
	CKBehaviorLink* CreateLink(CKBehavior* script, CKBehaviorIO* in, CKBehaviorIO* out);

	CKBehavior* CreateBB(CKBehavior* script, CKGUID guid, bool target = false);
	void InsertBB(CKBehavior* script, CKBehaviorLink* link, CKBehavior* beh, int inPos = 0, int outPos = 0);

	CKParameterLocal* CreateLocalParameter(CKBehavior* script, CKSTRING name, CKGUID type);
	CKParameter* CreateParamObject(CKBehavior* script, CKGUID guid, CKSTRING name, CKObject* value);
	CKParameter* CreateParamString(CKBehavior* script, CKSTRING name, CKSTRING value);
	template<typename T>
	CKParameter* CreateParamValue(CKBehavior* script, CKGUID guid, CKSTRING name, T value) {
		CKParameter* param = CreateLocalParameter(script, name, guid);
		param->SetValue(&value, sizeof(T));
		return param;
	}

	void SetParamObject(CKParameter* param, CKObject* value);
	void SetParamString(CKParameter* param, CKSTRING value);
	template<typename T>
	void SetParamValue(CKParameter* param, T value) {
		param->SetValue(&value, sizeof(T));
	}

	CKBehaviorLink* FindNextLink(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	CKBehaviorLink* FindPreviousLink(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	CKBehavior* FindNextBB(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);
	CKBehavior* FindPreviousBB(CKBehavior* script, CKBehavior* beh, CKSTRING name = nullptr, int inPos = -1, int outPos = -1,
		int inputCnt = -1, int outputCnt = -1, int inputParamCnt = -1, int outputParamCnt = -1);

	CKBehavior* FindEndOfChain(CKBehavior* script, CKBehavior* beh);

	void DeleteLink(CKBehavior* script, CKBehaviorLink* link);
	void DeleteBB(CKBehavior* script, CKBehavior* beh);
};
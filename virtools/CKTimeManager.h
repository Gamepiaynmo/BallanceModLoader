#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

typedef enum CK_FRAMERATE_LIMITS
{
	CK_RATE_NOP = 0x00000000,
	CK_BEHRATE_SYNC = 0x00000001,	// Behavioral Rate is synchronized to frame rate
	CK_BEHRATE_LIMIT = 0x00000004,	// Behavioral Rate is limited to a maximum value (see CKTimeManager::SetBehavioralRateLimit)
	CK_BEHRATE_MASK = 0x0000000F,	// Mask for values concerning behavioral rate

	CK_FRAMERATE_SYNC = 0x00000010,	// Frame Rate is synchronized to screen refresh rate (Render function will wait for vertical blank signal)
	CK_FRAMERATE_FREE = 0x00000020,	// Frame Rate is free. Rendering occurs at the maximum possible rate.
	CK_FRAMERATE_LIMIT = 0x00000040,	// Frame Rate is limited to a maximum value (see CKTimeManager::SetFrameRateLimit)
	CK_FRAMERATE_MASK = 0x000000F0,	// Mask for values concerning frame rate
} CK_FRAMERATE_LIMITS;

class BML_EXPORT VxTimeProfiler {
public:
	void Reset();
	float Current();
	float Split() {
		float c = Current();
		Reset();
		return c;
	}

protected:
	VxTimeProfiler() {};
	~VxTimeProfiler() {};
};

class BML_EXPORT CKTimeManager : public CKBaseManager {
public:
	CKDWORD GetMainTickCount();
	float GetTime();
	float GetLastDeltaTime();
	float GetLastDeltaTimeFree();
	float GetAbsoluteTime();
	void SetTimeScaleFactor(float mulfactor);
	float GetTimeScaleFactor();
	CKDWORD GetLimitOptions();
	float GetFrameRateLimit();
	float GetBehavioralRateLimit();
	float GetMinimumDeltaTime();
	float GetMaximumDeltaTime();
	void ChangeLimitOptions(CK_FRAMERATE_LIMITS FpsOptions, CK_FRAMERATE_LIMITS BehOptions = CK_RATE_NOP);
	void SetFrameRateLimit(float FRLimit);
	void SetBehavioralRateLimit(float BRLimit);
	void SetMinimumDeltaTime(float DtMin);
	void SetMaximumDeltaTime(float DtMax);
	void SetLastDeltaTime(float DtSet);
	void SetLastDeltaTimeFree(float DtSet);
	void SetAbsoluteTime(float time);
	void SetMainTickCount(CKDWORD tick);
	void GetTimeToWaitForLimits(float& TimeBeforeRender, float& TimeBeforeBeh);
	void ResetChronos(CKBOOL RenderChrono, CKBOOL BehavioralChrono);

protected:
	CKTimeManager() {};
	~CKTimeManager() {};
};
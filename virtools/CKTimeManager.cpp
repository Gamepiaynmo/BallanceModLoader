#include "CKTimeManager.h"

NAKED void VxTimeProfiler::Reset() {
	JUMP(0x2428F490);
}

NAKED float VxTimeProfiler::Current() {
	JUMP(0x24284970);
}


CKDWORD CKTimeManager::GetMainTickCount() {
	RETURN_MEM(0x28, CKDWORD);
}

float CKTimeManager::GetTime() {
	return GET_MEMPTR(0x90, VxTimeProfiler)->Current();
}

float CKTimeManager::GetLastDeltaTime() {
	RETURN_MEM(0x38, float);
}

float CKTimeManager::GetLastDeltaTimeFree() {
	RETURN_MEM(0xa0, float);
}

float CKTimeManager::GetAbsoluteTime() {
	RETURN_MEM(0x34, float);
}

void CKTimeManager::SetTimeScaleFactor(float mulfactor) {
	SET_MEM(0x5c, float, mulfactor);
}

float CKTimeManager::GetTimeScaleFactor() {
	RETURN_MEM(0x5c, float);
}

CKDWORD CKTimeManager::GetLimitOptions() {
	RETURN_MEM(0x4c, CKDWORD);
}

float CKTimeManager::GetFrameRateLimit() {
	RETURN_MEM(0x3c, float);
}

float CKTimeManager::GetBehavioralRateLimit() {
	RETURN_MEM(0x40, float);
}

float CKTimeManager::GetMinimumDeltaTime() {
	RETURN_MEM(0x48, float);
}

float CKTimeManager::GetMaximumDeltaTime() {
	RETURN_MEM(0x48, float);
}

NAKED void CKTimeManager::ChangeLimitOptions(CK_FRAMERATE_LIMITS FpsOptions, CK_FRAMERATE_LIMITS BehOptions) {
	JUMP(0x24017E47);
}

NAKED void CKTimeManager::SetFrameRateLimit(float FRLimit) {
	JUMP(0x24017E70);
}

NAKED void CKTimeManager::SetBehavioralRateLimit(float BRLimit) {
	JUMP(0x24017E98);
}

NAKED void CKTimeManager::SetMinimumDeltaTime(float DtMin) {
	JUMP(0x24017EDB);
}

NAKED void CKTimeManager::SetMaximumDeltaTime(float DtMax) {
	JUMP(0x24017EC0);
}

void CKTimeManager::SetLastDeltaTime(float DtSet) {
	SET_MEM(0x38, float, DtSet);
}

void CKTimeManager::SetLastDeltaTimeFree(float DtSet) {
	SET_MEM(0xa0, float, DtSet);
}

void CKTimeManager::SetAbsoluteTime(float time) {
	SET_MEM(0x34, float, time);
}

void CKTimeManager::SetMainTickCount(CKDWORD tick) {
	SET_MEM(0x28, CKDWORD, tick);
}

NAKED void CKTimeManager::GetTimeToWaitForLimits(float& TimeBeforeRender, float& TimeBeforeBeh) {
	JUMP(0x24017EF6);
}

NAKED void CKTimeManager::ResetChronos(CKBOOL RenderChrono, CKBOOL BehavioralChrono) {
	JUMP(0x24017F49);
}
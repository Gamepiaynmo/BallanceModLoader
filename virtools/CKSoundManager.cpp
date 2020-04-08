#include "CKSoundManager.h"

NAKED void CKSoundManager::SetListener(CK3dEntity* listener) {
	JUMP(0x24017A7A);
}

NAKED CK3dEntity* CKSoundManager::GetListener() {
	JUMP(0x24017AAD);
}

NAKED void CKSoundManager::SetStreamedBufferSize(CKDWORD bsize) {
	JUMP(0x24017ADF);
}

NAKED CKDWORD CKSoundManager::GetStreamedBufferSize() {
	JUMP(0x24017AE9);
}

NAKED SoundMinion* CKSoundManager::CreateMinion(CKSOUNDHANDLE source, float minimumdelay) {
	JUMP(0x24017AED);
}

NAKED void CKSoundManager::ReleaseMinions() {
	JUMP(0x24017BF9);
}

NAKED void CKSoundManager::PauseMinions() {
	JUMP(0x24017BB3);
}

NAKED void CKSoundManager::ResumeMinions() {
	JUMP(0x24017BD5);
}

NAKED void CKSoundManager::ProcessMinions() {
	JUMP(0x24017C48);
}

NAKED CKERROR CKSoundManager::SequenceDeleted(CK_ID* objids, int count) {
	JUMP(0x24017CA1);
}

NAKED CKERROR CKSoundManager::PostClearAll() {
	JUMP(0x24017CA9);
}

NAKED CKDWORD CKSoundManager::GetValidFunctionsMask() {
	JUMP(0x24017D1D);
}

NAKED void CKSoundManager::RegisterAttribute() {
	JUMP(0x2402141A);
}

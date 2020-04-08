#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

typedef void* CKSOUNDHANDLE;

struct SoundMinion {
	CKSOUNDHANDLE m_Source;
	CKSOUNDHANDLE m_OriginalSource;
	CK_ID m_Entity;
	CK_ID m_OriginalSound;
	VxVector m_Position;
	VxVector m_Direction;
	VxVector m_OldPosition;
	float m_TimeStamp;
};

class BML_EXPORT CKSoundManager : public CKBaseManager {
public:
	void SetListener(CK3dEntity* listener);
	CK3dEntity* GetListener();
	void SetStreamedBufferSize(CKDWORD bsize);
	CKDWORD GetStreamedBufferSize();
	SoundMinion* CreateMinion(CKSOUNDHANDLE source, float minimumdelay = 0.0f);
	void ReleaseMinions();
	void PauseMinions();
	void ResumeMinions();
	void ProcessMinions();
	CKERROR SequenceDeleted(CK_ID* objids, int count);
	CKERROR PostClearAll();
	CKDWORD GetValidFunctionsMask();
	void RegisterAttribute();

protected:
	CKSoundManager() {};
	~CKSoundManager() {};
};
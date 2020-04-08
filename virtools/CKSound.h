#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

class BML_EXPORT CKSound : public CKBeObject {
public:
	CK_SOUND_SAVEOPTIONS GetSaveOptions();
	void SetSaveOptions(CK_SOUND_SAVEOPTIONS Options);

protected:
	CKSound() {};
	~CKSound() {};
};

class BML_EXPORT CKMidiSound : public CKSound {
public:
	CKERROR SetSoundFileName(CKSTRING filename);
	CKSTRING GetSoundFileName();
	CKDWORD GetCurrentPos();
	CKERROR Play();
	CKERROR Stop();
	CKERROR Pause(CKBOOL pause = TRUE);
	CKBOOL IsPlaying();
	CKBOOL IsPaused();

protected:
	CKMidiSound() {};
	~CKMidiSound() {};
};

typedef void* CKSOUNDHANDLE;
class CKSoundReader;
struct CKWaveFormat {
	WORD  wFormatTag;
	WORD  nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD  nBlockAlign;
	WORD  wBitsPerSample;
	WORD  cbSize;
};

class BML_EXPORT CKWaveSound : public CKSound {
public:
	CKSOUNDHANDLE PlayMinion(CKBOOL Background = TRUE, CK3dEntity* Ent = NULL, VxVector* Position = NULL, VxVector* Direction = NULL, float MinDelay = 0.0f, float gain = 1.0f);
	CKERROR SetSoundFileName(const CKSTRING FileName);
	CKSTRING GetSoundFileName();
	int GetSoundLength();
	CKERROR GetSoundFormat(CKWaveFormat& Format);
	CK_WAVESOUND_TYPE GetType();
	void SetType(CK_WAVESOUND_TYPE Type);
	CKDWORD GetState();
	void SetState(CKDWORD State);
	void SetPriority(float Priority);
	float GetPriority();
	void SetLoopMode(CKBOOL Enabled);
	CKBOOL GetLoopMode();
	CKERROR SetFileStreaming(CKBOOL Enabled, BOOL RecreateSound = FALSE);
	CKBOOL GetFileStreaming();
	void Play(float FadeIn = 0, float FinalGain = 1.0f);
	void Resume();
	void Rewind();
	void Stop(float FadeOut = 0);
	void Pause();	
	CKBOOL IsPlaying();
	CKBOOL IsPaused();
	void SetGain(float Gain);
	float GetGain();
	void SetPitch(float Rate);
	float GetPitch();
	void SetPan(float Pan);
	float GetPan();
	CKSOUNDHANDLE GetSource();
	void PositionSound(CK3dEntity* Object, VxVector* Position = NULL, VxVector* Direction = NULL, CKBOOL Commit = FALSE);
	CK3dEntity* GetAttachedEntity();
	void GetPosition(VxVector& Pos);
	void GetDirection(VxVector& Dir);
	void GetSound3DInformation(VxVector& Pos, VxVector& Dir, float& DistanceFromListener);
	void SetCone(float InAngle, float OutAngle, float OutsideGain);
	void GetCone(float* InAngle, float* OutAngle, float* OutsideGain);
	void SetMinMaxDistance(float MinDistance, float MaxDistance, CKDWORD MaxDistanceBehavior = 1);
	void GetMinMaxDistance(float* MinDistance, float* MaxDistance, CKDWORD* MaxDistanceBehavior);
	void SetVelocity(VxVector& Pos);
	void GetVelocity(VxVector& Pos);
	void SetOrientation(VxVector& Dir, VxVector& Up);
	void GetOrientation(VxVector& Dir, VxVector& Up);
	CKERROR WriteData(BYTE* Buffer, int Buffersize);
	CKERROR Lock(CKDWORD WriteCursor, CKDWORD NumBytes, void** Ptr1, CKDWORD* Bytes1, void** Ptr2, CKDWORD* Bytes2, CK_WAVESOUND_LOCKMODE Flags);
	CKERROR Unlock(void* Ptr1, CKDWORD Bytes1, void* Ptr2, CKDWORD Bytes2);
	CKDWORD GetPlayPosition();
	int GetPlayedMs();
	CKERROR Create(CKBOOL FileStreaming, CKSTRING Filename);
	CKERROR Create(CK_WAVESOUND_TYPE Type, CKWaveFormat* Format, int Size);
	CKERROR SetReader(CKSoundReader* Reader);
	CKSoundReader* GetReader();
	void SetDataToRead(int Size);
	CKERROR Recreate(BOOL Safe = FALSE);
	void Release();
	CKERROR TryRecreate();
	void UpdatePosition(float deltaT);
	void UpdateFade();
	CKERROR WriteDataFromReader();
	void FillWithBlanks(CKBOOL IncBf = FALSE);
	void InternalStop();

protected:
	CKWaveSound() {};
	~CKWaveSound() {};
};
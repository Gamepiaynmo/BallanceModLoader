#include "CKSound.h"

NAKED CK_SOUND_SAVEOPTIONS CKSound::GetSaveOptions() {
	JUMP(0x24003B62);
}

NAKED void CKSound::SetSaveOptions(CK_SOUND_SAVEOPTIONS Options) {
	JUMP(0x24018678);
}


NAKED CKERROR CKMidiSound::SetSoundFileName(CKSTRING filename) {
	JUMP(0x240182F6);
}

NAKED CKSTRING CKMidiSound::GetSoundFileName() {
	JUMP(0x2402DC3B);
}

NAKED CKDWORD CKMidiSound::GetCurrentPos() {
	JUMP(0x240183F3);
}

NAKED CKERROR CKMidiSound::Play() {
	JUMP(0x240183DA);
}

NAKED CKERROR CKMidiSound::Stop() {
	JUMP(0x240183C1);
}

NAKED CKERROR CKMidiSound::Pause(CKBOOL pause) {
	JUMP(0x24018391);
}

NAKED CKBOOL CKMidiSound::IsPlaying() {
	JUMP(0x2401842C);
}

NAKED CKBOOL CKMidiSound::IsPaused() {
	JUMP(0x24018442);
}


NAKED CKSOUNDHANDLE CKWaveSound::PlayMinion(CKBOOL Background, CK3dEntity* Ent, VxVector* Position, VxVector* Direction, float MinDelay, float gain) {
	JUMP(0x240189C7);
}

NAKED CKERROR CKWaveSound::SetSoundFileName(const CKSTRING FileName) {
	JUMP(0x24018B70);
}

NAKED CKSTRING CKWaveSound::GetSoundFileName() {
	JUMP(0x2402DC3B);
}

NAKED int CKWaveSound::GetSoundLength() {
	JUMP(0x24018C07);
}

NAKED CKERROR CKWaveSound::GetSoundFormat(CKWaveFormat& Format) {
	JUMP(0x24018BEF);
}

NAKED CK_WAVESOUND_TYPE CKWaveSound::GetType() {
	JUMP(0x24018D32);
}

NAKED void CKWaveSound::SetType(CK_WAVESOUND_TYPE Type) {
	JUMP(0x24018CE0);
}

NAKED CKDWORD CKWaveSound::GetState() {
	JUMP(0x2402D41D);
}

NAKED void CKWaveSound::SetState(CKDWORD State) {
	JUMP(0x24019B6B);
}

NAKED void CKWaveSound::SetPriority(float Priority) {
	JUMP(0x24018DDF);
}

NAKED float CKWaveSound::GetPriority() {
	JUMP(0x24018E24);
}

NAKED void CKWaveSound::SetLoopMode(CKBOOL Enabled) {
	JUMP(0x24018E73);
}

NAKED CKBOOL CKWaveSound::GetLoopMode() {
	JUMP(0x24018EBE);
}

NAKED CKERROR CKWaveSound::SetFileStreaming(CKBOOL Enabled, BOOL RecreateSound) {
	JUMP(0x24018EC5);
}

NAKED CKBOOL CKWaveSound::GetFileStreaming() {
	JUMP(0x24018F15);
}

NAKED void CKWaveSound::Play(float FadeIn, float FinalGain) {
	JUMP(0x24018FAE);
}

NAKED void CKWaveSound::Resume() {
	JUMP(0x24019162);
}

NAKED void CKWaveSound::Rewind() {
	JUMP(0x240191B7);
}

NAKED void CKWaveSound::Stop(float FadeOut) {
	JUMP(0x24019281);
}

NAKED void CKWaveSound::Pause() {
	JUMP(0x240190D3);
}

NAKED CKBOOL CKWaveSound::IsPlaying() {
	JUMP(0x24019309);
}

NAKED CKBOOL CKWaveSound::IsPaused() {
	JUMP(0x2401931F);
}

NAKED void CKWaveSound::SetGain(float Gain) {
	JUMP(0x240196D1);
}

NAKED float CKWaveSound::GetGain() {
	JUMP(0x2401972F);
}

NAKED void CKWaveSound::SetPitch(float Rate) {
	JUMP(0x24018F1E);
}

NAKED float CKWaveSound::GetPitch() {
	JUMP(0x24018F62);
}

NAKED void CKWaveSound::SetPan(float Pan) {
	JUMP(0x24019743);
}

NAKED float CKWaveSound::GetPan() {
	JUMP(0x2401978A);
}

NAKED CKSOUNDHANDLE CKWaveSound::GetSource() {
	JUMP(0x2401AE62);
}

NAKED void CKWaveSound::PositionSound(CK3dEntity* Object, VxVector* Position, VxVector* Direction, CKBOOL Commit) {
	JUMP(0x24019A1A);
}

NAKED CK3dEntity* CKWaveSound::GetAttachedEntity() {
	JUMP(0x24019B02);
}

NAKED void CKWaveSound::GetPosition(VxVector& Pos) {
	JUMP(0x24019B0E);
}

NAKED void CKWaveSound::GetDirection(VxVector& Dir) {
	JUMP(0x24019B1F);
}

NAKED void CKWaveSound::GetSound3DInformation(VxVector& Pos, VxVector& Dir, float& DistanceFromListener) {
	JUMP(0x24019A68);
}

NAKED void CKWaveSound::SetCone(float InAngle, float OutAngle, float OutsideGain) {
	JUMP(0x240197D9);
}

NAKED void CKWaveSound::GetCone(float* InAngle, float* OutAngle, float* OutsideGain) {
	JUMP(0x24019820);
}

NAKED void CKWaveSound::SetMinMaxDistance(float MinDistance, float MaxDistance, CKDWORD MaxDistanceBehavior) {
	JUMP(0x2401986D);
}

NAKED void CKWaveSound::GetMinMaxDistance(float* MinDistance, float* MaxDistance, CKDWORD* MaxDistanceBehavior) {
	JUMP(0x240198B6);
}

NAKED void CKWaveSound::SetVelocity(VxVector& Pos) {
	JUMP(0x24019904);
}

NAKED void CKWaveSound::GetVelocity(VxVector& Pos) {
	JUMP(0x24019946);
}

NAKED void CKWaveSound::SetOrientation(VxVector& Dir, VxVector& Up) {
	JUMP(0x24019986);
}

NAKED void CKWaveSound::GetOrientation(VxVector& Dir, VxVector& Up) {
	JUMP(0x240199D1);
}

NAKED CKERROR CKWaveSound::WriteData(BYTE* Buffer, int Buffersize) {
	JUMP(0x24019328);
}

NAKED CKERROR CKWaveSound::Lock(CKDWORD WriteCursor, CKDWORD NumBytes, void** Ptr1, CKDWORD* Bytes1, void** Ptr2, CKDWORD* Bytes2, CK_WAVESOUND_LOCKMODE Flags) {
	JUMP(0x24018966);
}

NAKED CKERROR CKWaveSound::Unlock(void* Ptr1, CKDWORD Bytes1, void* Ptr2, CKDWORD Bytes2) {
	JUMP(0x2401899B);
}

NAKED CKDWORD CKWaveSound::GetPlayPosition() {
	JUMP(0x24018D49);
}

NAKED int CKWaveSound::GetPlayedMs() {
	JUMP(0x24018D5F);
}

NAKED CKERROR CKWaveSound::Create(CKBOOL FileStreaming, CKSTRING Filename) {
	JUMP(0x24018889);
}

NAKED CKERROR CKWaveSound::Create(CK_WAVESOUND_TYPE Type, CKWaveFormat* Format, int Size) {
	JUMP(0x240188BC);
}

NAKED CKERROR CKWaveSound::SetReader(CKSoundReader* Reader) {
	JUMP(0x24018915);
}

NAKED CKSoundReader* CKWaveSound::GetReader() {
	JUMP(0x24018952);
}

NAKED void CKWaveSound::SetDataToRead(int Size) {
	JUMP(0x24018959);
}

NAKED CKERROR CKWaveSound::Recreate(BOOL Safe) {
	JUMP(0x2401A75D);
}

NAKED void CKWaveSound::Release() {
	JUMP(0x2401ABD6);
}

NAKED CKERROR CKWaveSound::TryRecreate() {
	JUMP(0x2401A871);
}

NAKED void CKWaveSound::UpdatePosition(float deltaT) {
	JUMP(0x24019B33);
}

NAKED void CKWaveSound::UpdateFade() {
	JUMP(0x24019FAA);
}

NAKED CKERROR CKWaveSound::WriteDataFromReader() {
	JUMP(0x2401943A);
}

NAKED void CKWaveSound::FillWithBlanks(CKBOOL IncBf) {
	JUMP(0x2401A669);
}

NAKED void CKWaveSound::InternalStop() {
	JUMP(0x24019EC8);
}

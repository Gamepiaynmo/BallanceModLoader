#include "CKInputManager.h"
#include "CKDef.h"

NAKED void CKInputManager::EnableKeyboardRepetition(CKBOOL iEnable) {
	JUMPV(0x78);
}

NAKED CKBOOL CKInputManager::IsKeyboardRepetitionEnabled() {
	JUMPV(0x7c);
}

NAKED CKBOOL CKInputManager::IsKeyDown(CKDWORD iKey, CKDWORD* oStamp) {
	JUMPV(0x80);
}

NAKED CKBOOL CKInputManager::IsKeyUp(CKDWORD iKey) {
	JUMPV(0x84);
}

NAKED CKBOOL CKInputManager::IsKeyToggled(CKDWORD iKey, CKDWORD* oStamp) {
	JUMPV(0x88);
}

NAKED void CKInputManager::GetKeyName(CKDWORD iKey, char* oKeyName) {
	JUMPV(0x8c);
}

NAKED CKDWORD CKInputManager::GetKeyFromName(char* iKeyName) {
	JUMPV(0x90);
}

NAKED unsigned char* CKInputManager::GetKeyboardState() {
	JUMPV(0x94);
}

NAKED CKBOOL CKInputManager::IsKeyboardAttached() {
	JUMPV(0x98);
}

NAKED int CKInputManager::GetNumberOfKeyInBuffer() {
	JUMPV(0x9c);
}

NAKED int CKInputManager::GetKeyFromBuffer(int i, CKDWORD& oKey, CKDWORD* oTimeStamp) {
	JUMPV(0xa0);
}

NAKED CKBOOL CKInputManager::IsMouseButtonDown(CK_MOUSEBUTTON iButton) {
	JUMPV(0xa4);
}

NAKED CKBOOL CKInputManager::IsMouseClicked(CK_MOUSEBUTTON iButton) {
	JUMPV(0xa8);
}

NAKED CKBOOL CKInputManager::IsMouseToggled(CK_MOUSEBUTTON iButton) {
	JUMPV(0xac);
}

NAKED void CKInputManager::GetMouseButtonsState(CKBYTE oStates[4]) {
	JUMPV(0xb0);
}

NAKED void CKInputManager::GetMousePosition(Vx2DVector& oPosition, CKBOOL iAbsolute) {
	JUMPV(0xb4);
}

NAKED void CKInputManager::GetMouseRelativePosition(VxVector& oPosition) {
	JUMPV(0xb8);
}

NAKED CKBOOL CKInputManager::IsMouseAttached() {
	JUMPV(0xbc);
}

NAKED CKBOOL CKInputManager::IsJoystickAttached(int iJoystick) {
	JUMPV(0xc0);
}

NAKED void CKInputManager::GetJoystickPosition(int iJoystick, VxVector* oPosition) {
	JUMPV(0xc4);
}

NAKED void CKInputManager::GetJoystickRotation(int iJoystick, VxVector* oRotation) {
	JUMPV(0xc8);
}

NAKED void CKInputManager::GetJoystickSliders(int iJoystick, Vx2DVector* oPosition) {
	JUMPV(0xcc);
}

NAKED void CKInputManager::GetJoystickPointOfViewAngle(int iJoystick, float* oAngle) {
	JUMPV(0xd0);
}

NAKED CKDWORD CKInputManager::GetJoystickButtonsState(int iJoystick) {
	JUMPV(0xd4);
}

NAKED CKBOOL CKInputManager::IsJoystickButtonDown(int iJoystick, int iButton) {
	JUMPV(0xd8);
}

NAKED void CKInputManager::Pause(BOOL pause) {
	JUMPV(0xdc);
}

NAKED void CKInputManager::ShowCursor(BOOL iShow) {
	JUMPV(0xe0);
}

NAKED BOOL CKInputManager::GetCursorVisibility() {
	JUMPV(0xe4);
}

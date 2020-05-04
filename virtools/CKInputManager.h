#pragma once

#include "CKBaseManager.h"

#define NO_KEY			0
#define KEY_PRESSED		1
#define KEY_RELEASED	2

#define KS_IDLE			0
#define KS_PRESSED		1
#define KS_RELEASED		2

class BML_EXPORT CKInputManager : public CKBaseManager {
public:
	void EnableKeyboardRepetition(CKBOOL iEnable = TRUE);
	CKBOOL IsKeyboardRepetitionEnabled();
	CKBOOL IsKeyDown(CKDWORD iKey, CKDWORD* oStamp = NULL);
	CKBOOL IsKeyUp(CKDWORD iKey);
	CKBOOL IsKeyToggled(CKDWORD iKey, CKDWORD* oStamp = NULL);
	void GetKeyName(CKDWORD iKey, char* oKeyName);
	CKDWORD GetKeyFromName(char* iKeyName);
	unsigned char* GetKeyboardState();
	CKBOOL IsKeyboardAttached();
	int GetNumberOfKeyInBuffer();
	int GetKeyFromBuffer(int i, CKDWORD& oKey, CKDWORD* oTimeStamp = NULL);
	CKBOOL IsMouseButtonDown(CK_MOUSEBUTTON iButton);
	CKBOOL IsMouseClicked(CK_MOUSEBUTTON iButton);
	CKBOOL IsMouseToggled(CK_MOUSEBUTTON iButton);
	void GetMouseButtonsState(CKBYTE oStates[4]);
	void GetMousePosition(Vx2DVector& oPosition, CKBOOL iAbsolute = TRUE);
	void GetMouseRelativePosition(VxVector& oPosition);
	CKBOOL IsMouseAttached();
	CKBOOL IsJoystickAttached(int iJoystick);
	void GetJoystickPosition(int iJoystick, VxVector* oPosition);
	void GetJoystickRotation(int iJoystick, VxVector* oRotation);
	void GetJoystickSliders(int iJoystick, Vx2DVector* oPosition);
	void GetJoystickPointOfViewAngle(int iJoystick, float* oAngle);
	CKDWORD GetJoystickButtonsState(int iJoystick);
	CKBOOL IsJoystickButtonDown(int iJoystick, int iButton);
	void Pause(BOOL pause);
	void ShowCursor(BOOL iShow);
	BOOL GetCursorVisibility();

protected:
	CKInputManager() {};
	~CKInputManager() {};
};
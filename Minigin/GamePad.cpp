#include "GamePad.h"
#include <iostream>

void Gamepad::ProcessInput()
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_controllerIndex, &m_currentState);

	DWORD buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);

	//deadzones
	float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
	float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

	leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
	leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

	if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
	if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

	float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
	float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

	rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
	rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

	if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
	if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

	leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
	rightTrigger = (float)state.Gamepad.bRightTrigger / 255;
}

//source: https://katyscode.wordpress.com/2013/08/30/xinput-tutorial-part-1-adding-gamepad-support-to-your-windows-game/

int Gamepad::GetPort()
{
	return cId + 1;
}

XINPUT_GAMEPAD* Gamepad::GetState()
{
	return &state.Gamepad;
}

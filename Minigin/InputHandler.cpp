#include "InputHandler.h"

void Gamepad::ProcessInput()
{
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_controllerIndex, &m_currentState);

	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(m_controllerIndex, &m_currentState);

	DWORD buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}

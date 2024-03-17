#pragma once
#include <Windows.h>
#include <Xinput.h>

struct ControllerInput
{
public:
	ControllerInput(unsigned int button) : m_button{ WORD(button) } {};
	~ControllerInput() = default;

	unsigned int GetButton() { return m_button; };
private:
	WORD m_button;
};
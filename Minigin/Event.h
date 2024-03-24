#pragma once

enum struct EventType
{
	PlayerDied,
	PickedUp
};

struct Event
{
	static const int m_maxArguments = 8;

	EventType m_type;
	int m_numArguments;
	//EventArg m_args[m_maxArguments];
};
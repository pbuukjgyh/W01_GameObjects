#pragma once

enum struct EventType
{
	PlayerDied,
	PointsAddedSmall,
	PointsAddedBig
};

struct Event
{
	static const int m_maxArguments = 8;

	EventType m_type;
	int m_numArguments;
	//EventArg m_args[m_maxArguments];
};
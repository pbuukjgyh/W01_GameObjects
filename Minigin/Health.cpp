#include "Health.h"

int Health::GetLives()
{
	return m_lives;
}

void Health::RemoveLife()
{
	--m_lives;
	getOwner()->NotifyObservers(EventType::PlayerDied);
}

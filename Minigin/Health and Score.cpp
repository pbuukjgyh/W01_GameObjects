#include "Health and Score.h"

int Health::GetLives()
{
	return m_lives;
}

void Health::RemoveLife()
{
	--m_lives;
	getOwner()->NotifyObservers(EventType::PlayerDied);
}

int Score::GetScore()
{
	return m_totalScore;
}

void Score::AddScore(int score)
{
	m_totalScore += score;
	getOwner()->NotifyObservers(EventType::PointsAdded);
}

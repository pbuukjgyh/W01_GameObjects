#pragma once
#include "ObjectComponent.h"
#include "GameObject.h"

class Health: public ObjectComponent
{
public:
	Health(std::shared_ptr<dae::GameObject> pOwner) : ObjectComponent(pOwner) {};
	Health(std::shared_ptr<dae::GameObject> pOwner, int lives) : ObjectComponent(pOwner) { m_lives = lives; };
	int GetLives();
	void RemoveLife();

private:
	int m_lives{5};
};

class Score : public ObjectComponent
{
public:
	Score(std::shared_ptr<dae::GameObject> pOwner) : ObjectComponent(pOwner) {};
	int GetScore();
	void AddScoreSmall();
	void AddScoreBig();

private:
	int m_totalScore{ 5 };

	int m_scoreAddSmall{ 10 };
	int m_scoreAddBig{ 100 };
};


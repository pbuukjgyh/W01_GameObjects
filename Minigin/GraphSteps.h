#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "ObjectComponent.h"

class TestObject
{
	dae::Transform* m_pLocal;
	int m_id;
public:
	void Function() { m_id *= 2; }
};

class GraphSteps : public ObjectComponent
{
public:
	GraphSteps(std::shared_ptr<dae::GameObject>& pOwner): ObjectComponent(pOwner) { m_arrInt.resize(sizeArr); m_arrClass.resize(sizeArr); };
	~GraphSteps() = default;

	void Render() const;
	void Update(float deltaTime);

private:
	mutable int m_samples{ 100 };

	const int sizeArr{ 10000000 };

	std::vector<int> m_arrInt{};
	std::vector<TestObject> m_arrClass{};

	std::vector<float> m_timesInt{};
	std::vector<float> m_timesClass{};

	bool m_isLoadingInt{ false };
	bool m_isLoadingClass{ false };

	mutable bool m_startLoadingInt{ false };
	mutable bool m_startLoadingClass{ false };

	const std::string m_waitText{ "Wait for it..." };

	void CalculateLoopInt();
	void CalculateLoopClass();

};


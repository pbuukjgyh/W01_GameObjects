#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "ObjectComponent.h"

#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_opengl3.h"
#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_sdl2.h"
#include "..\3rdParty\imgui-1.90.4\plot-master\imgui_plot.h"

class TestObject
{
	dae::Transform* m_pLocal;
	int m_id;
public:
	void Function() { m_id *= 2; }
};

class GraphSteps;

template<typename T>
struct StepArrayStruct
{
	mutable bool isLoading{ false };
	mutable bool shouldReset{ false };

	std::vector<float> times{};
	std::vector<T> arr{};

	StepArrayStruct(int size)
	{
		arr.resize(size);
	}

	bool ShouldUpdate()
	{
		if (isLoading)
		{
			if (shouldReset)
			{
				shouldReset = false;
				times.clear();
			}
			return true;
		}
		return false;
	}
};

class GraphSteps : public ObjectComponent
{
public:
	GraphSteps(std::shared_ptr<dae::GameObject>& pOwner);
	~GraphSteps() = default;
	GraphSteps(const GraphSteps& copy) = delete;
	GraphSteps(GraphSteps&& move) = delete;
	GraphSteps& operator=(const GraphSteps& toCopy) = delete;
	GraphSteps& operator=(GraphSteps&& toMove) = delete;

	void Render() const;
	void Update(float deltaTime);

private:
	mutable int m_samples{ 100 };

	const int sizeArr{ 10000000 };

	std::vector<int> m_arrInt{};
	std::vector<TestObject> m_arrClass{};

	const std::string m_waitText{ "Wait for it..." };

	StepArrayStruct<int> m_intVar{sizeArr};
	StepArrayStruct<TestObject> m_classVar{sizeArr};

	void CalculateLoopInt();
	void CalculateLoopClass();

};


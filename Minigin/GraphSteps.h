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

	int samples{};

	ImGui::PlotConfig plot{};

	StepArrayStruct(int size)
	{
		arr.resize(size);

		plot.frame_size = { 125,75 };
		plot.tooltip.show = true;
		plot.grid_x.size = 1.0f; 
		plot.tooltip.format = "x=%.2f, y=%.2f";
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

	void AvrageTimes()
	{
		const int amountInTimes{ int(log2(1024)) + 1 };
		for (int index = amountInTimes; index < times.size(); ++index)
		{
			times[index % amountInTimes] += times[index];
		}

		times.resize(amountInTimes);

		for (int index = 0; index < times.size(); ++index)
		{
			times[index] /= amountInTimes;
		}

		plot.values.ys = times.data();
		plot.values.count = (int)times.size();

		plot.scale.min = times[times.size() - 1];
		plot.scale.max = times[0];

		isLoading = false;
	}

	void Reset()
	{
		isLoading = false;

		samples = 0;
	}
};

class GraphSteps : public ObjectComponent
{
public:
	GraphSteps(std::shared_ptr<dae::GameObject>& pOwner);
	~GraphSteps() { m_combinedPlot.values.ys_list = nullptr; };
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

	ImGui::PlotConfig m_combinedPlot{};

	void CalculateLoopInt();
	void CalculateLoopClass();

	void SetCombined();
};


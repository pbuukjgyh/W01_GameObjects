#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(std::make_shared<TextureComponent>("background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent(std::make_shared<TextureComponent>("logo.tga"));
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	text->SetPosition(80, 30);
	auto to = std::make_shared<dae::GameObject>(std::vector<std::shared_ptr<ObjectComponent>>{text});
	scene.Add(to);

	auto textFps = std::make_shared<dae::TextObject>("FPS", font);
	auto fps = std::make_shared<FPSComponent>();
	to = std::make_shared<dae::GameObject>(std::vector<std::shared_ptr<ObjectComponent>>{textFps,fps});
	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
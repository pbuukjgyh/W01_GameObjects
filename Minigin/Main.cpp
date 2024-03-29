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
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<dae::GameObject>();
    std::shared_ptr<TextureComponent> pBG = std::make_shared<TextureComponent>(go, "background.tga");
    scene.Add(go);

    go = std::make_shared<dae::GameObject>();
    std::shared_ptr<TextureComponent> pLogo = std::make_shared<TextureComponent>(go, "logo.tga");
    go->SetPosition(216, 180);
    scene.Add(go);

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto to = std::make_shared<dae::GameObject>();

    auto text = std::make_shared<dae::TextComponent>(to, "Programming 4 Assignment", font);
    text->SetPosition(80, 30);

    scene.Add(to);

    to = std::make_shared<dae::GameObject>();

    auto textFps = std::make_shared<dae::TextComponent>(to, "FPS", font);
    auto fps = std::make_shared<FPSComponent>(to);

    scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
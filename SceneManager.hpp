#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.hpp"
#include <memory>
#include <utility>

class SceneManager {
	std::unique_ptr<Scene> currentScene;
    
	public : void loadScene(std::unique_ptr<Scene> scene);
};
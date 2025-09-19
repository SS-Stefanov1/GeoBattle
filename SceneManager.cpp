#pragma once
#include "SceneManager.hpp"

void SceneManager::loadScene(std::unique_ptr<Scene> scene) {
	currentScene = std::move(scene);

	if (currentScene) {
		currentScene->run();
	}
};

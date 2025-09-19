#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "scenes/MainMenu.hpp"
#include "Game.hpp"

#include <iostream>

int main() {
	sf::RenderWindow m_window(sf::VideoMode(800, 600), "GeoBattle", sf::Style::Default);
	sf::Font font;
	font.loadFromFile("assets/arial.ttf");
	SceneManager sceneManager;

	sceneManager.loadScene(std::make_unique<MainMenu>(m_window, sceneManager, font));
}
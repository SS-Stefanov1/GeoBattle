#pragma once
#include "SFML/Graphics.hpp"
#include "../SceneManager.hpp"
#include "../Scene.hpp"

class MainMenu : public Scene {
	sf::RenderWindow& m_window;
	sf::Font          m_font;
	sf::Text          m_menu_text;
	SceneManager&     m_sceneManager;

	public :
		MainMenu(sf::RenderWindow& window, SceneManager& sc_mgr, sf::Font& font);
		void run() override;	
};
#include "MainMenu.hpp"
#include "../Game.hpp"

MainMenu::MainMenu(sf::RenderWindow& window, SceneManager& sc_mgr, sf::Font& font) : m_window(window), m_sceneManager(sc_mgr), m_font(font) {
	m_menu_text.setFont(m_font);
	m_menu_text.setCharacterSize(32);
	m_menu_text.setFillColor(sf::Color::White);
	m_menu_text.setPosition(200.0f, 200.0f);
	m_menu_text.setString("Press ENTER to Start");
};

void MainMenu::run() {
	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Enter) {
					m_sceneManager.loadScene(std::make_unique<Game>("config.ini"));
					return;
				} else if (event.key.code == sf::Keyboard::Escape) {
					m_window.close();
				}
			}
		}
		m_window.clear(sf::Color::Black);
		m_window.draw(m_menu_text);
		m_window.display();
	}
};
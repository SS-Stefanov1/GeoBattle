#include "Game.hpp"

Game::Game(const std::string& config) {
	init(config);
};

void Game::init(const std::string& path) {
	m_window.create(sf::VideoMode(1280,720), "GeoBattle");
	m_window.setFramerateLimit(60);

	spawnPlayer();
};

void Game::run() {
	while (m_running) {
		m_entities.update();

		if (!m_paused) {
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		};

		sRender();
		m_currentFrame++;
	}
};

void Game::setPaused(bool paused) {
	m_paused = paused;
};

void Game::spawnPlayer() {
	std::shared_ptr<Entity> entity = m_entities.addEntity("player");

	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;

	entity->cTransform = std::make_shared<CTransform>(Vc2(mx, my), Vc2(1.0f, 1.0f), 0.0f);
	entity->cShape     = std::make_shared<CShape>(32.0f, 8, sf::Color(10,10,10), sf::Color(255,0,0), 4.0f);
	entity->cInput     = std::make_shared<CInput>();

	m_player = entity;
};

void Game::spawnEnemy() {
	m_lastEnemySpawnTime = m_currentFrame;
};

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {

};

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vc2& target) {

};

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {

};

void Game::sMovement() {
	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
};

void Game::sLifespan() {

};

void Game::sCollision() {

};

void Game::sEnemySpawner() {

};

void Game::sRender() {
	m_window.clear();

	m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
	m_player->cTransform->angle += 1.0f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	m_window.draw(m_player->cShape->circle);

	for (auto e : m_entites.getEntities()) {
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		m_window.draw(e->cShape->circle);
	}

	m_window.display();
};

void Game::sUserInput() {
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_running = false; }

		if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
				case sf::Keyboard::W: break;
				case sf::Keyboard::A: break;
				case sf::Keyboard::S: break;
				case sf::Keyboard::D: break;

				case sf::Keyboard::P: m_paused = !m_paused;

				default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch(event.key.code) {
			case sf::Keyboard::W: break;
			case sf::Keyboard::A: break;
			case sf::Keyboard::S: break;
			case sf::Keyboard::D: break;

			case sf::Keyboard::P: m_paused = !m_paused;

			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				// event.mouseButton.x / event.mouseButton.y
			}

			if (event.mouseButton.button == sf::Mouse::Right) {
				// event.mouseButton.x / event.mouseButton.y
			}
		}
	}	
};
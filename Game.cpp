#include "Game.hpp"

Game::Game(const std::string& config) {
	init(config);
};

/*
struct WindowConfig { int W, H, FR; bool FS; };
struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
*/

void Game::loadFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) { return; }

	std::unordered_map<std::string, std::function<void(std::istringstream&)>> p_map;

	p_map["Window"] = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_windowConfig.W >> this->m_windowConfig.H >> this->m_windowConfig.FR >> this->m_windowConfig.FS) {
			std::getline(iss >> std::ws, data_in);
		}
	};

	p_map["Font"]   = [](std::istringstream& iss) {

	};

	p_map["Player"] = [](std::istringstream& iss) {

	};

	p_map["Enemy"]  = [](std::istringstream& iss) {

	};

	p_map["Bullet"] = [](std::istringstream& iss) {

	};

	std::string c_line;
	while (std::getline(file,c_line)) {
		if (c_line.empty() || c_line[0] == '#') { continue; }

		std::istringstream iss(c_line);
		std::string c_tag;

		iss >> c_tag;

		auto c_it = p_map.find(c_tag);
		
		if (c_it != p_map.end()) {
			c_it->second(iss);
		} else {
			std::cout << "Inccorectly formated config file." << std::endl;
		}
	};
};

void Game::init(const std::string& path) {
	loadFile(path);

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

	entity->cTransform = std::make_shared<CTransform>(Vc2(mx, my), Vc2(0.0f, 0.0f), 0.0f);
	entity->cShape     = std::make_shared<CShape>(32.0f, 8, sf::Color(10,10,10), sf::Color(255,0,0), 4.0f);
	entity->cInput     = std::make_shared<CInput>();

	m_player = entity;
};

void Game::spawnEnemy() {
	auto entity = m_entities.addEntity("enemy");

	float ex = rand() % m_window.getSize().x;
	float ey = rand() % m_window.getSize().y;

	entity->cTransform = std::make_shared<CTransform>(Vc2(ex,ey), Vc2(1.0f, 1.0f), 0.0f);
	entity->cShape     = std::make_shared<CShape>(16.0f, 3, sf::Color(0,0,255), sf::Color(255,255,255), 4.0f);

	m_lastEnemySpawnTime = m_currentFrame;
};

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {

};

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vc2& target) {

};

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {

};

void Game::sMovement() {
	if (m_player->cInput->up) {
		m_player->cTransform->velocity.x += m_playerConfig.S;
	} else if (m_player->cInput->down) {
		m_player->cTransform->velocity.x -= m_playerConfig.S;
	}

	if (m_player->cInput->left) {
		m_player->cTransform->velocity.y -= m_playerConfig.S;
	} else if (m_player->cInput->right) {
		m_player->cTransform->velocity.y += m_playerConfig.S;
	}
	
	if (m_player->cInput->shoot) {

	}
};

void Game::sLifespan() {

};

void Game::sCollision() {

};

void Game::sEnemySpawner() {
	spawnEnemy();
};

void Game::sRender() {
	m_window.clear();

	m_player->cShape->circle.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);
	m_player->cTransform->angle += 1.0f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	m_window.draw(m_player->cShape->circle);

	for (auto e : m_entities.getEntities()) {
		e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);
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
				case (sf::Keyboard::W): { m_player->cInput->up    = true; break; }
				case (sf::Keyboard::A): { m_player->cInput->down  = true; break; }
				case (sf::Keyboard::S): { m_player->cInput->left  = true; break; }
				case (sf::Keyboard::D): { m_player->cInput->right = true; break; }

				case (sf::Keyboard::P): { m_paused = !m_paused; }

				default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch(event.key.code) {
			case (sf::Keyboard::W): { m_player->cInput->up    = false; break; }
			case (sf::Keyboard::A): { m_player->cInput->down  = false; break; }
			case (sf::Keyboard::S): { m_player->cInput->left  = false; break; }
			case (sf::Keyboard::D): { m_player->cInput->right = false; break; }

			case (sf::Keyboard::P): { m_paused = !m_paused; }

			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				m_player->cInput->shoot = true;
				// event.mouseButton.x / event.mouseButton.y
			}

			if (event.mouseButton.button == sf::Mouse::Right) {
				// event.mouseButton.x / event.mouseButton.y
			}
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				m_player->cInput->shoot = false;
			}
		}
	}	
};
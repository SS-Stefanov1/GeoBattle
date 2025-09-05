#include "Game.hpp"

Game::Game(const std::string& config) {
	init(config);
};

void Game::loadFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) { return; }

	std::unordered_map<std::string, std::function<void(std::istringstream&)>> p_map;

	p_map["Window"] = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_windowConfig.W     // Width
				>> this->m_windowConfig.H     // Height
				>> this->m_windowConfig.FR    // Framerate 
				>> this->m_windowConfig.FS) { // Fullscreen Toggle
			std::getline(iss >> std::ws, data_in);
		}
	};

	p_map["Font"]   = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_fontConfig.S
				>> this->m_fontConfig.FR
				>> this->m_fontConfig.FG
				>> this->m_fontConfig.FB
				>> this->m_fontConfig.P) {
			std::getline(iss >> std::ws, data_in);
		}
	};

	p_map["Player"] = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_playerConfig.SR   // Player Radius
				>> this->m_playerConfig.CR   // Collision Radius
				>> this->m_playerConfig.FR   // R
				>> this->m_playerConfig.FG   // G
				>> this->m_playerConfig.FB   // B
				>> this->m_playerConfig.OR   // Outline R
				>> this->m_playerConfig.OG   // Outlibe G
				>> this->m_playerConfig.OB   // Outlibe B
				>> this->m_playerConfig.OT   // 
				>> this->m_playerConfig.V    // Sides
				>> this->m_playerConfig.S) { // Speed
			std::getline(iss >> std::ws, data_in);
		}
	};

	p_map["Enemy"]  = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_enemyConfig.SR      // Enemy Radius
				>> this->m_enemyConfig.CR      // Collision Radius
				>> this->m_enemyConfig.OR      // R
				>> this->m_enemyConfig.OG      // G
				>> this->m_enemyConfig.OB      // B
				>> this->m_enemyConfig.OT      // 
				>> this->m_enemyConfig.VMIN    // Sides Min
				>> this->m_enemyConfig.VMAX    // Sides Max
				>> this->m_enemyConfig.L       // 
				>> this->m_enemyConfig.SI      // 
				>> this->m_enemyConfig.SMIN    // Min Speed
				>> this->m_enemyConfig.SMAX) { // Max Speed
			std::getline(iss >> std::ws, data_in);
		}
	};

	p_map["Bullet"] = [&](std::istringstream& iss) {
		std::string data_in;

		if (iss >> this->m_bulletConfig.SR   // Size
				>> this->m_bulletConfig.CR   // Collision Radius
				>> this->m_bulletConfig.FR   // R
				>> this->m_bulletConfig.FG   // G
				>> this->m_bulletConfig.FB   // B
				>> this->m_bulletConfig.OR   // Outline R
				>> this->m_bulletConfig.OG   // Outline G
				>> this->m_bulletConfig.OB   // Outline B
				>> this->m_bulletConfig.L    // Lifetime
				>> this->m_bulletConfig.S) { // Speed
			std::getline(iss >> std::ws, data_in);
		}
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

	const bool window_mode = m_windowConfig.FS;

	if (!window_mode) {
		m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "GeoBattle", sf::Style::Default);
	} else {
		m_window.create(sf::VideoMode::getDesktopMode(), "GeoBattle", sf::Style::Fullscreen);
	}

	m_window.setFramerateLimit(m_windowConfig.FR);

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

	auto& [p_SR, p_CR, p_FR, p_FG, p_FB, p_OR, p_OG, p_OB, p_OT, p_V, p_S] = m_playerConfig;

	entity->cTransform = std::make_shared<CTransform>(Vc2(mx, my), Vc2(0.0f, 0.0f), p_S);
	entity->cShape     = std::make_shared<CShape>(p_CR, p_V, sf::Color(p_FR,p_FG,p_FB), sf::Color(p_OR,p_OG,p_OB), p_OT);
	entity->cInput     = std::make_shared<CInput>();

	m_player = entity;
};

void Game::spawnEnemy() {
	std::shared_ptr<Entity> entity = m_entities.addEntity("enemy");

	auto ex = rand() % m_window.getSize().x;
	auto ey = rand() % m_window.getSize().y;

	float e_speed = m_enemyConfig.SMIN + static_cast<float>(rand()) / ( static_cast<float> (RAND_MAX / (m_enemyConfig.SMAX - m_enemyConfig.SMIN)));
	float e_dir   = static_cast<float>(rand() % 360) * (3.14159f / 180.0f);
	float e_size  = 16 + (rand() % (m_enemyConfig.CR - 16 + 1));
	int   e_sides = m_enemyConfig.VMIN + (rand() / (RAND_MAX / (m_enemyConfig.VMAX - m_enemyConfig.VMIN)));
	sf::Color e_color(rand() % 256, rand() % 256, rand() % 256);
	sf::Color e_bcolor(rand() % 256, rand() % 256, rand() % 256);

	Vc2 e_velocity(std::cos(e_dir) * e_speed, std::sin(e_dir) * e_speed);

	entity->cTransform = std::make_shared<CTransform>(Vc2(ex,ey), e_velocity, 0.0f);
	entity->cShape     = std::make_shared<CShape>(e_size, e_sides, e_color, e_bcolor, 4.0f);

	entity->cShape->circle.setOrigin(16.0f, 16.0f);

	m_lastEnemySpawnTime = m_currentFrame;
};

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {

};

void Game::spawnBullet(const Vc2& target) {
	std::shared_ptr<Entity> entity = m_entities.addEntity("bullet");

	Vc2   origin  = m_player->cTransform->position;
	Vc2   e_dir   = target * 1.0f - origin * 1.0f;
	float e_speed = m_bulletConfig.S;
	float e_size  = m_bulletConfig.SR;
	float e_csize = m_bulletConfig.CR;
	float e_angle = std::atan2(e_dir.y, e_dir.x) * 180.0f / 3.14159f;
	int   e_life  = m_bulletConfig.L;
	int   e_sides = m_enemyConfig.VMIN + (rand() / (RAND_MAX / (m_enemyConfig.VMAX - m_enemyConfig.VMIN)));
	sf::Color e_color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB);
	sf::Color e_bcolor(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.FB);

	float e_dist = std::sqrt(e_dir.x * e_dir.x + e_dir.y * e_dir.y);
	if (e_dist != 0.0f) { e_dir.x /= e_dist; e_dir.y /= e_dist; } 

	//float p_radius = m_player->cShape->circle.getRadius();
	//Vc2 offset = { origin.x + p_radius, origin.y + p_radius };

	entity->cTransform = std::make_shared<CTransform>(Vc2(origin.x, origin.y), e_dir * e_speed, e_angle);
	entity->cBullet = std::make_shared<CBullet>(e_size, e_csize, e_color, e_bcolor, e_life, e_speed);

	std::cout << target.x << " " << target.y << std::endl;
};

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {

};

void Game::sMovement() {
	m_player->cTransform->velocity = { 0.0f, 0.0f };

	if (m_player->cInput->up)    { m_player->cTransform->velocity.y -= m_playerConfig.S; } 
	if (m_player->cInput->down)  { m_player->cTransform->velocity.y += m_playerConfig.S; }
	if (m_player->cInput->left)  { m_player->cTransform->velocity.x -= m_playerConfig.S; } 
	if (m_player->cInput->right) { m_player->cTransform->velocity.x += m_playerConfig.S; }

	m_player->cTransform->position += m_player->cTransform->velocity;
	
	for (auto& e : m_entities.getEntities("enemy")) {
		if (!e || !e->cShape) { continue; }
		e->cTransform->position += e->cTransform->velocity;
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
	}

	if (m_player->cInput->shoot) {

	}
};

void Game::sLifespan() {

};

void Game::sCollision() {
	float window_h = static_cast<float>(m_window.getSize().y);
	float window_w = static_cast<float>(m_window.getSize().x);

	//auto& active_bullets = m_entities.getEntities("bullet");
	/*auto& active_enemies = m_entities.getEntities("enemy");

	for (auto& e : active_enemies) {
		auto& t = e->cTransform;
		float r = e->cShape->circle.getRadius();

		if (t->position.x - r < 0) {
			t->position.x = r;
			t->velocity.x *= -1;
		}
		else if (t->position.x + r > window_w) {
			t->position.x = window_w - r;
			t->velocity.x *= -1;
		}


		if (t->position.y - r < 0) {
			t->position.y = r;
			t->velocity.y *= -1;
		}
		else if (t->position.y + r > window_h) {
			t->position.y = window_h - r;
			t->velocity.y *= -1;
		}
	}

	for (std::size_t i = 0; i < active_enemies.size(); ++i) {
		for (std::size_t j = i + 1; j < active_enemies.size(); ++j) {
			auto& e_i = active_enemies[i]->cTransform;
			auto& e_j = active_enemies[j]->cTransform;

			Vc2 diff     = e_i->position - e_j->position;
			float dist   = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			float m_dist = active_enemies[i]->cShape->circle.getRadius() + active_enemies[j]->cShape->circle.getRadius();

			if (dist < m_dist && dist > 0.0f) {
				Vc2 r_vel   = e_i->velocity - e_j->velocity;
				Vc2 norm    = diff / dist;
				float n_vel = r_vel.x * norm.x + r_vel.y * norm.y;
				
				if (n_vel > 0) { continue; }

				Vc2 force = norm * n_vel * 1.0f;

				e_i->velocity -= force;
				e_j->velocity += force;	

			    float overlap = 0.5f * (m_dist - dist * 1.0f);

				e_i->position += norm * overlap;	
				e_j->position -= norm * overlap;
			}
		}
	}*/
};	

void Game::sEnemySpawner() {
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI) { 
		//spawnEnemy();
	}
};

void Game::sRender() {
	m_window.clear();

	m_player->cShape->circle.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);
	m_player->cTransform->angle += 1.0f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	m_window.draw(m_player->cShape->circle);

	for (auto e : m_entities.getEntities()) {
		if (e->cShape && e->cTransform) {
			e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);
			e->cTransform->angle += 1.0f;
			e->cShape->circle.setRotation(e->cTransform->angle);

			m_window.draw(e->cShape->circle);
		} else if (e->cBullet && e->cTransform) {
			e->cBullet->bullet.setPosition(e->cTransform->position.x, e->cTransform->position.y);
			e->cBullet->bullet.setRotation(e->cTransform->angle);
			m_window.draw(e->cBullet->bullet);
		}
	}

	m_window.display();
};

void Game::sUserInput() {
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_running = false; }

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { m_window.close(); };

		if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
				case (sf::Keyboard::W): { m_player->cInput->up    = true; break; }
				case (sf::Keyboard::S): { m_player->cInput->down  = true; break; }
				case (sf::Keyboard::A): { m_player->cInput->left  = true; break; }
				case (sf::Keyboard::D): { m_player->cInput->right = true; break; }

				case (sf::Keyboard::P): { m_paused = !m_paused; }

				default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			switch(event.key.code) {
			case (sf::Keyboard::W): { m_player->cInput->up    = false; break; }
			case (sf::Keyboard::S): { m_player->cInput->down  = false; break; }
			case (sf::Keyboard::A): { m_player->cInput->left  = false; break; }
			case (sf::Keyboard::D): { m_player->cInput->right = false; break; }

			case (sf::Keyboard::P): { m_paused = !m_paused; }

			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				m_player->cInput->shoot = true;

				//For Test
				Vc2 target = { 1.0f * event.mouseButton.x, 1.0f * event.mouseButton.y };
				spawnBullet(target);
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
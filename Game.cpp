#include "Game.hpp"
#include "Properties.hpp"

Game::Game(const std::string& cfg) {
	init(cfg);
};

void Game::init(const std::string& path) {
	c_window.create(sf::VideoMode(1280,720), "GeoBattle");
	c_window.setFramerateLimit(60);

	spawnPlayer();
};

void Game::run() {
	while (c_running) {
		c_actors.update();

		sSpawnActor();
		sMovement();
		sCollision();
		sInput();
		sRender();

		c_frame++;
	}
};

void Game::spawnPlayer() {
	auto player = c_actors.addActor("player");
	
	player->pTransform = std::make_shared<PTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);
	player->pShape     = std::make_shared<PShape>(32.0f, 8, sf::Color(10,10,10), sf::Color(255,0,0), 4.0f);
	player->pControls  = std::make_shared<PControls>();
		
	c_player = player;
};

void Game::spawnEnemy() {

};

void Game::spawnBullet() {

};
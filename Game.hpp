#pragma once
#include "SFML/Graphics.hpp"
#include "Engine.hpp"
#include "Actor.hpp"

class Game {
	private : 
		Engine           c_engine; 
		sf::RenderWindow c_window; 
		sf::Font         c_font;
		sf::Text         c_text;
		PlayerCfg        c_player_cfg;
		EnemeyCfg        c_enemy_cfg;
		ProjectileCfg    c_projectile_cfg;
		int              c_score = 0;
		int              c_frame = 0;
		int              c_spawn = 0;
		bool             c_running = true;
		bool             c_paused  = false;

		std::shared_ptr<Actor> c_player;

		void init(const std::string& cfg);
		void pauseGame(bool state);
	
		void sMovement();
		void sInput();
		void sDuration();
		void sRender();
		void sSpawnActor();
		void sCollision();
		void spawnPlayer();
		void spawnEnemy();
		void spawnBullet();
		void breakEnemy(std::shared_ptr<Actor> actor);

	public :
		Game(const std::string& cfg);
		void run();
};
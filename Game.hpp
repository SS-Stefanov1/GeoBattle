#pragma once
#include "SFML/Graphics.hpp"
#include "EntityManager.hpp"
#include "SceneManager.hpp"
#include "Entity.hpp"
#include "Scene.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

struct FontConfig   { int FR, FG, FB, S; std::string P; };
struct WindowConfig { int W, H, FR; bool FS; };
struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, L; float S; };

class Game : public Scene {
	friend int main(); // FOR TESTING PURPOSES ONLY!

	private : 
		sf::RenderWindow m_window;
		sf::Font         m_font;
		sf::Text         m_text;
		EntityManager    m_entities;
		FontConfig		 m_fontConfig;
		WindowConfig     m_windowConfig;
		PlayerConfig     m_playerConfig;
		EnemyConfig      m_enemyConfig;
		BulletConfig     m_bulletConfig;
		int              m_score   = 0;
		int              m_currentFrame = 0;
		int              m_lastEnemySpawnTime = 0;
		bool             m_paused  = false;
		bool             m_running = true;

		std::shared_ptr<Entity> m_player;

		void loadFile(const std::string& path);
		void init(const std::string& config);
		void setPaused(bool paused);
		void sMovement();
		void sUserInput();
		void sLifespan();
		void sRender();
		void sEnemySpawner();
		void sCollision();

		void spawnPlayer();
		void spawnEnemy();
		void spawnSmallEnemies(std::shared_ptr<Entity> entity);
		void spawnBullet(const Vc2& mousePos);
		void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

	public :
		Game(const std::string& config);
		void run();
};
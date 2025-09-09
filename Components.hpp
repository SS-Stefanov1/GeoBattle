#pragma once
	
#include "Vc2.hpp"
#include <SFML/Graphics.hpp>

class CTransform {
	public : 
		Vc2 position = { 0.0, 0.0 };
		Vc2 velocity = { 0.0, 0.0 };
		float angle  = 0;

		CTransform(const Vc2& p, const Vc2& v, float a) : position(p), velocity(v), angle(a) {};
};

class CShape {
	public : 
		sf::CircleShape circle;
	
		CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness) : circle(radius, points) {
			circle.setFillColor(fill);
			circle.setOutlineColor(outline);
			circle.setOutlineThickness(thickness);
			circle.setOrigin(radius, radius);
		}
};

class CBullet {
	public :
		sf::RectangleShape bullet;
		float speed;
		int lifetime;

		CBullet(float size, float collision_area, const sf::Color& fill, const sf::Color& outline, int life, float spd) : lifetime(life), speed(spd) {
			bullet.setFillColor(fill);
			bullet.setOutlineColor(outline);
			bullet.setOutlineThickness(1.0f);
			bullet.setSize({ size * 2.0f, 2.0f });
			bullet.setOrigin(size / 4.0f, size / 4.0f);
		}
};


class CCollision {
	public : 
		float radius = 0;

		CCollision(float r) : radius(r) {};
};

class CScore {
	public : 
		int score = 0;

		CScore(int s) : score(s) {};
};

class CLifespan {
	public : 
		int remaining = 0, total = 0;

		CLifespan(int total) : remaining(total), total(total) {};
};

class CInput {
	public : 
		bool up = false, down = false, left = false, right = false, shoot = false;

		CInput() {};
};
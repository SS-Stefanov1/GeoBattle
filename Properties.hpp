#pragma once
#include "Vec2.hpp"
#include "SFML/Graphics.hpp"

class PShape {
	public : 
		sf::CircleShape circle;
		
		PShape(float r, int hp, const sf::Color& color, const sf::Color& border_color, float border_size) : circle(r,hp) {
			circle.setFillColor(color);
			circle.setOutlineColor(border_color);
			circle.setOutlineThickness(border_size);
			circle.setOrigin(r,r);
		}
};

class PTransform { 
	public : 
		Vec2 position   = {0.0,0.0};
		Vec2 speed      = {0.0,0.0};
		float direction = 0;

		PTransform(const Vec2& p, const Vec2& s, float& d) : position(p), speed(s), direction(d) {};
};

class PCollision {
	public : 
		float radius = 0;
		PCollision(float r) : radius(r) {};
};

class PScore {
	public : 
		int score = 0;
		PScore(int s) : score(s) {};
};

class PDuration { 
	public : 
		int time_left = 0, time_max = 0;
		PDuration(int t) : time_left(t), time_max(t) {};
};

class PControls { 
	public : 
		bool move_up    = false;
		bool move_down  = false;
		bool move_left  = false;
		bool move_right = false;
		bool shoot      = false;
		
		PControls() {};
};
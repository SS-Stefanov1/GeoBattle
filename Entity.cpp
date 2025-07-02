#pragma once

#include "Entity.hpp"
#include "Vc2.hpp"
#include <SFML/Graphics.hpp>

class CTransform {
	public:
		Vc2 position = { 0.0,0.0 };
		Vc2 velocity = { 0.0,0.0 };
		float angle = 0;

		CTransform(const Vc2& p, const Vc2& v, float a) : position(p), velocity(v), angle(a) {}
};

class CShape {
	public : 
		sf::CircleShape circle;

		CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness) : circle(radius,points) {
			circle.setFillColor(fill);
			circle.setOutlineColor(outline);
			circle.setOutlineThickness(thickness);
			circle.setOrigin(radius,radius);
		}
};

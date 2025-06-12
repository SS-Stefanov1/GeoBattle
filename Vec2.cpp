#include "Vec2.hpp"

Vec2::Vec2() : x(0), y(0) {};
Vec2::Vec2(float argx, float argy) : x(argx), y(argy) {};

Vec2 Vec2::operator +  (const Vec2& sh)  const { return Vec2(x + sh.x, y + sh.y) ;};
Vec2 Vec2::operator -  (const Vec2& sh)  const { return Vec2(x - sh.x, y - sh.y) ;};
Vec2 Vec2::operator /  (const float val) const { return Vec2(x / val, y / val) ;};
Vec2 Vec2::operator *  (const float val) const { return Vec2(x * val, y * val) ;};

bool Vec2::operator == (const Vec2& sh) const { return sh.x == sh.y; };
bool Vec2::operator != (const Vec2& sh) const { return sh.x != sh.y; };

void Vec2::operator += (const Vec2& sh) { x += sh.x; y += sh.y; };
void Vec2::operator -= (const Vec2& sh) { x -= sh.x; y -= sh.y; };
void Vec2::operator /= (const float val) { x /= val; y /= val; };
void Vec2::operator *= (const float val) { x *= val; y *= val; };

float Vec2::distance(const Vec2& sh) const { 
	float nx = x - sh.x, ny = y - sh.y;

	return std::sqrt(nx * nx + ny * ny);
};

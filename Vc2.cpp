#include "Vc2.hpp"

Vc2::Vc2() {};
Vc2::Vc2(float xin, float yin) : x(xin), y(yin) {};

bool Vc2::operator == (const Vc2& rhs)  const { return x == rhs.x && y == rhs.y; };
bool Vc2::operator != (const Vc2& rhs)  const { return x != rhs.x || y != rhs.y; };

Vc2  Vc2::operator +  (const Vc2& rhs)  const { return Vc2(x + rhs.x, y + rhs.y); };
Vc2  Vc2::operator -  (const Vc2& rhs)  const { return Vc2(x - rhs.x, y - rhs.y); };
Vc2  Vc2::operator /  (const float val) const { return Vc2(x / val, y / val); };
Vc2  Vc2::operator *  (const float val) const { return Vc2(x * val, y * val); };

void Vc2::operator += (const Vc2& rhs)  { x += rhs.x; y += rhs.y; };
void Vc2::operator -= (const Vc2& rhs)  { x -= rhs.y; y -= rhs.y; };
void Vc2::operator /= (const float val) { x /= val; y /= val; };
void Vc2::operator *= (const float val) { x *= val; y *= val; };

//fix this later
float Vc2::dist(const Vc2& rhs) const { return rhs.x + rhs.y; };
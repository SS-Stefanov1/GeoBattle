#pragma once
#include <cmath>

class Vec2 {
	public:

	float x = 0, y = 0;

	Vec2();
	Vec2(float argx, float argy);

	Vec2 operator +  (const Vec2& rhs) const;
	Vec2 operator -  (const Vec2& rhs) const;
	Vec2 operator /  (const float val) const;
	Vec2 operator *  (const float val) const;

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator /= (const float val);
	void operator *= (const float val);

	float distance(const Vec2& rhs) const;
};
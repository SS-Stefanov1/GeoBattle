#pragma once

#include <cmath>

class Vc2 {
	public :
		float x = 0, y = 0;

		Vc2();
		Vc2(float xin, float yin);

		bool operator == (const Vc2&  rhs) const;
		bool operator != (const Vc2&  rhs) const;

		Vc2  operator +  (const Vc2&  rhs) const;
		Vc2  operator -  (const Vc2&  rhs) const;
		Vc2  operator /  (const float val) const;
		Vc2  operator *  (const float val) const;
	
		void operator += (const Vc2&  rhs);
		void operator -= (const Vc2&  rhs);
		void operator /= (const float val);
		void operator *= (const float val);

		float dist(const Vc2& rhs) const;		
};


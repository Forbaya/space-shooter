#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2 {
	public:
		Vector2(int x, int y);
		Vector2();
		void SetX(int x);
		void SetY(int y);
		int GetX();
		int GetY();
		Vector2 operator-(const Vector2 &rhs);
		Vector2 operator*(const double & v);
		void Normalize();
	private:
		int x;
		int y;
};

#endif
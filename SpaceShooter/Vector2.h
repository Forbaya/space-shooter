#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
	public:
		Vector2(int x, int y);
		Vector2();
		void SetX(int x);
		void SetY(int y);
		int GetX();
		int GetY();
	private:
		int x;
		int y;
};

#endif
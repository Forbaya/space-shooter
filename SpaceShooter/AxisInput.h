#ifndef AXISINPUT_H
#define AXISINPUT_H

enum MovementSpeed {
	NO_SPEED = 0, SLOW_SPEED = 1, AVERAGE_SPEED = 2, FAST_SPEED = 3, REALLY_FAST_SPEED = 4
};

class AxisInput {
public:
	AxisInput();
	int GetLeftX();
	int GetLeftY();
	int GetRightX();
	int GetRightY();
	void SetLeftX(int newLeftX);
	void SetLeftY(int newLeftY);
	void SetRightX(int newRightX);
	void SetRightY(int newRightY);
private:
	int leftX;
	int leftY;
	int rightX;
	int rightY;
};

#endif
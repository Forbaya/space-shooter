#ifndef AXISINPUT_H
#define AXISINPUT_H

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
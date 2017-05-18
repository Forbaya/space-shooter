#include "KeyboardInput.h"

KeyboardInput::KeyboardInput() {
	arrowUp = false;
	arrowRight = false;
	arrowDown = false;
	arrowLeft = false;

	buttonQ = false;
	buttonW = false;
	buttonE = false;
	buttonR = false;
	buttonT = false;
	buttonY = false;
	buttonU = false;
	buttonI = false;
	buttonO = false;
	buttonP = false;
	buttonA = false;
	buttonS = false;
	buttonD = false;
	buttonF = false;
	buttonG = false;
	buttonH = false;
	buttonJ = false;
	buttonK = false;
	buttonL = false;
	buttonZ = false;
	buttonX = false;
	buttonC = false;
	buttonV = false;
	buttonB = false;
	buttonN = false;
	buttonM = false;

	buttonEnter = false;
	buttonEsc = false;
	buttonBackspace = false;
}

KeyboardInput::~KeyboardInput() {
}

bool KeyboardInput::GetArrowUp() {
	return arrowUp;
}

bool KeyboardInput::GetArrowRight() {
	return arrowRight;
}

bool KeyboardInput::GetArrowDown() {
	return arrowDown;
}

bool KeyboardInput::GetArrowLeft() {
	return arrowLeft;
}

bool KeyboardInput::GetButtonQ() {
	return buttonQ;
}

bool KeyboardInput::GetButtonW() {
	return buttonW;
}

bool KeyboardInput::GetButtonE() {
	return buttonE;
}

bool KeyboardInput::GetButtonR() {
	return buttonR;
}

bool KeyboardInput::GetButtonT() {
	return buttonT;
}

bool KeyboardInput::GetButtonY() {
	return buttonY;
}

bool KeyboardInput::GetButtonU() {
	return buttonU;
}

bool KeyboardInput::GetButtonI() {
	return buttonI;
}

bool KeyboardInput::GetButtonO() {
	return buttonO;
}

bool KeyboardInput::GetButtonP() {
	return buttonP;
}

bool KeyboardInput::GetButtonA() {
	return buttonA;
}

bool KeyboardInput::GetButtonS() {
	return buttonS;
}

bool KeyboardInput::GetButtonD() {
	return buttonD;
}

bool KeyboardInput::GetButtonF() {
	return buttonF;
}

bool KeyboardInput::GetButtonG() {
	return buttonG;
}

bool KeyboardInput::GetButtonH() {
	return buttonH;
}

bool KeyboardInput::GetButtonJ() {
	return buttonJ;
}

bool KeyboardInput::GetButtonK() {
	return buttonK;
}

bool KeyboardInput::GetButtonL() {
	return buttonL;
}

bool KeyboardInput::GetButtonZ() {
	return buttonZ;
}

bool KeyboardInput::GetButtonX() {
	return buttonX;
}

bool KeyboardInput::GetButtonC() {
	return buttonC;
}

bool KeyboardInput::GetButtonV() {
	return buttonV;
}

bool KeyboardInput::GetButtonB() {
	return buttonB;
}

bool KeyboardInput::GetButtonN() {
	return buttonN;
}

bool KeyboardInput::GetButtonM() {
	return buttonM;
}

bool KeyboardInput::GetButtonEnter() {
	return buttonEnter;
}

bool KeyboardInput::GetButtonEsc() {
	return buttonEsc;
}

bool KeyboardInput::GetButtonBackspace() {
	return buttonBackspace;
}

void KeyboardInput::SetArrowUp(bool arrowUp) {
	this->arrowUp = arrowUp;
}

void KeyboardInput::SetArrowRight(bool arrowRight) {
	this->arrowRight = arrowRight;
}

void KeyboardInput::SetArrowDown(bool arrowDown) {
	this->arrowDown = arrowDown;
}

void KeyboardInput::SetArrowLeft(bool arrowLeft) {
	this->arrowLeft = arrowLeft;
}

void KeyboardInput::SetButtonQ(bool buttonQ) {
	this->buttonQ = buttonQ;
}

void KeyboardInput::SetButtonW(bool buttonW) {
	this->buttonW = buttonW;
}

void KeyboardInput::SetButtonE(bool buttonE) {
	this->buttonE = buttonE;
}

void KeyboardInput::SetButtonR(bool buttonR) {
	this->buttonR = buttonR;
}

void KeyboardInput::SetButtonT(bool buttonT) {
	this->buttonT = buttonT;
}

void KeyboardInput::SetButtonY(bool buttonY) {
	this->buttonY = buttonY;
}

void KeyboardInput::SetButtonU(bool buttonU) {
	this->buttonU = buttonU;
}

void KeyboardInput::SetButtonI(bool buttonI) {
	this->buttonI = buttonI;
}

void KeyboardInput::SetButtonO(bool buttonO) {
	this->buttonO = buttonO;
}

void KeyboardInput::SetButtonP(bool buttonP) {
	this->buttonP = buttonP;
}

void KeyboardInput::SetButtonA(bool buttonA) {
	this->buttonA = buttonA;
}

void KeyboardInput::SetButtonS(bool buttonS) {
	this->buttonS = buttonS;
}

void KeyboardInput::SetButtonD(bool buttonD) {
	this->buttonD = buttonD;
}

void KeyboardInput::SetButtonF(bool buttonF) {
	this->buttonF = buttonF;
}

void KeyboardInput::SetButtonG(bool buttonG) {
	this->buttonG = buttonG;
}

void KeyboardInput::SetButtonH(bool buttonH) {
	this->buttonH = buttonH;
}

void KeyboardInput::SetButtonJ(bool buttonJ) {
	this->buttonJ = buttonJ;
}

void KeyboardInput::SetButtonK(bool buttonK) {
	this->buttonK = buttonK;
}

void KeyboardInput::SetButtonL(bool buttonL) {
	this->buttonL = buttonL;
}

void KeyboardInput::SetButtonZ(bool buttonZ) {
	this->buttonZ = buttonZ;
}

void KeyboardInput::SetButtonX(bool buttonX) {
	this->buttonX = buttonX;
}

void KeyboardInput::SetButtonC(bool buttonC) {
	this->buttonC = buttonC;
}

void KeyboardInput::SetButtonV(bool buttonV) {
	this->buttonV = buttonV;
}

void KeyboardInput::SetButtonB(bool buttonB) {
	this->buttonB = buttonB;
}

void KeyboardInput::SetButtonN(bool buttonN) {
	this->buttonN = buttonN;
}

void KeyboardInput::SetButtonM(bool buttonM) {
	this->buttonM = buttonM;
}

void KeyboardInput::SetButtonEnter(bool buttonEnter) {
	this->buttonEnter = buttonEnter;
}

void KeyboardInput::SetButtonEsc(bool buttonEsc) {
	this->buttonEsc = buttonEsc;
}

void KeyboardInput::SetButtonBackspace(bool backspace) {
	this->buttonBackspace = backspace;
}

bool KeyboardInput::GetButton(std::string button) {
	if (button.compare("Q") == 0) {
		return buttonQ;
	} else if (button.compare("W") == 0) {
		return buttonW;
	} else if (button.compare("E") == 0) {
		return buttonE;
	} else if (button.compare("R") == 0) {
		return buttonR;
	} else if (button.compare("T") == 0) {
		return buttonT;
	} else if (button.compare("Y") == 0) {
		return buttonY;
	} else if (button.compare("U") == 0) {
		return buttonU;
	} else if (button.compare("I") == 0) {
		return buttonI;
	} else if (button.compare("O") == 0) {
		return buttonO;
	} else if (button.compare("P") == 0) {
		return buttonP;
	} else if (button.compare("A") == 0) {
		return buttonA;
	} else if (button.compare("S") == 0) {
		return buttonS;
	} else if (button.compare("D") == 0) {
		return buttonD;
	} else if (button.compare("F") == 0) {
		return buttonF;
	} else if (button.compare("G") == 0) {
		return buttonG;
	} else if (button.compare("H") == 0) {
		return buttonH;
	} else if (button.compare("J") == 0) {
		return buttonJ;
	} else if (button.compare("K") == 0) {
		return buttonK;
	} else if (button.compare("L") == 0) {
		return buttonL;
	} else if (button.compare("Z") == 0) {
		return buttonZ;
	} else if (button.compare("X") == 0) {
		return buttonX;
	} else if (button.compare("C") == 0) {
		return buttonC;
	} else if (button.compare("V") == 0) {
		return buttonV;
	} else if (button.compare("B") == 0) {
		return buttonB;
	} else if (button.compare("N") == 0) {
		return buttonN;
	} else if (button.compare("M") == 0) {
		return buttonM;
	}

	return false;
}
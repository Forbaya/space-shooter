#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <string>

class KeyboardInput {
	public:
		KeyboardInput();
		~KeyboardInput();
		bool GetArrowUp();
		bool GetArrowRight();
		bool GetArrowDown();
		bool GetArrowLeft();
		bool GetButtonQ();
		bool GetButtonW();
		bool GetButtonE();
		bool GetButtonR();
		bool GetButtonT();
		bool GetButtonY();
		bool GetButtonU();
		bool GetButtonI();
		bool GetButtonO();
		bool GetButtonP();
		bool GetButtonA();
		bool GetButtonS();
		bool GetButtonD();
		bool GetButtonF();
		bool GetButtonG();
		bool GetButtonH();
		bool GetButtonJ();
		bool GetButtonK();
		bool GetButtonL();
		bool GetButtonZ();
		bool GetButtonX();
		bool GetButtonC();
		bool GetButtonV();
		bool GetButtonB();
		bool GetButtonN();
		bool GetButtonM();
		bool GetButtonEnter();
		bool GetButtonEsc();
		bool GetButtonBackspace();

		void SetArrowUp(bool arrowUp);
		void SetArrowRight(bool arrowRight);
		void SetArrowDown(bool arrowDown);
		void SetArrowLeft(bool arrowLeft);

		void SetButtonQ(bool buttonQ);
		void SetButtonW(bool buttonW);
		void SetButtonE(bool buttonE);
		void SetButtonR(bool buttonR);
		void SetButtonT(bool buttonT);
		void SetButtonY(bool buttonY);
		void SetButtonU(bool buttonU);
		void SetButtonI(bool buttonI);
		void SetButtonO(bool buttonO);
		void SetButtonP(bool buttonP);
		void SetButton≈(bool button≈);
		void SetButtonA(bool buttonA);
		void SetButtonS(bool buttonS);
		void SetButtonD(bool buttonD);
		void SetButtonF(bool buttonF);
		void SetButtonG(bool buttonG);
		void SetButtonH(bool buttonH);
		void SetButtonJ(bool buttonJ);
		void SetButtonK(bool buttonK);
		void SetButtonL(bool buttonL);
		void SetButtonZ(bool buttonZ);
		void SetButtonX(bool buttonX);
		void SetButtonC(bool buttonC);
		void SetButtonV(bool buttonV);
		void SetButtonB(bool buttonB);
		void SetButtonN(bool buttonN);
		void SetButtonM(bool buttonM);
		void SetButtonEnter(bool buttonEnter);
		void SetButtonEsc(bool buttonEsc);
		void SetButtonBackspace(bool backspace);
		bool GetButton(std::string button);

	private:
		bool arrowUp;
		bool arrowRight;
		bool arrowDown;
		bool arrowLeft;

		bool buttonQ;
		bool buttonW;
		bool buttonE;
		bool buttonR;
		bool buttonT;
		bool buttonY;
		bool buttonU;
		bool buttonI;
		bool buttonO;
		bool buttonP;
		bool buttonA;
		bool buttonS;
		bool buttonD;
		bool buttonF;
		bool buttonG;
		bool buttonH;
		bool buttonJ;
		bool buttonK;
		bool buttonL;
		bool buttonZ;
		bool buttonX;
		bool buttonC;
		bool buttonV;
		bool buttonB;
		bool buttonN;
		bool buttonM;

		bool buttonEnter;
		bool buttonEsc;
		bool buttonBackspace;
};

#endif
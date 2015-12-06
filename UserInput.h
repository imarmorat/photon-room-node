//#ifndef __USERINPUT_H_
//#define __USERINPUT_H_
//
//class UserInput
//{
//private:
//	int _buttonA;
//	int _buttonB;
//
//public:
//	UserInput(int buttonA, int buttonB)
//	{
//		_buttonA = buttonA;
//		_buttonB = buttonB;
//	}
//
//	void Init()
//	{
//		pinMode(BoardInput_Button1, INPUT_PULLUP);
//		pinMode(BoardInput_Button2, INPUT_PULLUP);
//		attachInterrupt(BoardInput_Button1, onButton1Pressed, FALLING);
//		attachInterrupt(BoardInput_Button2, onButton2Pressed, FALLING);
//	}
//
//	void Reset()
//	{
//		Init();
//	}
//
//};
//
//#endif
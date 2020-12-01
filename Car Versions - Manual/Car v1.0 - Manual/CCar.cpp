// CCar.cpp
// Car Control Class

#include "CCar.h"

////////////////////////////////////
// CCar Constructor
////////////////////////////////////
CCar::CCar()
{}


////////////////////////////////////
// Runs the car
// Monitors for key presses in manual mode
////////////////////////////////////
void CCar::run(void)
{
	char input = 'p';
	
	//motor_test();
	
	//Monitor for key press
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	
	//Key press control logic
	while(input != 'r')
	{
		std::cin >> input;
		switch (input)
		{
			case 'w':
				motor.forward();
				cout << ": " << "FORWARD" << endl;
				break;
			case 's':
				motor.stop();
				cout << ": " << "STOP" << endl;
				break;
			case 'a':
				motor.left();
				cout << ": " << "LEFT" << endl;
				break;
			case 'd':
				motor.right();
				cout << ": " << "RIGHT" << endl;
				break;
			case 'x':
				motor.back();
				cout << ": " << "BACKWARDS" << endl;
				break;
			default:
				cout << ": " << "BAD KEY" << endl;
				break;
		}
	}
	cout << "EXITED" << endl;
}


////////////////////////////////////
// Motor Control Test
////////////////////////////////////
void CCar::motor_test(void)
{
	motor.forward();
	sleep(2);
	motor.stop();
	sleep(2);
	motor.back();
	sleep(2);
	motor.stop();
	sleep(2);
	motor.left();
	usleep(350000);
	motor.stop();
	sleep(2);
	motor.right();
	usleep(350000);
	motor.stop();
}

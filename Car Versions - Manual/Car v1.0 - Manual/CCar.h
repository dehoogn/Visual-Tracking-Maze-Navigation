// CCar.h
// Car Control Class

#include "CMotor.h"
#include <iostream>
#include <fcntl.h>
#include <termios.h>

using namespace std;

class CCar
   {
   public:
		CCar();
		CMotor motor;
		void run(void);
		void motor_test(void);
   };

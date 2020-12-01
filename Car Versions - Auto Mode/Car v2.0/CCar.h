// CCar.h
// Car Control Class

#include "CMotor.h"
#include "CTrack.h"
#include "CSonar.h"
#include <iostream>

using namespace std;

class CCar
   {
   public:
		CCar();
		CMotor motor;
		CTrack guidance;
		CSonar sonar;
		void run(void);
		void adjust(int t, int x_min, int x_max);
		void motion(int t);
		void left(void);
		void right(void);
		void motor_test(void);
		void image_test(void);
		void sonar_test(void);
   };

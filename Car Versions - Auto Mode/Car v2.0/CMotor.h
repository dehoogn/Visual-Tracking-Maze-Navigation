// CMotor.h
// Motor Control Class

#include <unistd.h>
#include "pigpio.h"

using namespace std;

class CMotor
   {
   public:
		CMotor();
		~CMotor();
		void stop(void);
		void forward(void);
		void back(void);
		void left (void);
		void right (void);
   };

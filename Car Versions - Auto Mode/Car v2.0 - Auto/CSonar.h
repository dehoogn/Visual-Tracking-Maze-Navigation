// CSonar.h
// Ultrasonic Range Finder Control Class

// Echo returns a 5v signal which can damage the pi
// Use a voltage divider to return 3.3v
// Resistances of 4.7k and 10k will work
// Vcc = +5v
// Trigger = GPIO23 - Pin 16
// Echo = GPIO24 - Pin 18
// GND = Ground

#define TRIGGER_GPIO 23
#define ECHO_GPIO 24

using namespace std;

class CSonar
{
	public:
		CSonar();
		~CSonar();
		double distance;
		int Trig = TRIGGER_GPIO;
		int Echo = ECHO_GPIO;
		void Distance(void);
};

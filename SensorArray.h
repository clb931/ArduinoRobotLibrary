#ifndef SensorArray_h_
#define SensorArray_h_

#define MAX_SENSORS 10

class SensorArray
{
public:
	SensorArray(int num_sensors_IN, int pins_IN[]);
	
	float	getLocation();
	int 	readPin(int pin_IN);
private:
	int num_sensors;
	int mid_left, mid_right;
	int pins[10];
};

#endif
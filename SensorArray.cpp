#include "SensorArray.h"
#include "Arduino.h"
#include "string.h"

SensorArray::SensorArray(int num_sensors_IN, int pins_IN[])
{
	if (num_sensors_IN > MAX_SENSORS)
	{
		Serial.end();
		Serial.begin(9600);
		Serial.println("Too many sensors");
	}
	num_sensors = num_sensors_IN;
	mid_right = (num_sensors / 2) + 1;
	mid_left = mid_right - 1;
	for (int i = 0; i < num_sensors; ++i)
	{
		pins[i] = pins_IN[i];
	}
}

float SensorArray::getLocation()
{	
	const int size = num_sensors;
	int loc[size];
	int j = 0;
		
	for (int i = 0; i < size; ++i)
	{
		if (readPin(i) < 50)
		{
			loc[j] = i + 1;
			j++;
		}
	}
	
	if (j < 2)											// if less than 2 sensors are tripped,
		return 1.0f;									// go straight
	else if (j > 2)										// if more than 2 sensors are tripped,
		return 0.0f;									// stop
	else if (loc[0] > mid_left) 						// if the (left most) tripped sensor is not the mid_left sensor,
		return 1.0f - ((float)loc[0] / (float)mid_left);	// turn left
	else if (loc[1] < mid_right) 						// if the (right most) tripped sensor is not the mid_right sensor,
		return ((float)(loc[0] - mid_left)/ (float)mid_left) * -1.0f;	// turn right
	else												// if both tripped sensors are the middle sensors,
		return 1.0f;									// go straight
}

int SensorArray::readPin(int pin_IN)
{
	if (pin_IN >= num_sensors || pin_IN < 0)	
		return -1;
	else
		return analogRead(pins[pin_IN]);
}
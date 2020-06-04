#include "FlywheelAlgorithms.h"
#include <Arduino.h>


FlywheelAlgorithms::FlywheelAlgorithms(unsigned int pin = 1,
									   unsigned int max_voltage = 560)
		: _pin(pin),
		_max_voltage(max_voltage)
{}

unsigned int FlywheelAlgorithms::get_half_time_rot()
{
	_voltage = analogRead(_pin);
	if(_voltage > _max_voltage)
	{
		if(!current_volt)
		{
			unsigned int span = millis() - time;

			time = millis();

			return span;
		}

		current_volt = true;

	}else{
		current_volt = false;
	}

	return 0;
}


unsigned int FlywheelAlgorithms::get_full_time_rot()
{
	_voltage = analogRead(_pin);
	if(_voltage > _max_voltage)
	{
		if(!current_volt)
		{
			if(old_volt == false) aTime = get_half_time_rot();
			else bTime = get_half_time_rot();
			
			old_volt = !old_volt;
		}

		current_volt = true;
		unsigned int sum = aTime + bTime;

		return sum;
	} else {
		current_volt = false;
	}

	return 0;
}


float FlywheelAlgorithms::get_angular_velocity(Speed rad = RAD_PER_MS)
{
	float T = static_cast<float>(get_half_time_rot()); // millisec
	float angle_speed = 0.f;
	if(T > 0.0f) { 
		switch(rad)
		{
			// formula Pi/T, because T is a half period
			case RAD_PER_MS:
				angle_speed = 3.141592 / T;
				break;
			case RAD_PER_SEC:
				angle_speed = 3.141592 / (T * 0.001);
				break;
			case DEG_PER_MS:
				angle_speed = 180 / T;
				break;
			case DEG_PER_SEC:
				angle_speed = 180 / (T * 0.001);
				break;
		}
	}	

	return angle_speed;
}

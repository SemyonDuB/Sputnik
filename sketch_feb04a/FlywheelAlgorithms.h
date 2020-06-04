#pragma once


enum Speed { RAD_PER_SEC, RAD_PER_MS, DEG_PER_MS, DEG_PER_SEC };


class FlywheelAlgorithms
{
public:
	FlywheelAlgorithms(unsigned int pin = 1, 
					   unsigned int max_voltage = 560);

	unsigned int get_half_time_rot();
	unsigned int get_full_time_rot();

	float get_angular_velocity(Speed rad = RAD_PER_MS);
  
private:
	bool current_volt = false;
	bool old_volt     = false;

	unsigned int aTime = 0;
	unsigned int bTime = 0;
  
	unsigned int time = 0;

	unsigned int _voltage = 0;
	unsigned int _pin;
	unsigned int _max_voltage;
};

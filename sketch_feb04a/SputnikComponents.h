#pragma once

#include <Arduino.h>
#include <TroykaIMU.h>
#include <Thread.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Wire.h>

#include "FlywheelAlgorithms.h"
#include "WifiConnection.hpp"


class SputnikComponents
{
public:
	SputnikComponents();
	void initializeSputnik();
	void mainLoop();
	void commandsHandler();

private:

	Gyroscope gyro;
	SoftwareSerial wifi_serial;
	FlywheelAlgorithms flywheel;
	WifiConnection<SoftwareSerial> wifi_module;

	String msg;
};

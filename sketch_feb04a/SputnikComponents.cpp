#include "SputnikComponents.h"


SputnikComponents::SputnikComponents()
	: wifi_serial(8, 9),
	wifi_module(wifi_serial, "TP-Link_7CD6", "17242722", "192.168.4.2", "8090")
{}

void SputnikComponents::initializeSputnik()
{
	Serial.begin(9600);
	gyro.begin();
	gyro.setRange(RANGE_250DPS);
	wifi_module.initializeWifi();
}



void SputnikComponents::mainLoop()
{
}


void SputnikComponents::commandsHandler()
{

	if (wifi_serial.available()) 
	{

		msg = wifi_serial.readString();
		msg.trim();
		Serial.println(msg);

		if(msg.startsWith("+IPD"))
		{
			// gyro commands
			if(msg.endsWith("gyro x"))
				wifi_module.send_to_server(String(int(gyro.readDegPerSecX())));
			else if(msg.endsWith("gyro y"))
				wifi_module.send_to_server(String(int(gyro.readDegPerSecY())));
			else if(msg.endsWith("gyro z"))
				wifi_module.send_to_server(String(int(gyro.readDegPerSecZ())));

			// flywheel commands
			else if(msg.endsWith("flywheel rad/ms"))
				wifi_module.send_to_server(String(flywheel.get_angular_velocity(RAD_PER_MS)));
			else if(msg.endsWith("flywheel rad/sec"))
				wifi_module.send_to_server(String(flywheel.get_angular_velocity(RAD_PER_SEC)));
			else if(msg.endsWith("flywheel deg/ms"))
				wifi_module.send_to_server(String(flywheel.get_angular_velocity(DEG_PER_MS)));
			else if(msg.endsWith("flywheel deg/sec"))
				wifi_module.send_to_server(String(flywheel.get_angular_velocity(DEG_PER_SEC)));

			// trace command that send all information
			else if(msg.endsWith("trace"))
			{
				while(!msg.endsWith("quit"))
				{
					String gyroX = "X=" + String(int(gyro.readDegPerSecX()));
					String gyroY = "Y=" + String(int(gyro.readDegPerSecY()));
					String gyroZ = "Z=" + String(int(gyro.readDegPerSecZ()));

					String flywheelDeg_PER_SEC = String(flywheel.get_angular_velocity(DEG_PER_SEC));

					String commplexStr = gyroX + "\n" + gyroY + "\n" +
						gyroZ + "\n\n" + flywheelDeg_PER_SEC;

					wifi_module.send_to_server(commplexStr);
					msg = wifi_serial.readString();

					msg.trim();
				}
			}

			else wifi_module.send_to_server("Undefined command ...");
		}

	}
}

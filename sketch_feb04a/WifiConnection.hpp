#pragma once
#include <Arduino.h>

#include <SoftwareSerial.h>
#include <HardwareSerial.h>

// Template Declaration
template<class T>
class WifiConnection
{
public:
	WifiConnection(T &wifi_serial,
				   const String wifi_name,
				   const String wifi_pass,
				   const String server_ip,
				   const String server_port);

	void initializeWifi();

	void send_to_server(String msg);

private:
	void connect_to_WIFI();
	void check_ip();
	void connect_to_server();

	T &wifi_serial;

	const String wifi_name;
	const String wifi_pass;
	const String server_ip;
	const String server_port;
};


// Template definition
template<class T>
WifiConnection<T>::WifiConnection(T &wifi_serial,
							   const String wifi_name,
							   const String wifi_pass,
							   const String server_ip,
							   const String server_port)
	: wifi_serial(wifi_serial),
	wifi_name(wifi_name),
	wifi_pass(wifi_pass),
	server_ip(server_ip),
	server_port(server_port)
{}


template<class T>
void WifiConnection<T>::initializeWifi()
{
	wifi_serial.begin(9600);
	while(!wifi_serial);

	wifi_serial.println("AT+RST");
	wifi_serial.println("AT+CWMODE=3");
	delay(500);

	wifi_serial.println("AT+CIPMUX=0");
	delay(500);

	check_ip();
	connect_to_server();

	delay(500);
}


template<class T>
void WifiConnection<T>::send_to_server(String msg)
{
	wifi_serial.print("AT+CIPSEND=");
	wifi_serial.println(msg.length());
	delay(50);
	wifi_serial.println(msg);
}


// Check connection to wifi
template<class T>
void WifiConnection<T>::connect_to_WIFI()
{
	// Make a string and send to wifi_module
	String cwjap = String("AT+CWJAP=");
	wifi_serial.println(cwjap + "\"" +  wifi_name + "\"" + "," + "\"" + wifi_pass + "\"");
	delay(500);

	wifi_serial.println("AT+CWJAP?");

	// Wait connection
	while(1){
		if(wifi_serial.find("OK")) 
		{ 
			Serial.println("\nConnection!");
			break;
		} else {
			Serial.print(".");
			delay(250);
		}          
	}
	Serial.println();
}


// Check that IP is given
template<class T>
void WifiConnection<T>::check_ip()
{
	wifi_serial.println("AT+CIFSR");

	while(1){                      
		if (wifi_serial.find("OK"))
		{ 
			Serial.println("IP received");
			break;
		} else {
			wifi_serial.println("AT+CIFSR");
			Serial.print(".");
			delay(250);    
		}
	}

	Serial.println();
}


template<class T>
void WifiConnection<T>::connect_to_server()
{
	// Make a string and send to wifi module
	String cipstart = "AT+CIPSTART=\"UDP\",";
	cipstart += "\"" + server_ip + "\"" + "," + server_port + "," + "8091";
	wifi_serial.println(cipstart);

	// Wait connection
	while(1){         
		if (wifi_serial.find("ALREADY CONNECTED"))
		{ 
			// Just simple debug information
			String debug_msg = "Success connection to server! (IP: ";
			Serial.println(debug_msg + server_ip + " ) (PORT: " + server_port + " )");
			break;
		} else {
			// Try connect to wifi module while not connection
			wifi_serial.println(cipstart);
			Serial.print(".");
			delay(250);    
		}
	}
}

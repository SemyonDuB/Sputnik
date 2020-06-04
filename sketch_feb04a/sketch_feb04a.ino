#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Thread.h>

#include "FlywheelAlgorithms.h"
#include "WifiConnection.hpp"
#include "SputnikComponents.h"


SputnikComponents Sputnik;
Thread commandsThread = Thread();


void Sputnik_commandsHandler_wrapper()
{
    Sputnik.commandsHandler();
}


void setup() 
{
    Sputnik.initializeSputnik();
    commandsThread.onRun(Sputnik_commandsHandler_wrapper);
}


void loop() 
{
    if(commandsThread.shouldRun()) commandsThread.run();
}

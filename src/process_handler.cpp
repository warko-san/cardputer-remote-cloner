#include <Arduino.h>
#include "process_handler.h"

ProcessHandler::ProcessHandler()
{
}

ProcessHandler::~ProcessHandler()
{
}

void ProcessHandler::savePrevProcess(Process proc)
{
    prevProcess = proc;
}

void ProcessHandler::savePrevProcess()
{
    prevProcess = currentProcess;
}

Process ProcessHandler::getPrevProcess()
{
    return prevProcess;
}

void ProcessHandler::setCurrentProcess(Process proc)
{
    currentProcess = proc;
}

void ProcessHandler::saveSendProcess()
{
     Serial.printf("Saving Send Process: %d\n", currentProcess);
    sendProcess = currentProcess;
}

Process ProcessHandler::getSavedSendProcess()
{
    return sendProcess;
}

Process ProcessHandler::getCurrentProcess()
{
    return currentProcess;
}

#include "process_handler.h"

ProcessHandler::ProcessHandler()
{
}

ProcessHandler::~ProcessHandler()
{
}

void ProcessHandler::saveProcess()
{
    saved_proc = current_proc;
}

void ProcessHandler::setCurrentProcess(int proc)
{
    current_proc = proc;
}

int ProcessHandler::getSavedProcess()
{
    return saved_proc;
}

int ProcessHandler::getCurrentProcess()
{
    return current_proc;
}

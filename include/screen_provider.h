#ifndef SCREEN_PROVIDER_H
#define SCREEN_PROVIDER_H

#include <M5Cardputer.h>
#include "definitions.h"

class ScreenProvider
{
    private:
    public:
    ScreenProvider();
    ~ScreenProvider();

    void readScreen();
    void showReceivedData(uint16_t address, uint16_t command);
    void printCommandData(uint16_t address, uint16_t command, bool firstInput, bool codeSaved);
    void printCurrentCommand(String commandName);
};

#endif
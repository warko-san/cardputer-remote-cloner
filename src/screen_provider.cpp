#include "screen_provider.h"

ScreenProvider::ScreenProvider()
{
}

ScreenProvider::~ScreenProvider()
{
}

void ScreenProvider::readScreen()
{
    DISP.clearDisplay();
    DISP.setTextColor(WHITE);
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.setCursor(10, 20);
    DISP.println("Reading:");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);
}

void ScreenProvider::showReceivedData(uint16_t address, uint16_t command)
{
    DISP.setCursor(10, 50);
    DISP.print("Address:");
    DISP.println(address, HEX);
    DISP.fillRect(10, 70, DISP.width(), 20, BGCOLOR); // Reset the back of line
    DISP.setCursor(10, 70);
    DISP.print("Command: 0x");
    DISP.println(command, HEX);
}

void ScreenProvider::printCommandData(uint16_t address, uint16_t command, bool firstInput)
{
    DISP.setTextSize(SMALL_TEXT);
    DISP.setCursor(10, 70);
    DISP.setTextColor(RED);
    if (address != 0)
    {
        DISP.print("Address:");
        DISP.println(address, HEX);
    }
    DISP.setCursor(10, 90);
    if (command != 0)
    {
        DISP.print("Command: 0x");
        DISP.println(command, HEX);
    }

    DISP.setCursor(10, 110);
    if (command != 0 && address != 0)
    {
        if (firstInput)
        {
            DISP.print("Repeat command ");
            DISP.setCursor(10, 100);
            DISP.println("to save");
        }
        else
        {
            DISP.println("Saved! Press next");
        }
    }
}

void ScreenProvider::printCurrentCommand(String commandName)
{
    DISP.clearDisplay();
    DISP.setTextColor(RED);
    DISP.setTextSize(SMALL_TEXT);
    DISP.setCursor(10, 20);
    DISP.print("Prepared to save: ");
    DISP.setTextColor(WHITE);
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.println(commandName.c_str());
}
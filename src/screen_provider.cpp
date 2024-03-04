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
#pragma once

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE

#include <Arduino.h>
#include <string>
#include <M5Cardputer.h>
#include "definitions.h"
#include "ir_handler.h"
#include "sd_card.h"
#include "comand_saver.h"
#include "menu_handler.h"
#include "process_handler.h"
#include "screen_provider.h"

class TaskManager
{
private:
    uint8_t rotation = 1;

    SDcard sdCard;
    ProcessHandler processHandler;
    MenuHandler menuHandler;
    ComandSaver comandSaver;
    IRHandler irHandler;
    ScreenProvider screenProvider;

public:
    TaskManager();
    ~TaskManager();

    void setup();
    void loop();
};


#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE

#include <string>
#include <M5Cardputer.h>
#include "ir_handler.h"
#include "sd_card.h"
#include "comand_saver.h"
#include "menu_handler.h"
#include "process_handler.h"
#include "definitions.h"

class TaskManager
{
private:
    uint8_t rotation = 1;

    SDcard sdCard;
    ProcessHandler processHandler;
    MenuHandler menuHandler;
    ComandSaver comandSaver;
    IRHandler irHandler;

public:
    TaskManager();
    ~TaskManager();

    void setup();
    void loop();
};

#endif

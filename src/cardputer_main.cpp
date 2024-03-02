#include <Arduino.h>
#include "task_manager.h"

TaskManager taskManager;

void setup()
{
  taskManager.setup();
}

void loop()
{
  taskManager.loop();
}


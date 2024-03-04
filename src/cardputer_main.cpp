#include "cardputer_main.h"
#include "task_manager.h"

TaskManager taskManager;

void setup()
{
  Serial.begin(115200);
  taskManager.setup();
}

void loop()
{
  taskManager.loop();
}


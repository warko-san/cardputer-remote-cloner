#include "task_manager.h"

TaskManager::TaskManager() : menuHandler(processHandler, sdCard, comandSaver, irHandler)
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::setup()
{
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    DISP.setRotation(rotation);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    sdCard.setupSdCard();
}

void TaskManager::loop()
{
    // This is the code to handle running the main loops
    // Background processes
    //  switcher_button_proc();
    // screen_dim_proc();
    menuHandler.check_menu_press();

    // Switcher
    if (menuHandler.isSwitching)
    {
        menuHandler.isSwitching = false;
        Serial.printf("Switching To Task: %d\n", processHandler.getCurrentProcess());
        switch (processHandler.getCurrentProcess())
        {
        case 1:
            menuHandler.mmenu_setup();
            break;
        case 2:
            menuHandler.read_setup();
            break;
        case 3:
            menuHandler.send_setup();
            break;
        case 4:
            menuHandler.settings_setup();
            break;
        case 5:
            menuHandler.battery_setup();
            break;
        case 6:
            menuHandler.enter_name_setup();
            break;
        case 7:
            menuHandler.copy_menu_setup();
            break;
        case 8:
            menuHandler.copy_main_contr_setup();
            break;
        case 9:
            menuHandler.copy_num_setup();
            break;
        case 10:
            menuHandler.copy_nav_setup();
            break;
        case 11:
            menuHandler.copy_misc_setup();
            break;
        case 12:
            menuHandler.load_remote_setup();
            break;
        case 13:
            comandSaver.copyKeySetup(processHandler, sdCard, irHandler);
            break;
        case 14:
            menuHandler.loadRemoteSetup();
            break;
        case 15:
            menuHandler.sendMenuSetup();
            break;
        case 16:
            menuHandler.sendMainCtrlSetup();
            break;
        case 17:
            menuHandler.sendNumCtrlSetup();
            break;
        case 18:
            menuHandler.sendNavCtrlSetup();
            break;
        case 19:
            menuHandler.sendMiscCtrlSetup();
            break;
        case 20:
            menuHandler.sendControlSetup();
            break;
        }
    }

    switch (processHandler.getCurrentProcess())
    {
    case 1:
        menuHandler.mmenu_loop();
        break;
    case 2:
        menuHandler.read_loop();
        break;
    case 3:
        menuHandler.send_loop();
        break;
    case 4:
        menuHandler.settings_loop();
        break;
    case 5:
        menuHandler.battery_loop();
        break;
    case 6:
        menuHandler.enter_name_loop();
        break;
    case 7:
        menuHandler.copy_menu_loop();
        break;
    case 8:
        menuHandler.copy_main_contr_loop();
        break;
    case 9:
        menuHandler.copy_num_loop();
        break;
    case 10:
        menuHandler.copy_nav_loop();
        break;
    case 11:
        menuHandler.copy_misc_loop();
        break;
    case 12:
        menuHandler.load_remote_loop();
        break;
    case 13:
        comandSaver.copyKeyLoop(menuHandler, processHandler, sdCard, irHandler);
        break;
    case 14:
        menuHandler.loadRemoteLoop();
        break;
    case 15:
        menuHandler.sendMenuLoop();
        break;
    case 16:
        menuHandler.sendMainCtrlLoop();
        break;
    case 17:
        menuHandler.sendNumCtrlLoop();
        break;
    case 18:
        menuHandler.sendNavCtrlLoop();
        break;
    case 19:
        menuHandler.sendMiscCtrlLoop();
        break;
    case 20:
        menuHandler.sendControlLoop();
        break;
    }
}

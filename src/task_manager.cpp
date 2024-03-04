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
    menuHandler.checkBackPress();

    // Switcher
    if (menuHandler.isSwitching)
    {
        menuHandler.isSwitching = false;
        Serial.printf("Switching To Task: %d\n", processHandler.getCurrentProcess());
        switch (processHandler.getCurrentProcess())
        {
        case Process::MAIN_MENU:
            menuHandler.mmenu_setup();
            break;
        case Process::READ_MENU:
            menuHandler.read_setup();
            break;
        case Process::SEND_MENU:
            menuHandler.send_setup();
            break;
        case Process::SETTINGS:
            menuHandler.settings_setup();
            break;
        case Process::BATTERY_INFO:
            menuHandler.battery_setup();
            break;
        case Process::COPY_REMOTE_ENTER_NAME:
            menuHandler.enter_name_setup();
            break;
        case Process::COPY_REMOTE_CONTROLS:
            menuHandler.copy_menu_setup();
            break;
        case Process::COPY_MAIN_CONTROLS:
            menuHandler.copy_main_contr_setup();
            break;
        case Process::COPY_NUMBERS:
            menuHandler.copy_num_setup();
            break;
        case Process::COPY_NAVIGATION:
            menuHandler.copy_nav_setup();
            break;
        case Process::COPY_MISC:
            menuHandler.copy_misc_setup();
            break;
        case Process::LOAD_REMOTE:
            menuHandler.load_remote_setup();
            break;
        case Process::SAVE_CONTROLS:
            comandSaver.copyKeySetup(processHandler, sdCard, irHandler);
            break;
        case Process::LOAD_REMOTE_INTO_MEMORY:
            menuHandler.loadRemoteControlsSetup();
            break;
        case Process::SEND_REMOTE_CONTROLS:
            menuHandler.sendMenuSetup();
            break;
        case Process::SEND_MAIN_CONTROLS:
            menuHandler.sendMainCtrlSetup();
            break;
        case Process::SEND_NUMBERS:
            menuHandler.sendNumCtrlSetup();
            break;
        case Process::SEND_NAVIGATION:
            menuHandler.sendNavCtrlSetup();
            break;
        case Process::SEND_MISC:
            menuHandler.sendMiscCtrlSetup();
            break;
        case Process::SEND_COMMAND:
   //         menuHandler.sendControlSetup();
            break;
        }
    }

    switch (processHandler.getCurrentProcess())
    {
    case Process::MAIN_MENU:
        menuHandler.mmenu_loop();
        break;
    case Process::READ_MENU:
        menuHandler.read_loop();
        break;
    case Process::SEND_MENU:
        menuHandler.send_loop();
        break;
    case Process::SETTINGS:
        menuHandler.settings_loop();
        break;
    case Process::BATTERY_INFO:
        menuHandler.battery_loop();
        break;
    case Process::COPY_REMOTE_ENTER_NAME:
        menuHandler.enter_name_loop();
        break;
    case Process::COPY_REMOTE_CONTROLS:
        menuHandler.copy_menu_loop();
        break;
    case Process::COPY_MAIN_CONTROLS:
        menuHandler.copy_main_contr_loop();
        break;
    case Process::COPY_NUMBERS:
        menuHandler.copy_num_loop();
        break;
    case Process::COPY_NAVIGATION:
        menuHandler.copy_nav_loop();
        break;
    case Process::COPY_MISC:
        menuHandler.copy_misc_loop();
        break;
    case Process::LOAD_REMOTE:
        menuHandler.load_remote_loop();
        break;
    case Process::SAVE_CONTROLS:
        comandSaver.copyKeyLoop(menuHandler, processHandler, sdCard, irHandler);
        break;
    case Process::LOAD_REMOTE_INTO_MEMORY:
   //     menuHandler.loadRemoteControlsLoop();
        break;
    case Process::SEND_REMOTE_CONTROLS:
        menuHandler.sendMenuLoop();
        break;
    case Process::SEND_MAIN_CONTROLS:
        menuHandler.sendMainCtrlLoop();
        break;
    case Process::SEND_NUMBERS:
        menuHandler.sendNumCtrlLoop();
        break;
    case Process::SEND_NAVIGATION:
        menuHandler.sendNavCtrlLoop();
        break;
    case Process::SEND_MISC:
        menuHandler.sendMiscCtrlLoop();
        break;
    case Process::SEND_COMMAND:
        // menuHandler.sendControlLoop();
        break;
    }
}

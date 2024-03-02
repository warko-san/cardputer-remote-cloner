#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#pragma once

#include <WString.h>
#include "menus.h"
#include "definitions.h"

class ProcessHandler;
class ComandSaver;
class SDcard;
class IRHandler;
struct MenuIr;

#ifdef MENUS_H

class MenuHandler
{
private:

    ProcessHandler &processHandler;
    SDcard &sdCard;
    ComandSaver &comandSaver;
    IRHandler &irHandler;
    
    uint8_t oldBattery = 0;
    uint8_t loadedSize = 0;
    String loadedDir = "";

    void drawmenu(MenuIr thismenu[], int size);
    void drawmenu(String thismenu[], int size);

public:
    MenuHandler(ProcessHandler &processHandler, SDcard &sdCard, ComandSaver &comandSaver, IRHandler &irHandler);

    uint8_t cursor = 0;
    bool rstOverride = true; // Reset Button Override. Set to true when navigating menus.
    bool isSwitching = true;
    String data = "";

    void drawmenu(const MENU thismenu[], int size, MarkType mark = MarkType::EMPTY);

    /// BATTERY INFO ///
    void battery_drawmenu(uint8_t battery);
    void battery_setup();
    void battery_loop();

    // Main operations
    bool check_select_press();
    bool check_next_press();
    void switcher_button_proc();
    void check_menu_press();
    void checkBackPress();

    // Menu operations
    void mmenu_setup();
    void mmenu_loop();

    void read_setup();
    void read_loop();

    void send_setup();
    void send_loop();

    void settings_setup();
    void settings_loop();

    void enter_name_setup();
    void enter_name_loop();

    void copy_menu_setup();
    void copy_menu_loop();

    void copy_main_contr_setup();
    void copy_main_contr_loop();

    void copy_num_setup();
    void copy_num_loop();

    void copy_nav_setup();
    void copy_nav_loop();

    void copy_misc_setup();
    void copy_misc_loop();

    void load_remote_setup();
    void load_remote_loop();

    void loadRemoteControlsSetup();
    void loadRemoteControlsLoop();

    void sendControlSetup();
    void sendControlLoop();

    void sendMenuSetup();
    void sendMenuLoop();

    void sendMainCtrlSetup();
    void sendMainCtrlLoop();

    void sendNumCtrlSetup();
    void sendNumCtrlLoop();

    void sendNavCtrlSetup();
    void sendNavCtrlLoop();

    void sendMiscCtrlSetup();
    void sendMiscCtrlLoop();

    void copyKeyInternalLoop();
}; // MenuHandler

#endif // MENUS_H

#endif // MENU_HANDLER_H


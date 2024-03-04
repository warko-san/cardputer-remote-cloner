#ifndef MENUS_H
#define MENUS_H

#include <cstdint>
#include "process.h"

struct MENU
{
    char name[23];
    Process command;
    Process backProcess;
};

enum MarkType
{
    EMPTY,
    DOT,
    CHECK
};

/// MAIN MENU ///
const MENU mmenu[] = {
    {"Read signals", Process::READ_MENU, Process::MAIN_MENU},
    {"Send signals", Process::SEND_MENU, Process::MAIN_MENU},
    {"Copy remote", Process::COPY_REMOTE_ENTER_NAME, Process::MAIN_MENU},
    {"Load remote", Process::LOAD_REMOTE, Process::MAIN_MENU},
    {"Battery info", Process::BATTERY_INFO, Process::MAIN_MENU},
    {"Settings", Process::SETTINGS, Process::MAIN_MENU}};
const int mmenu_size = sizeof(mmenu) / sizeof(MENU);

const MENU copyRContrM[] = {
    {"Main controls", Process::COPY_MAIN_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Num buttons", Process::COPY_NUMBERS, Process::COPY_REMOTE_CONTROLS},
    {"Navigation controls", Process::COPY_NAVIGATION, Process::COPY_REMOTE_CONTROLS},
    {"Misc controls", Process::COPY_MISC, Process::COPY_REMOTE_CONTROLS}};
const int copy_remote_size = sizeof(copyRContrM) / sizeof(MENU);

const MENU mainCtrM[] = {
    {"Power", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Source", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Vol +", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Vol -", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Chan +", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Chan -", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Mute", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Home", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Settings", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
};
const int copy_main_size = sizeof(mainCtrM) / sizeof(MENU);

const MENU btnCtrM[] = {
    {"1", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"2", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"3", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"4", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"5", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"6", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"7", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"8", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"9", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"0", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
};
const int copy_num_size = sizeof(btnCtrM) / sizeof(MENU);

const MENU navCtrM[] = {
    {"Up", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Down", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Left", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Right", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Ok", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Return", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Exit", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
};
const int copy_nav_size = sizeof(navCtrM) / sizeof(MENU);

const MENU miscCtrM[] = {
    {"CH List", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
    {"Info", Process::SAVE_CONTROLS, Process::COPY_REMOTE_CONTROLS},
};
const int copy_misc_size = sizeof(miscCtrM) / sizeof(MENU);

const MENU sendRContrM[] = {
    {"Main controls", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Num buttons", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"Navigation controls", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Misc controls", Process::SEND_MISC, Process::SEND_REMOTE_CONTROLS}};
const int send_remote_size = sizeof(sendRContrM) / sizeof(MENU);

const MENU mainCtrMSend[] = {
    {"Power", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Source", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Vol +", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Vol -", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Chan +", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Chan -", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Mute", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Home", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
    {"Settings", Process::SEND_MAIN_CONTROLS, Process::SEND_REMOTE_CONTROLS},
};
const int sendMainSize = sizeof(mainCtrMSend) / sizeof(MENU);

const MENU btnCtrMSend[] = {
    {"1", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"2", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"3", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"4", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"5", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"6", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"7", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"8", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"9", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
    {"0", Process::SEND_NUMBERS, Process::SEND_REMOTE_CONTROLS},
};
const int sendNumSize = sizeof(btnCtrMSend) / sizeof(MENU);

const MENU navCtrMSend[] = {
    {"Up", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Down", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Left", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Right", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Ok", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Return", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
    {"Exit", Process::SEND_NAVIGATION, Process::SEND_REMOTE_CONTROLS},
};
const int sendNavSize = sizeof(navCtrMSend) / sizeof(MENU);

const MENU miscCtrMSend[] = {
    {"CH List", Process::SEND_MISC, Process::SEND_REMOTE_CONTROLS},
    {"Info", Process::SEND_MISC, Process::SEND_REMOTE_CONTROLS},
};
const int sendMiscSize = sizeof(miscCtrMSend) / sizeof(MENU);

#endif

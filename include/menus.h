#ifndef MENUS_H
#define MENUS_H

#include <cstdint>


enum class Process
{
    EMPTY,
    MAIN_MENU,
    READ_MENU,
    SEND_MENU,
    SETTINGS,
    BATTERY_INFO,
    COPY_REMOTE_ENTER_NAME,
    COPY_REMOTE_CONTROLS,
    COPY_MAIN_CONTROLS,
    COPY_NUMBERS,
    COPY_NAVIGATION,
    COPY_MISC,
    LOAD_REMOTE,
    SAVE_CONTROLS,
    LOAD_REMOTE_INTO_MEMORY,
    SEND_REMOTE_CONTROLS,
    SEND_MAIN_CONTROLS,
    SEND_NUMBERS,
    SEND_NAVIGATION,
    SEND_MISC,
    SEND_COMMAND
};

struct MENU
{
    char name[23];
    Process command; // Use a pointer to Process
};

enum MarkType
{
    EMPTY,
    DOT,
    CHECK
};

/// MAIN MENU ///
const MENU mmenu[] = {
    {"Read signals", Process::READ_MENU},
    {"Send signals", Process::SEND_MENU},
    {"Copy remote", Process::COPY_REMOTE_ENTER_NAME},
    {"Load remote", Process::LOAD_REMOTE},
    {"Battery info", Process::BATTERY_INFO},
    {"Settings", Process::SETTINGS}};
const int mmenu_size = sizeof(mmenu) / sizeof(MENU);

const MENU copyRContrM[] = {
    {"Main controls", Process::COPY_MAIN_CONTROLS},
    {"Num buttons", Process::COPY_NUMBERS},
    {"Navigation controls", Process::COPY_NAVIGATION},
    {"Misc controls", Process::COPY_MISC}};
const int copy_remote_size = sizeof(copyRContrM) / sizeof(MENU);

const MENU mainCtrM[] = {
    {"Power", Process::SAVE_CONTROLS},
    {"Source", Process::SAVE_CONTROLS},
    {"Vol +", Process::SAVE_CONTROLS},
    {"Vol -", Process::SAVE_CONTROLS},
    {"Chan +", Process::SAVE_CONTROLS},
    {"Chan -", Process::SAVE_CONTROLS},
    {"Mute", Process::SAVE_CONTROLS},
    {"Home", Process::SAVE_CONTROLS},
    {"Settings", Process::SAVE_CONTROLS},
};
const int copy_main_size = sizeof(mainCtrM) / sizeof(MENU);

const MENU btnCtrM[] = {
    {"1", Process::SAVE_CONTROLS},
    {"2", Process::SAVE_CONTROLS},
    {"3", Process::SAVE_CONTROLS},
    {"4", Process::SAVE_CONTROLS},
    {"5", Process::SAVE_CONTROLS},
    {"6", Process::SAVE_CONTROLS},
    {"7", Process::SAVE_CONTROLS},
    {"8", Process::SAVE_CONTROLS},
    {"9", Process::SAVE_CONTROLS},
    {"0", Process::SAVE_CONTROLS},
};
const int copy_num_size = sizeof(btnCtrM) / sizeof(MENU);

const MENU navCtrM[] = {
    {"Up", Process::SAVE_CONTROLS},
    {"Down", Process::SAVE_CONTROLS},
    {"Left", Process::SAVE_CONTROLS},
    {"Right", Process::SAVE_CONTROLS},
    {"Ok", Process::SAVE_CONTROLS},
    {"Return", Process::SAVE_CONTROLS},
    {"Exit", Process::SAVE_CONTROLS},
};
const int copy_nav_size = sizeof(navCtrM) / sizeof(MENU);

const MENU miscCtrM[] = {
    {"CH List", Process::SAVE_CONTROLS},
    {"Info", Process::SAVE_CONTROLS},
};
const int copy_misc_size = sizeof(miscCtrM) / sizeof(MENU);

const MENU sendRContrM[] = {
    {"Main controls", Process::SEND_MAIN_CONTROLS},
    {"Num buttons", Process::SEND_NUMBERS},
    {"Navigation controls", Process::SEND_NAVIGATION},
    {"Misc controls", Process::SEND_MISC}};
const int send_remote_size = sizeof(sendRContrM) / sizeof(MENU);

const MENU mainCtrMSend[] = {
    {"Power", Process::SEND_COMMAND},
    {"Source", Process::SEND_COMMAND},
    {"Vol +", Process::SEND_COMMAND},
    {"Vol -", Process::SEND_COMMAND},
    {"Chan +", Process::SEND_COMMAND},
    {"Chan -", Process::SEND_COMMAND},
    {"Mute", Process::SEND_COMMAND},
    {"Home", Process::SEND_COMMAND},
    {"Settings", Process::SEND_COMMAND},
};
const int sendMainSize = sizeof(mainCtrMSend) / sizeof(MENU);

const MENU btnCtrMSend[] = {
    {"1", Process::SEND_COMMAND},
    {"2", Process::SEND_COMMAND},
    {"3", Process::SEND_COMMAND},
    {"4", Process::SEND_COMMAND},
    {"5", Process::SEND_COMMAND},
    {"6", Process::SEND_COMMAND},
    {"7", Process::SEND_COMMAND},
    {"8", Process::SEND_COMMAND},
    {"9", Process::SEND_COMMAND},
    {"0", Process::SEND_COMMAND},
};
const int sendNumSize = sizeof(btnCtrMSend) / sizeof(MENU);

const MENU navCtrMSend[] = {
    {"Up", Process::SEND_COMMAND},
    {"Down", Process::SEND_COMMAND},
    {"Left", Process::SEND_COMMAND},
    {"Right", Process::SEND_COMMAND},
    {"Ok", Process::SEND_COMMAND},
    {"Return", Process::SEND_COMMAND},
    {"Exit", Process::SEND_COMMAND},
};
const int sendNavSize = sizeof(navCtrMSend) / sizeof(MENU);

const MENU miscCtrMSend[] = {
    {"CH List", Process::SEND_COMMAND},
    {"Info", Process::SEND_COMMAND},
};
const int sendMiscSize = sizeof(miscCtrMSend) / sizeof(MENU);

#endif

#ifndef MENUS_H
#define MENUS_H

#include <cstdint>

struct MENU
{
    char name[23];
    uint8_t command;
};

enum MarkType
{
    EMPTY,
    DOT,
    CHECK
};

/// MAIN MENU ///
const MENU mmenu[] = {
    {"Read signals", 2}, // We jump to the region menu first
    {"Send signals", 3},
    {"Copy remote", 6},
    {"Load remote", 12},
    {"Battery info", 5},
    {"Settings", 4}};
const int mmenu_size = sizeof(mmenu) / sizeof(MENU);

const MENU copyRContrM[] = {
    {"Main controls", 8},
    {"Num buttons", 9},
    {"Navigation controls", 10},
    {"Misc controls", 11}};
const int copy_remote_size = sizeof(copyRContrM) / sizeof(MENU);

const MENU mainCtrM[] = {
    {"Power", 13},
    {"Source", 13},
    {"Vol +", 13},
    {"Vol -", 13},
    {"Chan +", 13},
    {"Chan -", 13},
    {"Mute", 13},
    {"Home", 13},
    {"Settings", 13},
};
const int copy_main_size = sizeof(mainCtrM) / sizeof(MENU);

const MENU btnCtrM[] = {
    {"1", 13},
    {"2", 13},
    {"3", 13},
    {"4", 13},
    {"5", 13},
    {"6", 13},
    {"7", 13},
    {"8", 13},
    {"9", 13},
    {"0", 13},
};
const int copy_num_size = sizeof(btnCtrM) / sizeof(MENU);

const MENU navCtrM[] = {
    {"Up", 13},
    {"Down", 13},
    {"Left", 13},
    {"Right", 13},
    {"Ok", 13},
    {"Return", 13},
    {"Exit", 13},
};
const int copy_nav_size = sizeof(navCtrM) / sizeof(MENU);

const MENU miscCtrM[] = {
    {"CH List", 13},
    {"Info", 13},
};
const int copy_misc_size = sizeof(miscCtrM) / sizeof(MENU);

const MENU sendRContrM[] = {
    {"Main controls", 16},
    {"Num buttons", 17},
    {"Navigation controls", 18},
    {"Misc controls", 19}};
const int send_remote_size = sizeof(sendRContrM) / sizeof(MENU);

const MENU mainCtrMSend[] = {
    {"Power", 20},
    {"Source", 20},
    {"Vol +", 20},
    {"Vol -", 20},
    {"Chan +", 20},
    {"Chan -", 20},
    {"Mute", 20},
    {"Home", 20},
    {"Settings", 20},
};
const int sendMainSize = sizeof(mainCtrMSend) / sizeof(MENU);

const MENU btnCtrMSend[] = {
    {"1", 20},
    {"2", 20},
    {"3", 20},
    {"4", 20},
    {"5", 20},
    {"6", 20},
    {"7", 20},
    {"8", 20},
    {"9", 20},
    {"0", 20},
};
const int sendNumSize = sizeof(btnCtrMSend) / sizeof(MENU);

const MENU navCtrMSend[] = {
    {"Up", 20},
    {"Down", 20},
    {"Left", 20},
    {"Right", 20},
    {"Ok", 20},
    {"Return", 20},
    {"Exit", 20},
};
const int sendNavSize = sizeof(navCtrMSend) / sizeof(MENU);

const MENU miscCtrMSend[] = {
    {"CH List", 20},
    {"Info", 20},
};
const int sendMiscSize = sizeof(miscCtrMSend) / sizeof(MENU);

#endif

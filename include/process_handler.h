#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

/// SWITCHER ///
// Proc codes
// 1  - Main Menu
// 2  - Read Menu
// 3  - Send Menu
// 4  - Settings
// 5  - Battery info
// 6  - Copy remote enter name
// 7  - Copy remote controls
// 8  - Copy main controls
// 9  - Copy numbers
// 10 - Copy navigation
// 11 - Copy misc
// 12 - Load remote
// 13 - Save controls
// 14 - Load remote into memory
// 15 - Send remote controls
// 16 - Send main controls
// 17 - Send numbers
// 18 - Send navigation
// 19 - Send misc
// 20 - Send command
// ===============================

#include "menus.h"

class ProcessHandler
{
private:
    Process currentProcess = Process::MAIN_MENU;
    Process prevProcess = Process::MAIN_MENU;
    Process sendProcess = Process::MAIN_MENU;

public:
    ProcessHandler();
    ~ProcessHandler();

    void setCurrentProcess(Process proc);
    Process getCurrentProcess();

    void savePrevProcess(Process proc);
    void savePrevProcess();
    Process getPrevProcess();

    void saveSendProcess();
    Process getSavedSendProcess();
};

#endif

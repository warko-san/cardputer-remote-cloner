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

class ProcessHandler
{
private:
    int current_proc = 1;
    int saved_proc = 1;

public:
    ProcessHandler();
    ~ProcessHandler();

    void setCurrentProcess(int proc);
    int getCurrentProcess();

    void saveProcess();
    int getSavedProcess();
};

#endif

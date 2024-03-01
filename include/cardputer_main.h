#ifndef CARDPUTER_MAIN_H
#define CARDPUTER_MAIN_H
#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE

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
// 21 - Deauth Attack
// .. - ..
// 97 - Mount/UnMount SD Card on M5Stick devices, if SDCARD is declared

class SDcard* sdCard;
class MenuHandler* menuHandler;
class ProcessHandler* processHandler;
class ComandSaver* comandSaver;

#endif
#ifndef COMAND_SAVER_H
#define COMAND_SAVER_H

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE

#include <WString.h>
#include "process.h"
#include "ir_handler.h"

class ProcessHandler;
class MenuHandler;
class SDcard;
class IRHandler;
class ScreenProvider;

class ComandSaver
{
private:
public:
    ComandSaver();
    ~ComandSaver();

    String data;
    uint8_t saveConfirmations = 0;

    void copyKeySetup(ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler, ScreenProvider &screenProvider, MenuHandler &menuHandler);
    // void copyKeyLoop(MenuHandler &menuHandler, ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler);
    void saveCommand(IRData prevData, IRData currentData, ScreenProvider &ScreenProvider, ProcessHandler &processHandler, MenuHandler &MenuHandler, SDcard &sdCard);
};
#endif

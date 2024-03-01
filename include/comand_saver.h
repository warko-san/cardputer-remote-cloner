#ifndef COMAND_SAVER_H
#define COMAND_SAVER_H

#include <WString.h>

class ProcessHandler;
class MenuHandler;
class SDcard;
class IRHandler;

class ComandSaver
{
private:
  
public:
    ComandSaver();
    ~ComandSaver();

    String data;

    void copyKeySetup(ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler);
    void copyKeyLoop(MenuHandler &menuHandler, ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler);
};
#endif

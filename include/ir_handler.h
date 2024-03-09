#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include "process.h"

#include "definitions.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

class ComandSaver;
class ScreenProvider;
class ProcessHandler;
class SDcard;
class MenuHandler;

struct MenuIr
{
    char name[19];
    IRData receivedIRData;
};

class IRHandler
{
private:
    IRData lastDecodedData = IrReceiver.decodedIRData;
public:
    IRHandler();
    ~IRHandler();

    MenuIr sendMenu[52] = {
        {"Send signals:", IRData()}};

    IRData mainControls[9] = {};
    IRData numControls[10] = {};
    IRData navControls[7] = {};
    IRData miscControls[2] = {};

    uint8_t currentStoredCodes = 1;
    uint8_t selectedSavedCode = 0;

    uint16_t lastAddress = 0;
    uint16_t lastCommand = 0;

    IRData receivedIRData;
    IRData irDataArray[52];
    // extensions for sendRaw
    uint8_t rawCode[RAW_BUFFER_LENGTH]; // The durations if raw
    uint8_t rawCodeLength;     

    void readSetup();
    void SendSetup();
    void plainDecodeLoop(ScreenProvider &screenProvider);
    void decodeLoop(ComandSaver &comandSaver, ScreenProvider &screenProvider, ProcessHandler &processHandler, MenuHandler &menuHandler, SDcard &sdCard);
    void StoreCode();
    void SendCode(IRData *aIRDataToSend);
    void sendCode(Process currentProcess, uint8_t cursor);
};
constexpr uint8_t DELAY_BETWEEN_REPEAT = 250;
#endif
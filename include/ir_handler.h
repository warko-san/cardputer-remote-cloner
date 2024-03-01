#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include "definitions.h" // Define macros for input and output pin etc.



#include <IRremote.hpp>

// Storage for the recorded code
struct StoredIRDataStruct
{
    IRData receivedIRData;
    IRData irDataArray[52];
    // extensions for sendRaw
    uint8_t rawCode[RAW_BUFFER_LENGTH]; // The durations if raw
    uint8_t rawCodeLength;              // The length of the code
};

struct MenuIr
{
    char name[19];
    IRData receivedIRData;
};

namespace ir_handler
{
    extern StoredIRDataStruct sStoredIRData;
    extern IRData sIRData;
    extern MenuIr sendMenu[52];
    extern IRData mainControls[9];
    extern IRData numControls[10];
    extern IRData navControls[7];
    extern IRData miscControls[2];

    extern uint8_t currentStoredCodes;
    extern uint8_t selectedSavedCode;
}

class IRHandler
{
private:
public:
    IRHandler();
    ~IRHandler();

    void readSetup();
    void SendSetup();
    bool Decode();
    void Resume();
    void StoreCode();
    void SendCode(IRData *aIRDataToSend);
};
constexpr uint8_t DELAY_BETWEEN_REPEAT = 250;
#endif
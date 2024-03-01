#include "ir_handler.h"

namespace ir_handler
{
    // Storage for the recorded code
    StoredIRDataStruct sStoredIRData;

    MenuIr sendMenu[52] = {
        {"Send signals:", sStoredIRData.receivedIRData}};

    IRData mainControls[9] = {};
    IRData numControls[10] = {};
    IRData navControls[7] = {};
    IRData miscControls[2] = {};
    IRData sIRData;

    uint8_t currentStoredCodes = 1;
    uint8_t selectedSavedCode = 0;
} // namespace ir_handler

IRHandler::IRHandler()
{
}

IRHandler::~IRHandler()
{
}

void IRHandler::readSetup()
{
    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
    IrReceiver.start();
}

void IRHandler::SendSetup()
{
    IrReceiver.stop();
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable
}

bool IRHandler::Decode()
{
    return IrReceiver.decode();
}

void IRHandler::Resume()
{
    IrReceiver.resume();
}

// Stores the code for later playback in sStoredIRData
// Most of this code is just logging
void IRHandler::StoreCode()
{
    if (IrReceiver.decodedIRData.rawDataPtr->rawlen < 4)
    {
        Serial.print(F("Ignore data with rawlen="));
        Serial.println(IrReceiver.decodedIRData.rawDataPtr->rawlen);
        return;
    }
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)
    {
        Serial.println(F("Ignore repeat"));
        return;
    }
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_AUTO_REPEAT)
    {
        Serial.println(F("Ignore autorepeat"));
        return;
    }
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_PARITY_FAILED)
    {
        Serial.println(F("Ignore parity error"));
        return;
    }
    /*
     * Copy decoded data
     */
    ir_handler::sStoredIRData.receivedIRData = IrReceiver.decodedIRData;

    snprintf(ir_handler::sendMenu[ir_handler::currentStoredCodes].name, sizeof(ir_handler::sendMenu[ir_handler::currentStoredCodes].name), "%X", IrReceiver.decodedIRData.command);
    ir_handler::sendMenu[ir_handler::currentStoredCodes].receivedIRData = IrReceiver.decodedIRData;
    ir_handler::currentStoredCodes++;

    if (ir_handler::sStoredIRData.receivedIRData.protocol == UNKNOWN)
    {
        Serial.print(F("Received unknown code and store "));
        Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
        Serial.println(F(" timing entries as raw "));
        IrReceiver.printIRResultRawFormatted(&Serial, true); // Output the results in RAW format
        ir_handler::sStoredIRData.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
        /*
         * Store the current raw data in a dedicated array for later usage
         */
        IrReceiver.compensateAndStoreIRResultInArray(ir_handler::sStoredIRData.rawCode);
    }
    else
    {
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        ir_handler::sStoredIRData.receivedIRData.flags = 0; // clear flags -esp. repeat- for later sending
        Serial.println();
    }
}

void IRHandler::SendCode(IRData *aIRDataToSend)
{
    if (aIRDataToSend->protocol == UNKNOWN)
        return;
    // if (aIRDataToSend->receivedIRData.protocol == UNKNOWN /* i.e. raw */) {
    //   // Assume 38 KHz
    //   IrSender.sendRaw(aIRDataToSend->rawCode, aIRDataToSend->rawCodeLength, 38);

    //   Serial.print(F("raw "));
    //   Serial.print(aIRDataToSend->rawCodeLength);
    //   Serial.println(F(" marks or spaces"));
    // } else {

    //   /*
    //        * Use the write function, which does the switch for different protocols
    //        */
    //   IrSender.write(&aIRDataToSend->irDataArray[selectedSavedCode]);
    //   printIRResultShort(&Serial, &aIRDataToSend->irDataArray[selectedSavedCode], false);
    // }
    /*
     * Use the write function, which does the switch for different protocols
     */

    IrSender.write(aIRDataToSend);
    printIRResultShort(&Serial, aIRDataToSend, false);
}
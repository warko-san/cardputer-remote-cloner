#include "comand_saver.h"
#include "task_manager.h"

ComandSaver::ComandSaver()
{
}

ComandSaver::~ComandSaver()
{
}

void ComandSaver::copyKeySetup(ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler)
{
    switch (processHandler.getSavedProcess())
    {
    case 8:
        if (!sdCard.exists((sdCard.rootDir + data + "/main_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/main_controls.bin").c_str());
        }
        break;
    case 9:
        if (!sdCard.exists((sdCard.rootDir + data + "/num_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/num_controls.bin").c_str());
        }
        break;
    case 10:
        if (!sdCard.exists((sdCard.rootDir + data + "/nav_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/nav_controls.bin").c_str());
        }
        break;
    case 11:
        if (!sdCard.exists((sdCard.rootDir + data + "/misc_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/misc_controls.bin").c_str());
        }
        break;
    }
    irHandler.readSetup();
    delay(200);
}

void ComandSaver::copyKeyLoop(MenuHandler &menuHandler, ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler)
{
    menuHandler.copyKeyInternalLoop();

    IRData lastDecodedData = IrReceiver.decodedIRData;
    if (irHandler.Decode())
    {
        printIRResultShort(&Serial, &IrReceiver.decodedIRData, false);
        switch (processHandler.getSavedProcess())
        {
        case 8:
            if (lastDecodedData.command == IrReceiver.decodedIRData.command && lastDecodedData.address == IrReceiver.decodedIRData.address && lastDecodedData.protocol == IrReceiver.decodedIRData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/main_controls.bin").c_str(), IrReceiver.decodedIRData);
                    menuHandler.drawmenu(mainCtrM, copy_main_size, MarkType::CHECK);
                    sdCard.saveConfirmations++;
                }
            }
            else
            {
                menuHandler.drawmenu(mainCtrM, copy_main_size, MarkType::DOT);
                sdCard.saveConfirmations++;
            }
            break;
        case 9:
            if (lastDecodedData.command == IrReceiver.decodedIRData.command && lastDecodedData.address == IrReceiver.decodedIRData.address && lastDecodedData.protocol == IrReceiver.decodedIRData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/num_controls.bin").c_str(), IrReceiver.decodedIRData);
                    menuHandler.drawmenu(btnCtrM, copy_num_size, MarkType::CHECK);
                    sdCard.saveConfirmations++;
                }
            }
            else
            {
                menuHandler.drawmenu(btnCtrM, copy_num_size, MarkType::DOT);
                sdCard.saveConfirmations++;
            }
            break;
        case 10:
            if (lastDecodedData.command == IrReceiver.decodedIRData.command && lastDecodedData.address == IrReceiver.decodedIRData.address && lastDecodedData.protocol == IrReceiver.decodedIRData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/nav_controls.bin").c_str(), IrReceiver.decodedIRData);
                   menuHandler.drawmenu(navCtrM, copy_nav_size, MarkType::CHECK);
                    sdCard.saveConfirmations++;
                }
            }
            else
            {
                menuHandler.drawmenu(navCtrM, copy_nav_size, MarkType::DOT);
                sdCard.saveConfirmations++;
            }
            break;
        case 11:
            if (lastDecodedData.command == IrReceiver.decodedIRData.command && lastDecodedData.address == IrReceiver.decodedIRData.address && lastDecodedData.protocol == IrReceiver.decodedIRData.protocol)
            {
                if (sdCard.saveConfirmations = 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/misc_controls.bin").c_str(), IrReceiver.decodedIRData);
                    menuHandler.drawmenu(miscCtrM, copy_misc_size, MarkType::CHECK);
                    sdCard.saveConfirmations++;
                }
            }
            else
            {
                menuHandler.drawmenu(miscCtrM, copy_misc_size, MarkType::DOT);
                sdCard.saveConfirmations++;
            }
            break;
        }
        if (IrReceiver.decodedIRData.protocol == UNKNOWN)
        {
            irHandler.Resume();
            return;
        }
        else
        {
            lastDecodedData = IrReceiver.decodedIRData;
        }

        delay(300);
        irHandler.Resume(); // resume receiver
    }
}
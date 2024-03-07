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
    switch (processHandler.getSavedSendProcess())
    {
    case Process::COPY_MAIN_CONTROLS:
        if (!sdCard.exists((sdCard.rootDir + data + "/main_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/main_controls.bin").c_str());
        }
        break;
    case Process::COPY_NUMBERS:
        if (!sdCard.exists((sdCard.rootDir + data + "/num_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/num_controls.bin").c_str());
        }
        break;
    case Process::COPY_NAVIGATION:
        if (!sdCard.exists((sdCard.rootDir + data + "/nav_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/nav_controls.bin").c_str());
        }
        break;
    case Process::COPY_MISC:
        if (!sdCard.exists((sdCard.rootDir + data + "/misc_controls.bin").c_str()))
        {
            sdCard.createEmptyFile((sdCard.rootDir + data + "/misc_controls.bin").c_str());
        }
        break;
    }
    irHandler.readSetup();
    delay(200);
}

// void ComandSaver::copyKeyLoop(ScreenProvider &ScreenProvider, ProcessHandler &processHandler, SDcard &sdCard)
// {
//     menuHandler.copyKeyInternalLoop();

    
//     if (irHandler.Decode())
//     {
//         printIRResultShort(&Serial, &currentData, false);
        
//         if (currentData.protocol == UNKNOWN)
//         {
//             irHandler.Resume();
//             return;
//         }
//         else
//         {
//             prevData = currentData;
//         }

//         delay(300);
//         irHandler.Resume(); // resume receiver
//     }
// }

void ComandSaver::saveCommand(IRData prevData, IRData currentData, ScreenProvider &ScreenProvider, ProcessHandler &processHandler, SDcard &sdCard)
{
    switch (processHandler.getSavedSendProcess())
        {
        case Process::COPY_MAIN_CONTROLS:
            if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/main_controls.bin").c_str(), currentData);
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
        case Process::COPY_NUMBERS:
            if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/num_controls.bin").c_str(), currentData);
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
        case Process::COPY_NAVIGATION:
            if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
            {
                if (sdCard.saveConfirmations == 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/nav_controls.bin").c_str(), currentData);
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
        case Process::COPY_MISC:
            if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
            {
                if (sdCard.saveConfirmations = 1)
                {
                    sdCard.appendToFileIrData((sdCard.rootDir + data + "/misc_controls.bin").c_str(), currentData);
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
}
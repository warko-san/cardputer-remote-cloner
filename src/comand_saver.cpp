#include "comand_saver.h"
#include "task_manager.h"

ComandSaver::ComandSaver()
{
}

ComandSaver::~ComandSaver()
{
}

void ComandSaver::copyKeySetup(ProcessHandler &processHandler, SDcard &sdCard, IRHandler &irHandler, ScreenProvider &screenProvider, MenuHandler &menuHandler)
{
    switch (processHandler.getSavedSendProcess())
    {
    case Process::COPY_MAIN_CONTROLS:
        sdCard.createEmptyFile((sdCard.rootDir + data + FILE_MAIN_CONTROLS).c_str());
        break;
    case Process::COPY_NUMBERS:
        sdCard.createEmptyFile((sdCard.rootDir + data + FILE_NUM_CONTROLS).c_str());
        break;
    case Process::COPY_NAVIGATION:
        sdCard.createEmptyFile((sdCard.rootDir + data + FILE_NAV_CONTROLS).c_str());
        break;
    case Process::COPY_MISC:
        sdCard.createEmptyFile((sdCard.rootDir + data + FILE_MISC_CONTROLS).c_str());
        break;
    }
    irHandler.readSetup();
    delay(200);
}

void ComandSaver::saveCommand(IRData prevData, IRData currentData, ScreenProvider &screenProvider, ProcessHandler &processHandler, MenuHandler &menuHandler, SDcard &sdCard)
{
    switch (processHandler.getSavedSendProcess())
    {
    case Process::COPY_MAIN_CONTROLS:
        if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
        {
            if (saveConfirmations == 1 && !comandSaved)
            {
                sdCard.appendToFileIrData((sdCard.rootDir + data + FILE_MAIN_CONTROLS).c_str(), currentData);
                screenProvider.printCommandData(currentData.address, currentData.command, false, comandSaved);
                comandSaved = true;
                saveConfirmations++;
            }
        }
        else
        {
            screenProvider.printCommandData(currentData.address, currentData.command, true, comandSaved);
            saveConfirmations++;
        }
        break;
    case Process::COPY_NUMBERS:
        if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
        {
            if (saveConfirmations == 1 && !comandSaved)
            {
                sdCard.appendToFileIrData((sdCard.rootDir + data + FILE_NUM_CONTROLS).c_str(), currentData);
                screenProvider.printCommandData(currentData.address, currentData.command, false, comandSaved);
                comandSaved = true;
                saveConfirmations++;
            }
        }
        else
        {
            screenProvider.printCommandData(currentData.address, currentData.command, true, comandSaved);
            saveConfirmations++;
        }
        break;
    case Process::COPY_NAVIGATION:
        if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
        {
            if (saveConfirmations == 1 && !comandSaved)
            {
                sdCard.appendToFileIrData((sdCard.rootDir + data + FILE_NAV_CONTROLS).c_str(), currentData);
                screenProvider.printCommandData(currentData.address, currentData.command, false, comandSaved);
                comandSaved = true;
                saveConfirmations++;
            }
        }
        else
        {
            screenProvider.printCommandData(currentData.address, currentData.command, true, comandSaved);
            saveConfirmations++;
        }
        break;
    case Process::COPY_MISC:
        if (prevData.command == currentData.command && prevData.address == currentData.address && prevData.protocol == currentData.protocol)
        {
            if (saveConfirmations == 1 && !comandSaved)
            {
                sdCard.appendToFileIrData((sdCard.rootDir + data + FILE_MISC_CONTROLS).c_str(), currentData);
                screenProvider.printCommandData(currentData.address, currentData.command, false, comandSaved);
                comandSaved = true;
                saveConfirmations++;
            }
        }
        else
        {
            screenProvider.printCommandData(currentData.address, currentData.command, true, comandSaved);
            saveConfirmations++;
        }
        break;
    }
}
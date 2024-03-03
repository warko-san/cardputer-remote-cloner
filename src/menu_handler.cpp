#include "menu_handler.h"
#include "task_manager.h"

MenuHandler::MenuHandler(ProcessHandler &processHandler, SDcard &sdCard, ComandSaver &comandSaver, IRHandler &irHandler) : processHandler(processHandler), sdCard(sdCard), comandSaver(comandSaver), irHandler(irHandler)
{
}

void MenuHandler::drawmenu(const MENU thismenu[], int size, MarkType mark)
{
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 5);
    // scrolling menu
    if (cursor < 0)
    {
        cursor = size - 1; // rollover hack for up-arrow on cardputer
    }
    if (cursor > 5)
    {
        for (int i = 0 + (cursor - 5); i < size; i++)
        {
            DISP.print((cursor == i) ? ">" : " ");
            if (cursor == i)
            {
                switch (mark)
                {
                case MarkType::EMPTY:
                    DISP.print(thismenu[i].name);
                    DISP.println("     ");
                    break;

                case MarkType::DOT:
                    DISP.print(thismenu[i].name);
                    DISP.println("    .");
                    break;
                case MarkType::CHECK:
                    DISP.print(thismenu[i].name);
                    DISP.println("   ..");
                    break;
                }
            }
            else
            {
                DISP.println(thismenu[i].name);
            }
        }
    }
    else
    {
        for (
            int i = 0; i < size; i++)
        {
            DISP.print((cursor == i) ? ">" : " ");
            if (cursor == i)
            {
                switch (mark)
                {
                case MarkType::EMPTY:
                    DISP.print(thismenu[i].name);
                    DISP.println("     ");
                    break;

                case MarkType::DOT:
                    DISP.print(thismenu[i].name);
                    DISP.println("    .");
                    break;
                case MarkType::CHECK:
                    DISP.print(thismenu[i].name);
                    DISP.println("   ..");
                    break;
                }
            }
            else
            {
                DISP.println(thismenu[i].name);
            }
        }
    }
}

void MenuHandler::drawmenu(MenuIr thismenu[], int size)
{
    DISP.setTextSize(SMALL_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 5);
    // scrolling menu
    if (cursor < 0)
    {
        cursor = size - 1; // rollover hack for up-arrow on cardputer
    }
    if (cursor > 5)
    {
        for (int i = 0 + (cursor - 5); i < size; i++)
        {
            if (i == 0)
            {
                DISP.setTextColor(FGCOLOR, BGCOLOR);
                DISP.print((cursor == i) ? ">" : " ");
                DISP.println(thismenu[i].name);
            }
            else
            {
                DISP.setTextColor(WHITE, BGCOLOR);
                DISP.print((cursor == i) ? ">" : " ");
                DISP.print(F(" Command=0x"));
                DISP.println(thismenu[i].name);
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                DISP.setTextColor(FGCOLOR, BGCOLOR);
                DISP.print((cursor == i) ? ">" : " ");
                DISP.println(thismenu[i].name);
            }
            else
            {
                DISP.setTextColor(WHITE, BGCOLOR);
                DISP.print((cursor == i) ? ">" : " ");
                DISP.print(F(" Command=0x"));
                DISP.println(thismenu[i].name);
            }
        }
    }
}

void MenuHandler::drawmenu(String thismenu[], int size)
{
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 5);
    // scrolling menu
    if (cursor < 0)
    {
        cursor = size - 1; // rollover hack for up-arrow on cardputer
    }
    if (cursor > 5)
    {
        for (int i = 0 + (cursor - 5); i < size; i++)
        {
            DISP.print((cursor == i) ? ">" : " ");
            DISP.println(thismenu[i]);
        }
    }
    else
    {
        for (
            int i = 0; i < size; i++)
        {
            DISP.print((cursor == i) ? ">" : " ");
            DISP.println(thismenu[i]);
        }
    }
}

bool MenuHandler::check_select_press()
{
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/'))
    {
        // dimtimer();
        return true;
    }
    return false;
}

bool MenuHandler::check_next_press()
{
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed(';'))
    {
        // hack to handle the up arrow
        cursor = cursor - 2;
        return true;
    }
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.'))
    {
        // dimtimer();
        return true;
    }
    return false;
}

void MenuHandler::switcher_button_proc()
{
    if (rstOverride == false)
    {
        if (check_next_press())
        {
            isSwitching = true;
            processHandler.setCurrentProcess(Process::MAIN_MENU);
        }
    }
}

// Tap the power button from pretty much anywhere to get to the main menu
void MenuHandler::check_menu_press()
{
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed('`'))
    {
        isSwitching = true;
        rstOverride = false;
        processHandler.setCurrentProcess(Process::MAIN_MENU);
        delay(100);
    }
}

void MenuHandler::checkBackPress()
{
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed(','))
    {
        isSwitching = true;
        rstOverride = false;
        processHandler.setCurrentProcess(processHandler.getPrevProcess());
        delay(100);
    }
}

void MenuHandler::mmenu_setup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(mmenu, mmenu_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::mmenu_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % mmenu_size;
        drawmenu(mmenu, mmenu_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.setCurrentProcess(mmenu[cursor].command);
    }
}

void MenuHandler::read_setup()
{
    cursor = 0;
    // rstOverride = true;
    DISP.clearDisplay();
    DISP.setTextColor(WHITE);
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.setCursor(10, 20);
    DISP.println("Reading:");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);

    processHandler.savePrevProcess(Process::MAIN_MENU);
    irHandler.readSetup();
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::read_loop()
{
    if (irHandler.Decode())
    {
        DISP.setCursor(10, 50);
        DISP.print("Address:");
        DISP.println(IrReceiver.decodedIRData.address, HEX);
        DISP.fillRect(10, 70, DISP.width(), 20, BGCOLOR); // Reset the back of line
        DISP.setCursor(10, 70);
        DISP.print("Command: 0x");
        DISP.println(IrReceiver.decodedIRData.command, HEX);
        irHandler.StoreCode();
        irHandler.Resume(); // resume receiver
    }
    delay(200);
}

void MenuHandler::send_setup()
{
    irHandler.SendSetup();
    cursor = 0;
    // rstOverride = true;
    processHandler.savePrevProcess(Process::MAIN_MENU);
    drawmenu(irHandler.sendMenu, irHandler.currentStoredCodes);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::send_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % irHandler.currentStoredCodes;
        drawmenu(irHandler.sendMenu, irHandler.currentStoredCodes);
        delay(250);
    }
    if (check_select_press())
    {
        irHandler.SendCode(&irHandler.sendMenu[cursor].receivedIRData);
        delay(DELAY_BETWEEN_REPEAT);
    }
}

void MenuHandler::battery_drawmenu(uint8_t battery)
{
    // Battery bar color definition
    uint16_t batteryBarColor = BLUE;
    if (battery < 20)
    {
        batteryBarColor = RED;
    }
    else if (battery < 60)
    {
        batteryBarColor = ORANGE;
    }
    else
    {
        batteryBarColor = GREEN;
    }
    // Battery bar
    DISP.fillScreen(BGCOLOR);
    DISP.drawRect(10, 10, 220, 100, batteryBarColor);
    DISP.fillRect(10, 10, (220 * battery / 100), 100, batteryBarColor);
    // Battery percentage
    DISP.setTextColor(WHITE);
    DISP.setTextSize(BIG_TEXT);
    DISP.setCursor(80, 45);
    DISP.print(battery);
    DISP.println("%");
    // Exit text
    DISP.setCursor(10, 120);
    DISP.setTextSize(TINY_TEXT);
    DISP.println("Exit");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void MenuHandler::battery_setup()
{
    rstOverride = false;
    pinMode(VBAT_PIN, INPUT);
    uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
    processHandler.savePrevProcess(Process::MAIN_MENU);
    battery_drawmenu(battery);
    delay(500); // Prevent switching after menu loads up
                /*
                    Used minimum 3,0V and maximum 4,2V for battery. So it may show wrong values. Needs testing.
                    It only shows decent values when disconnected from charger, due to HW limitations.
                    Equation: Bat% = ((Vadc - 1842) / (2580 - 1842)) * 100. Where: 4,2V = 2580, 3,0V = 1842.
                  */
}

void MenuHandler::battery_loop()
{
    // Read 30 battery values to calculate the average (avoiding unprecise and close values)
    uint16_t batteryValues = 0;
    for (uint8_t i = 0; i < 30; i++)
    { // 30 iterations X 100ms = 3 seconds for each refresh
        delay(100);
        batteryValues += ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed())
        { // If any key is pressed
            rstOverride = false;
            isSwitching = true;
            break;
        }
    }

    if (!isSwitching)
    {                                         // If is not switching, calculate battery average
        uint8_t battery = batteryValues / 30; // Iteration times
        Serial.printf("Battery Level: %d\n", battery);
        if (battery != oldBattery)
        { // Only draw a new screen if value is different
            oldBattery = battery;
            battery_drawmenu(battery);
        }
    }
}

void MenuHandler::settings_setup()
{
}

void MenuHandler::settings_loop()
{
}

void MenuHandler::enter_name_setup()
{
    DISP.clear();
    DISP.setCursor(10, 10);
    DISP.println("Enter remote name");
    DISP.setCursor(10, DISP.height() - 48);
    DISP.println(">");
    data = "";
    processHandler.savePrevProcess(Process::MAIN_MENU);

    delay(400);
}

void MenuHandler::enter_name_loop()
{
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange())
    {
        if (M5Cardputer.Keyboard.isPressed())
        {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (auto i : status.word)
            {
                data += i;
            }

            if (status.del)
            {
                data.remove(data.length() - 1);
            }

            if (status.enter)
            {
                if (data.indexOf('/') != -1)
                {
                    sdCard.createDir((sdCard.rootDir + data).c_str());
                }
                else
                {
                    data = "/" + data;
                    sdCard.createDir((sdCard.rootDir + data).c_str());
                }
                comandSaver.data = data;
                isSwitching = true;
                processHandler.setCurrentProcess(Process::COPY_REMOTE_CONTROLS);
            }

            DISP.fillRect(25, DISP.height() - 48, DISP.width(), 25, BLACK);

            DISP.setCursor(25, DISP.height() - 48);
            DISP.print(data);
        }
    }
}

void MenuHandler::copy_menu_setup()
{
    cursor = 0;
    // rstOverride = true;
    drawmenu(copyRContrM, copy_remote_size);
    processHandler.savePrevProcess(Process::MAIN_MENU);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::copy_menu_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % copy_remote_size;
        drawmenu(copyRContrM, copy_remote_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(copyRContrM[cursor].backProcess);
        processHandler.setCurrentProcess(copyRContrM[cursor].command);
        processHandler.saveSendProcess();
    }
}

void MenuHandler::copy_main_contr_setup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(mainCtrM, copy_main_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::copy_main_contr_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % copy_main_size;
        drawmenu(mainCtrM, copy_main_size);
        delay(250);
    }
    if (check_select_press())
    {
        // rstOverride = true;
        isSwitching = true;
        processHandler.savePrevProcess(mainCtrM[cursor].backProcess);
        processHandler.setCurrentProcess(mainCtrM[cursor].command);
    }
}

void MenuHandler::copy_num_setup()
{
    cursor = 0;
    // rstOverride = true;
    drawmenu(btnCtrM, copy_num_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::copy_num_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % copy_num_size;
        drawmenu(btnCtrM, copy_num_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(btnCtrM[cursor].backProcess);
        processHandler.setCurrentProcess(btnCtrM[cursor].command);
    }
}

void MenuHandler::copy_nav_setup()
{
    cursor = 0;
    // rstOverride = true;
    drawmenu(navCtrM, copy_nav_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::copy_nav_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % copy_nav_size;
        drawmenu(navCtrM, copy_nav_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(navCtrM[cursor].backProcess);
        processHandler.setCurrentProcess(navCtrM[cursor].command);
    }
}

void MenuHandler::copy_misc_setup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(miscCtrM, copy_misc_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::copy_misc_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % copy_misc_size;
        drawmenu(miscCtrM, copy_misc_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(miscCtrM[cursor].backProcess);
        processHandler.setCurrentProcess(miscCtrM[cursor].command);
    }
}

void MenuHandler::load_remote_setup()
{
    cursor = 0;
    sdCard.listDir(sdCard.rootDir.c_str());
    drawmenu(sdCard.dirs, sdCard.dirCount);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::load_remote_loop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % sdCard.dirCount;
        drawmenu(sdCard.dirs, sdCard.dirCount);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        loadedDir = sdCard.dirs[cursor];
        processHandler.savePrevProcess();
        processHandler.setCurrentProcess(Process::LOAD_REMOTE_INTO_MEMORY);
    }
}

void MenuHandler::loadRemoteControlsSetup()
{
    sdCard.loadIrDataFromFile((sdCard.rootDir + "/" + loadedDir + "/main_controls.bin").c_str(), irHandler.mainControls, 9);
    sdCard.loadIrDataFromFile((sdCard.rootDir + "/" + loadedDir + "/num_controls.bin").c_str(), irHandler.numControls, 10);
    sdCard.loadIrDataFromFile((sdCard.rootDir + "/" + loadedDir + "/nav_controls.bin").c_str(), irHandler.navControls, 7);
    sdCard.loadIrDataFromFile((sdCard.rootDir + "/" + loadedDir + "/misc_controls.bin").c_str(), irHandler.miscControls, 2);
    isSwitching = true;
    processHandler.setCurrentProcess(Process::SEND_REMOTE_CONTROLS);
    delay(500);
}

void MenuHandler::loadRemoteControlsLoop()
{
}

void MenuHandler::sendControlSetup()
{
    irHandler.SendSetup();
}

void MenuHandler::sendControlLoop()
{
    if (check_next_press())
    {
        cursor++;
        Serial.printf("Saved send process is: %d\n", processHandler.getSavedSendProcess());
        switch (processHandler.getSavedSendProcess())
        {
        case Process::SEND_MAIN_CONTROLS:
            cursor = cursor % sendMainSize;
            drawmenu(mainCtrMSend, sendMainSize);
            break;

        case Process::SEND_NUMBERS:
            cursor = cursor % sendNumSize;
            drawmenu(btnCtrMSend, sendNumSize);
            break;

        case Process::SEND_NAVIGATION:
            cursor = cursor % sendNavSize;
            drawmenu(navCtrMSend, sendNavSize);
            break;

        case Process::SEND_MISC:
            cursor = cursor % sendMiscSize;
            drawmenu(miscCtrMSend, sendMiscSize);
            break;
        }
    }
    delay(250);

    if (check_select_press())
    {
        switch (processHandler.getSavedSendProcess())
        {
        case Process::SEND_MAIN_CONTROLS:
            irHandler.SendCode(&irHandler.mainControls[cursor]);
            delay(DELAY_BETWEEN_REPEAT);
            break;
        case Process::SEND_NUMBERS:
            irHandler.SendCode(&irHandler.numControls[cursor]);
            delay(DELAY_BETWEEN_REPEAT);
            break;
        case Process::SEND_NAVIGATION:
            irHandler.SendCode(&irHandler.navControls[cursor]);
            delay(DELAY_BETWEEN_REPEAT);
            break;
        case Process::SEND_MISC:
            irHandler.SendCode(&irHandler.miscControls[cursor]);
            delay(DELAY_BETWEEN_REPEAT);
            break;
        }
    }
}

void MenuHandler::sendMenuSetup()
{
    cursor = 0;
    //  rstOverride = true;
    processHandler.savePrevProcess(Process::LOAD_REMOTE);
    drawmenu(sendRContrM, send_remote_size);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::sendMenuLoop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % send_remote_size;
        drawmenu(sendRContrM, send_remote_size);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(sendRContrM[cursor].backProcess);
        processHandler.setCurrentProcess(sendRContrM[cursor].command);
        processHandler.saveSendProcess();
    }
}

void MenuHandler::sendMainCtrlSetup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(mainCtrMSend, sendMainSize);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::sendMainCtrlLoop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % sendMainSize;
        drawmenu(mainCtrMSend, sendMainSize);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(mainCtrMSend[cursor].backProcess);
        processHandler.setCurrentProcess(mainCtrMSend[cursor].command);
    }
}

void MenuHandler::sendNumCtrlSetup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(btnCtrMSend, sendNumSize);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::sendNumCtrlLoop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % sendNumSize;
        drawmenu(btnCtrMSend, sendNumSize);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(btnCtrMSend[cursor].backProcess);
        processHandler.setCurrentProcess(btnCtrMSend[cursor].command);
    }
}

void MenuHandler::sendNavCtrlSetup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(navCtrMSend, sendNavSize);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::sendNavCtrlLoop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % sendNavSize;
        drawmenu(navCtrMSend, sendNavSize);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(navCtrMSend[cursor].backProcess);
        processHandler.setCurrentProcess(navCtrMSend[cursor].command);
    }
}

void MenuHandler::sendMiscCtrlSetup()
{
    cursor = 0;
    //  rstOverride = true;
    drawmenu(miscCtrMSend, sendMiscSize);
    delay(500); // Prevent switching after menu loads up
}

void MenuHandler::sendMiscCtrlLoop()
{
    if (check_next_press())
    {
        cursor++;
        cursor = cursor % sendMiscSize;
        drawmenu(miscCtrMSend, sendMiscSize);
        delay(250);
    }
    if (check_select_press())
    {
        rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess(miscCtrMSend[cursor].backProcess);
        processHandler.setCurrentProcess(miscCtrMSend[cursor].command);
    }
}

void MenuHandler::copyKeyInternalLoop()
{
    if (check_select_press())
    {
        // rstOverride = false;
        isSwitching = true;
        processHandler.savePrevProcess();
        processHandler.setCurrentProcess(Process::COPY_REMOTE_CONTROLS);
    }

    if (check_next_press())
    {
        cursor++;
        sdCard.saveConfirmations = 0;

        switch (processHandler.getSavedSendProcess())
        {
        case Process::COPY_MAIN_CONTROLS:
            cursor = cursor % copy_main_size;
            drawmenu(mainCtrM, copy_main_size);
            break;
        case Process::COPY_NUMBERS:
            cursor = cursor % copy_num_size;
            drawmenu(btnCtrM, copy_num_size);
            break;
        case Process::COPY_NAVIGATION:
            cursor = cursor % copy_nav_size;
            drawmenu(navCtrM, copy_nav_size);
            break;
        case Process::COPY_MISC:
            cursor = cursor % copy_misc_size;
            drawmenu(miscCtrM, copy_misc_size);
            break;

        default:
            break;
        }
        delay(250);
    }
}
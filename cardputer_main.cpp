#include "sd_card.h"
#include "cardputer_main.h"

void drawmenu(MENU thismenu[], int size)
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
      DISP.println(thismenu[i].name);
    }
  }
  else
  {
    for (
        int i = 0; i < size; i++)
    {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(thismenu[i].name);
    }
  }
}

void drawmenu(MENU_IR thismenu[], int size)
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

void switcher_button_proc()
{
  if (rstOverride == false)
  {
    if (check_next_press())
    {
      isSwitching = true;
      current_proc = 1;
    }
  }
}

bool check_next_press()
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

bool check_select_press()
{
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/'))
  {
    // dimtimer();
    return true;
  }
  return false;
}

// Tap the power button from pretty much anywhere to get to the main menu
void check_menu_press()
{
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(',') || M5Cardputer.Keyboard.isKeyPressed('`'))
  {
    isSwitching = true;
    rstOverride = false;
    current_proc = 1;
    delay(100);
  }
}

void mmenu_setup()
{
  cursor = 0;
  rstOverride = true;
  drawmenu(mmenu, mmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void mmenu_loop()
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
    current_proc = mmenu[cursor].command;
  }
}

void read_setup()
{
  cursor = 0;
  rstOverride = true;
  DISP.clearDisplay();
  DISP.setTextColor(WHITE);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setCursor(10, 20);
  DISP.println("Reading:");
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
  IrReceiver.start();
  delay(500); // Prevent switching after menu loads up
}

void read_loop()
{
  if (IrReceiver.decode())
  {
    /*
     * Button is not pressed and data available -> store received data and resume
     */
    DISP.setCursor(10, 50);
    DISP.print("Address:");
    DISP.println(IrReceiver.decodedIRData.address, HEX);
    DISP.fillRect(10, 70, DISP.width(), 20, BGCOLOR); // Reset the back of line
    DISP.setCursor(10, 70);
    DISP.print("Command: 0x");
    DISP.println(IrReceiver.decodedIRData.command, HEX);
    storeCode();
    IrReceiver.resume(); // resume receiver
  }
  delay(200);
}

void send_setup()
{
  IrReceiver.stop();
  IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable
  cursor = 0;
  rstOverride = true;
  drawmenu(sendMenu, currentStoredCodes);
  delay(500); // Prevent switching after menu loads up
}

void send_loop()
{
  if (check_next_press())
  {
    cursor++;
    cursor = cursor % currentStoredCodes;
    drawmenu(sendMenu, currentStoredCodes);
    delay(250);
  }
  if (check_select_press())
  {
    sendCode(&sendMenu[cursor].receivedIRData);
    delay(DELAY_BETWEEN_REPEAT);
  }
}

/// BATTERY INFO ///
void battery_drawmenu(uint8_t battery)
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

void battery_setup()
{
  rstOverride = false;
  pinMode(VBAT_PIN, INPUT);
  uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
  battery_drawmenu(battery);
  delay(500); // Prevent switching after menu loads up
  /*
      Used minimum 3,0V and maximum 4,2V for battery. So it may show wrong values. Needs testing.
      It only shows decent values when disconnected from charger, due to HW limitations.
      Equation: Bat% = ((Vadc - 1842) / (2580 - 1842)) * 100. Where: 4,2V = 2580, 3,0V = 1842.
    */
}

void battery_loop()
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
      current_proc = 1;
      break;
    }
  }

  if (!isSwitching)
  {                                       // If is not switching, calculate battery average
    uint8_t battery = batteryValues / 30; // Iteration times
    Serial.printf("Battery Level: %d\n", battery);
    if (battery != oldBattery)
    { // Only draw a new screen if value is different
      oldBattery = battery;
      battery_drawmenu(battery);
    }
  }
}

void settings_setup()
{
}

void settings_loop()
{
}

M5Canvas canvas(&M5Cardputer.Display);
String data = "";

void enter_name_setup()
{
  DISP.clear();
  DISP.setCursor(10, 10);
  DISP.println("Enter remote name");
  DISP.setCursor(10, DISP.height() - 48);
  DISP.println(">");
  data = "";

  delay(400);
}

void enter_name_loop()
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
          sdCard.createDir(SD, data);
        }
        else
        {
          sdCard.createDir(SD, "/" + data);
        }

        isSwitching = true;
        current_proc = 7;

        // data = "";
      }

      DISP.fillRect(25, DISP.height() - 48, DISP.width(), 25, BLACK);

      DISP.setCursor(25, DISP.height() - 48);
      DISP.print(data);
    }
  }
}

void copy_menu_setup()
{
  cursor = 0;
  rstOverride = true;
  drawmenu(copyRContrM, copy_remote_size);
  delay(500); // Prevent switching after menu loads up
}

void copy_menu_loop()
{
  if (check_next_press())
  {
    cursor++;
    cursor = cursor % mmenu_size;
    drawmenu(copyRContrM, copy_remote_size);
    delay(250);
  }
  if (check_select_press())
  {
    rstOverride = false;
    isSwitching = true;
    current_proc = copyRContrM[cursor].command;
  }
}

void setup()
{
  Serial.begin(115200);

  auto cfg = M5.config();
  M5Cardputer.begin(cfg);
  DISP.setRotation(rotation);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  sdCard.setupSdCard();
}

void loop()
{
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  // screen_dim_proc();
  check_menu_press();

  // Switcher
  if (isSwitching)
  {
    isSwitching = false;
    Serial.printf("Switching To Task: %d\n", current_proc);
    switch (current_proc)
    {
    case 1:
      mmenu_setup();
      break;
    case 2:
      read_setup();
      break;
    case 3:
      send_setup();
      break;
    case 4:
      settings_setup();
      break;
    case 5:
      battery_setup();
      break;
    case 6:
      enter_name_setup();
      break;
      case 7:
      copy_menu_setup();
      break;
    }
  }

  switch (current_proc)
  {
  case 1:
    mmenu_loop();
    break;
  case 2:
    read_loop();
    break;
  case 3:
    send_loop();
    break;
  case 4:
    settings_loop();
    break;
  case 5:
    battery_loop();
    break;
  case 6:
    enter_name_loop();
    break;
    case 7:
    copy_menu_loop();
    break;
  }
}

// Stores the code for later playback in sStoredIRData
// Most of this code is just logging
void storeCode()
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
  sStoredIRData.receivedIRData = IrReceiver.decodedIRData;

  snprintf(sendMenu[currentStoredCodes].name, sizeof(sendMenu[currentStoredCodes].name), "%X", IrReceiver.decodedIRData.command);
  sendMenu[currentStoredCodes].receivedIRData = IrReceiver.decodedIRData;
  currentStoredCodes++;

  // DISP.setTextColor(FGCOLOR, BGCOLOR);
  // DISP.setCursor(10, 50, 1);
  // DISP.print("Address:");
  // DISP.println(IrReceiver.decodedIRData.address, HEX);
  // DISP.setCursor(10, 70, 1);
  // DISP.print("Command: 0x");
  // DISP.println(IrReceiver.decodedIRData.command, HEX);

  if (sStoredIRData.receivedIRData.protocol == UNKNOWN)
  {
    Serial.print(F("Received unknown code and store "));
    Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
    Serial.println(F(" timing entries as raw "));
    IrReceiver.printIRResultRawFormatted(&Serial, true); // Output the results in RAW format
    sStoredIRData.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
    /*
     * Store the current raw data in a dedicated array for later usage
     */
    IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData.rawCode);
  }
  else
  {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    sStoredIRData.receivedIRData.flags = 0; // clear flags -esp. repeat- for later sending
    Serial.println();
  }
}

void sendCode(IRData *aIRDataToSend)
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

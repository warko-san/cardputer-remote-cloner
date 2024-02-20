#include <Arduino.h>

#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include "M5Cardputer.h"
#include <IRremote.hpp>
#include "sd_card.h"

/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */
//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
//#define DECODE_LG
//#define DECODE_NEC          // Includes Apple and Onkyo
#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER
//#define DECODE_FAST

//#define EXCLUDE_UNIVERSAL_PROTOCOLS // Saves up to 1000 bytes program memory.
//#define EXCLUDE_EXOTIC_PROTOCOLS // saves around 650 bytes program memory if all other protocols are active
//#define NO_LED_FEEDBACK_CODE      // saves 92 bytes program memory
//#define RECORD_GAP_MICROS 12000   // Default is 5000. Activate it for some LG air conditioner protocols
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

// MARK_EXCESS_MICROS is subtracted from all marks and added to all spaces before decoding,
// to compensate for the signal forming of different IR receiver modules. See also IRremote.hpp line 142.
#define MARK_EXCESS_MICROS 20  // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

#define DEBUG  // Activate this for lots of lovely debug output from the decoders.

// -------- SYSTEM LOGIC SETUP ----------
#define BGCOLOR BLACK
#define FGCOLOR RED

#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define KB
#define HID
#define ACTIVE_LOW_IR
#define USE_EEPROM
#define SDCARD
// -=-=- ALIASES -=-=-
#define DISP M5Cardputer.Display
#define IRLED 44
#define BACKLIGHT 38
#define MINBRIGHT 165
#define SPEAKER M5Cardputer.Speaker
#define SD_CLK_PIN 40
#define SD_MISO_PIN 39
#define SD_MOSI_PIN 14
#define SD_CS_PIN 12
#define VBAT_PIN 10
#define M5LED_ON LOW
#define M5LED_OFF HIGH

/// SWITCHER ///
// Proc codes
// 1  - Main Menu
// 2  - Read Menu
// 3  - Send Menu
// 4  - Settings
// 5  - Battery info
// 6  - Copy remote enter name
// 7  - Copy remote controls
// 8  - Copy main controls
// 9  - Copy numbers
// 10 - Copy navigation
// 11 - Copy misc
// 12 - Load remote
// ===============================
// 13 - TV-B-Gone Region Setting
// 14 - Wifi scanning
// 15 - Wifi scan results
// 16 - Bluetooth Spam Menu
// 17 - Bluetooth Maelstrom
// 18 - QR Codes
// 19 - NEMO Portal
// 20 - Attack menu
// 21 - Deauth Attack
// .. - ..
// 97 - Mount/UnMount SD Card on M5Stick devices, if SDCARD is declared

int SEND_BUTTON_PIN = 0;

int DELAY_BETWEEN_REPEAT = 100;

// Storage for the recorded code
struct storedIRDataStruct {
  IRData receivedIRData;
  IRData irDataArray[52];
  // extensions for sendRaw
  uint8_t rawCode[RAW_BUFFER_LENGTH];  // The durations if raw
  uint8_t rawCodeLength;               // The length of the code
} sStoredIRData;

struct MENU {
  char name[19];
  int command;
};

struct MENU_IR {
  char name[19];
  IRData receivedIRData;
};

SDcard sdCard;

uint8_t currentStoredCodes = 1;
uint8_t selectedSavedCode = 0;
uint8_t cursor = 0;
uint8_t rotation = 1;
uint8_t current_proc = 1;
bool rstOverride = false;  // Reset Button Override. Set to true when navigating menus.
bool isSwitching = true;

void storeCode();
void sendCode(IRData *aIRDataToSend);

bool check_next_press();

void drawmenu(MENU thismenu[], int size) {
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 5);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < size; i++) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(thismenu[i].name);
    }
  } else {
    for (
      int i = 0; i < size; i++) {
      DISP.print((cursor == i) ? ">" : " ");
      DISP.println(thismenu[i].name);
    }
  }
}

void drawmenu(MENU_IR thismenu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 5);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < size; i++) {
      if (i == 0) {
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.print((cursor == i) ? ">" : " ");
        DISP.println(thismenu[i].name);
      } else {
        DISP.setTextColor(WHITE, BGCOLOR);
        DISP.print((cursor == i) ? ">" : " ");
        DISP.print(F(" Command=0x"));
        DISP.println(thismenu[i].name);
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      if (i == 0) {
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.print((cursor == i) ? ">" : " ");
        DISP.println(thismenu[i].name);
      } else {
        DISP.setTextColor(WHITE, BGCOLOR);
        DISP.print((cursor == i) ? ">" : " ");
        DISP.print(F(" Command=0x"));
        DISP.println(thismenu[i].name);
      }
    }
  }
}

void switcher_button_proc() {
  if (rstOverride == false) {
    if (check_next_press()) {
      isSwitching = true;
      current_proc = 1;
    }
  }
}

bool check_next_press() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(';')) {
    // hack to handle the up arrow
    cursor = cursor - 2;
    return true;
  }
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')) {
    // dimtimer();
    return true;
  }
  return false;
}

bool check_select_press() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')) {
    // dimtimer();
    return true;
  }
  return false;
}

// Tap the power button from pretty much anywhere to get to the main menu
void check_menu_press() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(',') || M5Cardputer.Keyboard.isKeyPressed('`')) {
    isSwitching = true;
    rstOverride = false;
    current_proc = 1;
    delay(100);
  }
}

/// MAIN MENU ///
MENU mmenu[] = {
  { "Read signals", 2 },  // We jump to the region menu first
  { "Send signals", 3 },
  { "Battery info", 5 },
  { "Settings", 4 }
};
int mmenu_size = sizeof(mmenu) / sizeof(MENU);

void mmenu_setup() {
  cursor = 0;
  rstOverride = true;
  drawmenu(mmenu, mmenu_size);
  delay(500);  // Prevent switching after menu loads up
}

void mmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % mmenu_size;
    drawmenu(mmenu, mmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    rstOverride = false;
    isSwitching = true;
    current_proc = mmenu[cursor].command;
  }
}

void read_setup() {
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
  delay(500);  // Prevent switching after menu loads up
}

void read_loop() {
  // if (check_next_press()) {
  //   cursor++;
  //   cursor = cursor % mmenu_size;
  //   drawmenu(mmenu, mmenu_size);
  //   delay(250);
  // }
  // if (check_select_press()) {
  //   rstOverride = false;
  //   isSwitching = true;
  //   current_proc = mmenu[cursor].command;
  // }

  if (IrReceiver.decode()) {
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
    IrReceiver.resume();  // resume receiver
  }
  delay(200);
}

MENU_IR sendMenu[52] = {
  { "Send signals:", sStoredIRData.receivedIRData }
};

void send_setup() {
  IrReceiver.stop();
  IrSender.begin();  // Start with IR_SEND_PIN as send pin and enable
  cursor = 0;
  rstOverride = true;
  drawmenu(sendMenu, currentStoredCodes);
  delay(500);  // Prevent switching after menu loads up
}

void send_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % currentStoredCodes;
    drawmenu(sendMenu, currentStoredCodes);
    delay(250);
  }
  if (check_select_press()) {
    sendCode(&sendMenu[cursor].receivedIRData);
    delay(DELAY_BETWEEN_REPEAT);
  }
}

/// BATTERY INFO ///
uint8_t oldBattery = 0;
void battery_drawmenu(uint8_t battery) {
  // Battery bar color definition
  uint16_t batteryBarColor = BLUE;
  if (battery < 20) {
    batteryBarColor = RED;
  } else if (battery < 60) {
    batteryBarColor = ORANGE;
  } else {
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

void battery_setup() {
  rstOverride = false;
  pinMode(VBAT_PIN, INPUT);
  uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
  battery_drawmenu(battery);
  delay(500);  // Prevent switching after menu loads up
  /*
      Used minimum 3,0V and maximum 4,2V for battery. So it may show wrong values. Needs testing.
      It only shows decent values when disconnected from charger, due to HW limitations.
      Equation: Bat% = ((Vadc - 1842) / (2580 - 1842)) * 100. Where: 4,2V = 2580, 3,0V = 1842.
    */
}

void battery_loop() {
  // Read 30 battery values to calculate the average (avoiding unprecise and close values)
  uint16_t batteryValues = 0;
  for (uint8_t i = 0; i < 30; i++) {  // 30 iterations X 100ms = 3 seconds for each refresh
    delay(100);
    batteryValues += ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {  // If any key is pressed
      rstOverride = false;
      isSwitching = true;
      current_proc = 1;
      break;
    }
  }

  if (!isSwitching) {                      // If is not switching, calculate battery average
    uint8_t battery = batteryValues / 30;  // Iteration times
    Serial.printf("Battery Level: %d\n", battery);
    if (battery != oldBattery) {  // Only draw a new screen if value is different
      oldBattery = battery;
      battery_drawmenu(battery);
    }
  }
}

void settings_setup() {
}

void settings_loop() {
}

void setup() {
  Serial.begin(115200);

  auto cfg = M5.config();
  M5Cardputer.begin(cfg);
  DISP.setRotation(rotation);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  sdCard.setupSdCard();
}

void loop() {
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  // screen_dim_proc();
  check_menu_press();

  // Switcher
  if (isSwitching) {
    isSwitching = false;
    Serial.printf("Switching To Task: %d\n", current_proc);
    switch (current_proc) {
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
    }
  }

  switch (current_proc) {
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
  }
}

// Stores the code for later playback in sStoredIRData
// Most of this code is just logging
void storeCode() {
  if (IrReceiver.decodedIRData.rawDataPtr->rawlen < 4) {
    Serial.print(F("Ignore data with rawlen="));
    Serial.println(IrReceiver.decodedIRData.rawDataPtr->rawlen);
    return;
  }
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
    Serial.println(F("Ignore repeat"));
    return;
  }
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_AUTO_REPEAT) {
    Serial.println(F("Ignore autorepeat"));
    return;
  }
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_PARITY_FAILED) {
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

  if (sStoredIRData.receivedIRData.protocol == UNKNOWN) {
    Serial.print(F("Received unknown code and store "));
    Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
    Serial.println(F(" timing entries as raw "));
    IrReceiver.printIRResultRawFormatted(&Serial, true);  // Output the results in RAW format
    sStoredIRData.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;
    /*
         * Store the current raw data in a dedicated array for later usage
         */
    IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData.rawCode);
  } else {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    sStoredIRData.receivedIRData.flags = 0;  // clear flags -esp. repeat- for later sending
    Serial.println();
  }
}

void sendCode(IRData *aIRDataToSend) {
  if (aIRDataToSend->protocol == UNKNOWN) return;
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

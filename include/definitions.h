
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
#define DISP M5Cardputer.Display

// -=-=- IR SETUP -=-=-
#define IR_RECEIVE_PIN          1  // D1
#define IR_SEND_PIN             44  // D44
#define TONE_PIN                27  // D27 25 & 26 are DAC0 and 1
#define APPLICATION_PIN         16  // RX2 pin
/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */
// #define DECODE_DENON        // Includes Sharp
// #define DECODE_JVC
// #define DECODE_KASEIKYO
// #define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
// #define DECODE_LG
// #define DECODE_NEC          // Includes Apple and Onkyo
// #define DECODE_SAMSUNG
// #define DECODE_SONY
// #define DECODE_RC5
// #define DECODE_RC6

// #define DECODE_BOSEWAVE
// #define DECODE_LEGO_PF
// #define DECODE_MAGIQUEST
// #define DECODE_WHYNTER
// #define DECODE_FAST

// #define EXCLUDE_UNIVERSAL_PROTOCOLS // Saves up to 1000 bytes program memory.
// #define EXCLUDE_EXOTIC_PROTOCOLS // saves around 650 bytes program memory if all other protocols are active
// #define NO_LED_FEEDBACK_CODE      // saves 92 bytes program memory
// #define RECORD_GAP_MICROS 12000   // Default is 5000. Activate it for some LG air conditioner protocols
// #define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
// #define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

// MARK_EXCESS_MICROS is subtracted from all marks and added to all spaces before decoding,
// to compensate for the signal forming of different IR receiver modules. See also IRremote.hpp line 142.
#define MARK_EXCESS_MICROS 20 // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

#define DEBUG // Activate this for lots of lovely debug output from the decoders.

/*
 * Helper macro for getting a macro definition as string
 */
#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif


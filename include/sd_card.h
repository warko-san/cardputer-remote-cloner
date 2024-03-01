#ifndef SD_CARD_H
#define SD_CARD_H
#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE

#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "ir_handler.h"

#define SD_CLK_PIN 40
#define SD_MISO_PIN 39
#define SD_MOSI_PIN 14
#define SD_CS_PIN 12

class SDcard
{
private:
  SemaphoreHandle_t sdcardSemaphore;
  SPIClass *sdcardSPI = NULL;

public:
  SDcard();
  bool sdcardMounted = false;
  uint8_t dirCount = 0;
  uint8_t saveConfirmations = 0;
  String *dirs = new String[42];

  String rootDir = "/wcopy_universal";

  bool setupSdCard();

  bool exists(const char *path);

  String *listDir(const char *path);

  void createDir(const char *path);

  void loadIrDataFromFile(const char *path, IRData *dataArray, int maxDataCount);

  void writeFile(const char *path, const char *message);
  void createEmptyFile(const char *path);

  void appendToFile(const char *path, const char *text);
  void appendToFileIrData(const char *path, IRData &data);
};

#endif

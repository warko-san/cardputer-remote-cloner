#include "sd_card.h"

SDcard::SDcard() {}

void SDcard::createDir(fs::FS &fs, const char *path)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path))
    {
      Serial.println("Dir created");
    }
    else
    {
      Serial.println("mkdir failed");
    }
    xSemaphoreGive(sdcardSemaphore);
  }
}

void SDcard::writeFile(fs::FS &fs, const char *path, const char *message)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
      Serial.println("Failed to open file for writing");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }
    if (file.print(message))
    {
      Serial.println("File written");
    }
    else
    {
      Serial.println("Write failed");
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}

void SDcard::appendToFile(fs::FS &fs, const char *path, const char *text)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
      Serial.println("Failed to open file for appending");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }
    Serial.printf("Appending text '%s' to file: %s\n", text, path);
    if (file.println(text))
    {
      Serial.println("Text appended");
    }
    else
    {
      Serial.println("Append failed");
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}

bool SDcard::setupSdCard()
{
  sdcardSemaphore = xSemaphoreCreateMutex();
  sdcardSPI = new SPIClass(FSPI);
  sdcardSPI->begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  delay(10);
  if (!SD.begin(SD_CS_PIN, *sdcardSPI))
  {
    sdcardSPI->end();
    Serial.println("Failed to mount SDCARD");
    sdcardMounted = false;
    return false;
  }
  else
  {
    Serial.println("SDCARD mounted successfully");
    sdcardMounted = true;
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
      DISP.println("None SD Card");
      Serial.println("None SD Card");
    }
    DISP.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
      DISP.println("MMC");
      Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
      DISP.println("SDSC");
      Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
      DISP.println("SDHC");
      Serial.println("SDHC");
    }
    else
    {
      DISP.println("UNKNOWN");
      Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    DISP.printf("SD Card Size: %lluMB\n", cardSize);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    return true;
  }
  return false;
}

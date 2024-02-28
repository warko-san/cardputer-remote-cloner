#include "sd_card.h"

SDcard::SDcard() {}

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

    if (!exists(rootDir.c_str())) {
      createDir(rootDir.c_str());
    }
    return true;
  }
  return false;
}

bool SDcard::exists(const char *path) {
  return SPIFFS.exists(path);
}

String* SDcard::listDir(const char * dirname){
  for(int i = 0; i < 42; ++i) {
    dirs[i] = "";
}
    Serial.printf("Listing directory: %s\n", dirname);

    File root = SD.open(dirname);
    if(!root){
      Serial.println("Failed to open directory");
      return dirs;
    }
    if(!root.isDirectory()){
      Serial.println("Not a directory");
      return dirs;
    }

    File file = root.openNextFile();
    while(file){
      if(file.isDirectory()){
        Serial.print("  DIR : ");
        Serial.println(file.name());
        dirs[dirCount++] = file.name();
      }
      file = root.openNextFile();
    }

    return dirs;
}

void SDcard::createDir(const char *path)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Creating Dir: %s\n", path);
    if (SD.mkdir(path))
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

void SDcard::readFile(const char * path){
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Reading file: %s\n", path);

    File file = SD.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        xSemaphoreGive(sdcardSemaphore);
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    while (file.available()) {
        String line = file.readStringUntil('\n');
        IRData irData;
        uint8_t position = 0;
        if (sscanf(line.c_str(), "Address 0x%hx Command 0x%hx", &irData.address, &irData.command) == 2) {
            // Successfully parsed the address and command
            Serial.print("Address: 0x");
            Serial.print(irData.address, HEX);
            Serial.print(", Command: 0x");
            Serial.println(irData.command, HEX);
            // You can now store `irData` in an array or process it as needed
            ir_handler::mainControls[position++] = irData;
        } else {
            Serial.println("Failed to parse line");
        }
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}

void SDcard::loadIrDataFromFile(const char * path, IRData* dataArray, int maxDataCount){
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Reading file: %s\n", path);

    File file = SD.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        xSemaphoreGive(sdcardSemaphore);
        return;
    }

    Serial.print("Read from file: ");
    // while(file.available()){
    //     Serial.write(file.read());
    // }
    int count = 0;
    while (file.available() && count < maxDataCount) {
        file.read((uint8_t*)&dataArray[count], sizeof(IRData));
        count++;
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}

void SDcard::writeFile(const char *path, const char *message)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Writing file: %s\n", path);

    File file = SD.open(path, FILE_WRITE);
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

void SDcard::createFile(const char *path)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    Serial.printf("Creating file: %s\n", path);
    File file = SD.open(path, FILE_WRITE);
    if (!file)
    {
      Serial.println("Failed to create file");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}

void SDcard::appendToFile(const char *path, const char *text)
{
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    File file = SD.open(path, FILE_APPEND);
    if (!file)
    {
      Serial.println("Failed to open file for appending");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }
    Serial.printf("Appending text '%s' to file: %s\n", text, path);
    file.println();
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

void SDcard::appendToFileIrData(const char *path, IRData& data) {
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE)
  {
    File file = SD.open(path, FILE_APPEND);
    if (!file)
    {
      Serial.println("Failed to open file for appending");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }

    if (file.write((const uint8_t*)&data, sizeof(IRData)))
    {
      Serial.println("Data appended");
    }
    else
    {
      Serial.println("Append failed");
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }

}

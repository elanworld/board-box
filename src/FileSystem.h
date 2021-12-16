#include "SPIFFS.h"

void check() {
  // Launch SPIFFS file system
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }
}

void write(char * fileName, char * line) {
  File file = SPIFFS.open(fileName,"w");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("File size: ");
  Serial.println(file.size());
  file.println(line);
  file.close();
}

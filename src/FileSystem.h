#include "SPIFFS.h"

void mountFs() {
  // Launch SPIFFS file system
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }
}

void write(const char * fileName, const char * line) {

  File file = SPIFFS.open(fileName, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file");
    return;
  }
  Serial.print("File size: ");
  Serial.println(file.size());
  file.print(line);
  file.close();
}

String read(const char * fileName) {
  File file = SPIFFS.open(fileName, FILE_READ);
  Serial.print("File size: ");
  Serial.println(file.size());
  String res = file.readString();
  file.close();
  return res;
}

bool checkFileExists(const char * path) {
  return SPIFFS.exists(path);
}

#include <ArduinoJson.h>
#include "hmi_ops.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
}

bool foundReadyJson = false;
void loop() {
  if (!foundReadyJson) {
    if (Serial3.findUntil("readyJson\r\n", "\n")) {
      foundReadyJson = true;
    }
  } else {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, Serial3);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      foundReadyJson = false;
      return;
    };
    
    updateHmi(doc);

    foundReadyJson = false;
  }
}

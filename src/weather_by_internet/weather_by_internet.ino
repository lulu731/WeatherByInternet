#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
//#include "secrets.h"

#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "json_ops.h"
#include "w_OTA.h"

SerialCmd serCmd(Serial, SERIALCMD_LF);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }

  otaUpdate();
  serCmd.AddCmd("REQJSO", SERIALCMD_FROMSERIAL, requestJson);
  Serial.print("SEROK\n");
}

void loop() {
  ArduinoOTA.handle();
  serCmd.ReadSer();
}

#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "host_data.h"
#include <ArduinoJson.h>
#include "json_ops.h"
#include "w_OTA.h"


WiFiClient wifiClient;
HttpClient client(wifiClient, host, httpPort);

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

  int err = client.get(url);
  delay(500);

  if (err == 0) {
    err = client.responseStatusCode();
    int bodyLen = client.contentLength();
  }

  StaticJsonDocument<12288> doc;
  DeserializationError error = get_json_doc (doc, client);
  if (error) { //todo: how to manage error?
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  Serial.println("readyJson");
  serializeJson(doc, Serial);
}

void loop() {
  ArduinoOTA.handle();
}

#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "host_data.h"
#include <ArduinoJson.h>
#include "json_ops.h"


WiFiClient wifiClient;
HttpClient client(wifiClient, host, httpPort);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  //delay(100);
  Serial.println();
  Serial.println("------------");
  Serial.println("Serial OK");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  int err = client.get(url);
  delay(500);

  if (err == 0) {
    //Serial.println("startedReq OK");
    err = client.responseStatusCode();
    //Serial.print("responsStatus : ");
    //Serial.println(err);
    int bodyLen = client.contentLength();
  }

  StaticJsonDocument<1024> doc;
  DeserializationError error = get_json_doc (doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  //Serial.println(error.f_str());
  serializeJsonPretty(doc, Serial);
}

void loop() {
}
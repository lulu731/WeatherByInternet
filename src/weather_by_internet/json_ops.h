#ifndef __JSON_OPS_H__
#define __JSON_OPS_H__

#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "host_data.h"

//static bool docUpdated = false;
static WiFiClient wifiClient;
static HttpClient client(wifiClient, host, httpPort);
static DynamicJsonDocument doc(12288);

DeserializationError get_json_doc(JsonDocument&, Stream&);
void requestJson();
void cleanJson(JsonDocument&);

#endif


//{"weather":[{"icon":"50d"}],"main":{"temp":287.32,"feels_like":287.25,"temp_min":287.24,"temp_max":287.42,"pressure":1021,"humidity":94},"visibility":3900,"wind":{"speed":5.66,"deg":210}}

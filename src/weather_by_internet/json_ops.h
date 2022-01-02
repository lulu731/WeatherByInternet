#ifndef __JSON_OPS_H__
#define __JSON_OPS_H__

#include <ArduinoJson.h>

DeserializationError get_json_doc(JsonDocument& doc, Stream& stream) {
  StaticJsonDocument<384> filter;
  filter["weather"][0]["icon"] = true;
  filter["main"] = true;
  filter["visibility"] = true;
  filter["wind"] = true;

  // Deserialize the document
  
  return deserializeJson(doc, stream, DeserializationOption::Filter(filter));
}

void clean_json_doc(JsonDocument& doc) {
  if (doc["visibility"] > 4000) {
    //todo
  }
}

#endif


//{"weather":[{"icon":"50d"}],"main":{"temp":287.32,"feels_like":287.25,"temp_min":287.24,"temp_max":287.42,"pressure":1021,"humidity":94},"visibility":3900,"wind":{"speed":5.66,"deg":210}}

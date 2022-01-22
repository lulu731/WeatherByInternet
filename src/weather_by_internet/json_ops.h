#ifndef __JSON_OPS_H__
#define __JSON_OPS_H__

#include <ArduinoJson.h>

DeserializationError get_json_doc(JsonDocument& doc, Stream& stream) {
  StaticJsonDocument<512> filter;
  filter["list"][0]["main"]["temp"] = true;
  filter["list"][0]["main"]["feels_like"] = true;
  filter["list"][0]["main"]["pressure"] = true;
  filter["list"][0]["main"]["humidity"] = true;
  filter["list"][0]["weather"][0]["icon"] = true;
  filter["list"][0]["visibility"] = true;
  filter["list"][0]["wind"] = true;
  filter["list"][0]["dt_txt"] = true;
  filter["city"]["name"] = true;

  // Deserialize the document
  
  return deserializeJson(doc, stream, DeserializationOption::Filter(filter));
}

#endif


//{"weather":[{"icon":"50d"}],"main":{"temp":287.32,"feels_like":287.25,"temp_min":287.24,"temp_max":287.42,"pressure":1021,"humidity":94},"visibility":3900,"wind":{"speed":5.66,"deg":210}}

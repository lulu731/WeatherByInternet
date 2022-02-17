#include "json_ops.h"
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
};

void cleanJson(JsonDocument& doc) {
  //clean json to keep only first weather data and those with time 12:00:00
  JsonArray list = doc["list"];
  byte day = 0;
  for (JsonArray::iterator it = list.begin(); it != list.end(); ++it) {
    String dtTxt = (*it)["dt_txt"];
    String dtEnd = "12:00:00";
    if ((!(it == list.begin()) && !(dtTxt.endsWith(dtEnd)) || day > 4)) {
      list.remove(it);
    } else {
      ++day;
    }
  }
}

void requestJson() {
  doc.clear();

  //connect to url
  int err = client.get(url);
  delay(500);

  if (err == 0) {
    err = client.responseStatusCode();
    int bodyLen = client.contentLength();
  }

  //get json from internet
  DeserializationError error = get_json_doc(doc, client);
  if (error) {  //todo: how to manage error? => send a command to Arduino
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  cleanJson(doc);
  Serial.print("PULLJS\n");
  serializeJson(doc, Serial);
}

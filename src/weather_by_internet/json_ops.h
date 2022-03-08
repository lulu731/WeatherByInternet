#ifndef __JSON_OPS_H__
#define __JSON_OPS_H__

#include <ArduinoJson.h>

DeserializationError GetJsonDoc(JsonDocument&, Stream&);
bool RequestJson(JsonDocument&);
void CleanJson(JsonDocument&);

#endif


//{"weather":[{"icon":"50d"}],"main":{"temp":287.32,"feels_like":287.25,"temp_min":287.24,"temp_max":287.42,"pressure":1021,"humidity":94},"visibility":3900,"wind":{"speed":5.66,"deg":210}}

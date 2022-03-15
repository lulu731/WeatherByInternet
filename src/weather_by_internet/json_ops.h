#ifndef __JSON_OPS_H__
#define __JSON_OPS_H__

#include <ArduinoJson.h>

DeserializationError GetJsonDoc(JsonDocument&, Stream&);
bool RequestJson(JsonDocument&);
void CleanJson(JsonDocument&);

#endif

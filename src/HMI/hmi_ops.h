#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

byte getIconIndex(const char* ch);

void updateHmi(const StaticJsonDocument<1024>& doc);

#endif

#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

byte getIconIndex(const char*);

void updateHmi(const DynamicJsonDocument&);

#endif

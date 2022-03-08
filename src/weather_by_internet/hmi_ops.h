#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

byte GetIconIndex(const char*);
void UpdateHmi(const DynamicJsonDocument&);

#endif

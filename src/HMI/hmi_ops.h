#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

extern bool docUpdated;
extern DynamicJsonDocument doc;

void pullJson();
byte getIconIndex(const char*);
void updateHmi(const DynamicJsonDocument&);

#endif

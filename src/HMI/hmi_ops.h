#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

extern bool docUpdated;
extern bool HMIUpdated;
extern DynamicJsonDocument doc;
extern bool jsonToRequest;

void PullJson();
void SerialOK();
byte GetIconIndex(const char*);
bool UpdateHmi(const DynamicJsonDocument&);

#endif

#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "hmi_ops.h"


SerialCmd serCmd(Serial3, SERIALCMD_LF);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, pullJson);
  delay(60000);
};

bool jsonToRequest = true;
bool docUpdated = false;
DynamicJsonDocument doc(4096);
  
void loop() {
  //Serial.print("in loop - ");
  //Serial.println(docUpdated);
  if (jsonToRequest) {
    Serial3.println("REQJSO");
    //Serial.println("REQJSO sent.");
    jsonToRequest = false;
  }
  //Serial.println("Waiting for pullJSON");
  

  //update screen when JSON doc is updated
  if (docUpdated) {
    //Serial.println("docUpdated is true");
    updateHmi(doc);
    docUpdated = false;
    jsonToRequest = true;
    delay(120000);//delay for 2 min when updated
  }
  serCmd.ReadSer();  
};

#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "hmi_ops.h"
#include "sleep.h"

const int wakeUpPin = 21;
SerialCmd serCmd(Serial3);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
  pinMode(wakeUpPin, INPUT);
  //serCmd.AddCmd("SLEEP", SERIALCMD_FROMSERIAL, goToSleep);
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, pullJson);
  Serial.println("delay 1mn");
  delay(60000);
};

bool jsonToRequest = true;
void loop() {
  if (jsonToRequest) {
    Serial3.println("REQJSO");
    Serial.println("request JSON to ESP");
    jsonToRequest = false;
  }
  serCmd.ReadSer();

  //update screen when JSON doc is updated
  if (docUpdated) {
    Serial.println("doc Updated");
    HMIUpdated = updateHmi(doc);
    docUpdated = false;
    //delay(120000);//delay for 2 min when updated
  }  

  //send go to sleep signal to ESP and board sleeps
  if (HMIUpdated) {
    HMIUpdated = false;
    Serial3.println("SLEEP"); 
    Serial.println("go to sleep");
    goToSleep();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(300); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);
    delay(300); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(LED_BUILTIN, INPUT);
    
    jsonToRequest = true;
  }
};

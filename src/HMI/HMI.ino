#include <SerialCmd.h>
#include "Nextion.h"
#include "hmi_ops.h"
#include "sleep.h"

const int wakeUpPin = 21;
SerialCmd serCmd(Serial3, SERIALCMD_LF);

void setup() {
  /*dbSerialBegin(115200);
  while (!dbSerial) {
    ;
  }*/
  nexInit();
  dbSerialPrintln("Serial OK");

  /*nexSerial.begin(9600);
  while (!nexSerial) {
    ;
  }*/
  dbSerialPrintln("Serial1 OK");

  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
  dbSerialPrintln("Serial3 OK");

  //wait 10s to ease ESP OTA update
  delay(10000);

  pinMode(wakeUpPin, INPUT);

  serCmd.AddCmd("SEROK", SERIALCMD_FROMSERIAL, SerialOK);
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, PullJson);
};
  
void loop() {
  serCmd.ReadSer();

  if (jsonToRequest) {
    Serial3.print("REQJSO\n");
    jsonToRequest = false;
  }
  
  //update screen when JSON doc is updated
  if (docUpdated) {
    //Serial.println("update HMI");
    HMIUpdated = UpdateHmi(doc);
    docUpdated = false;
  }  

  //send go to sleep signal to ESP and board sleeps if HMI is updated
  if (HMIUpdated) {
    HMIUpdated = false;
    Serial3.print("SLEEP\n"); 
    //Serial.println("");
    dbSerialPrintln("go to sleep");
    goToSleep();
    //Serial.println("woke up");
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
  }
};

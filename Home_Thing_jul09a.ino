#include "arduino_secrets.h"
#include "thingProperties.h"

int countWiFiNotification = 0;

void setup() {
  pinMode(12,OUTPUT); 
  pinMode(14,OUTPUT); 
  pinMode(16,OUTPUT); 
 // pinMode(13,OUTPUT); 


  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000); 
  Serial.println("OK thus far");
  delay(1000); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println("Finish set-up");

}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  Serial.println("Keep Alive!");
  delay(1500);
  if (countWiFiNotification == 0) {
    if (WiFi.status() != WL_CONNECTED ) {
    Serial.println("WiFi Connected");
    countWiFiNotification = 1; 
    }
    else{
      Serial.println("WiFi NOT Connected");
    }
  }
}


/*
  Since HARPiSupplySW is READ_WRITE variable, onHARPiSupplySWChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHARPiSupplySWChange()  {
  // Add your code here to act upon HARPiSupplySW change

   if (hA_RPi_Supply_SW == 1){
   //if SW is ON (HIGH), S2 and S4 Relay CONNECTS COM to NO (Normally Open). Otherwise, BOTH COM in connect to NC (Normally Connected)
   
   digitalWrite(16,HIGH); //IMPORTANT, FIRST DISCONNECT S2, SINCE IT IS CONNECTED TO GROUND
   delay(500);
   digitalWrite(12,HIGH);
   }
   else {
   digitalWrite(12,LOW); //IMPORTANT, FIRST DISCONNECT S4, SINCE IT IS CONNECTED TO 5V
   delay(500);
   digitalWrite(16,LOW);
   delay(500);

   }
   delay(500);
}
/*
  Since S2Relay is READ_WRITE variable, onS2RelayChange() is
  executed every time a new value is received from IoT Cloud.
*/
/* //BLOCKING INDEPENDENT S2 CHANGE - IT IS CONNECTED TO THE GROUND OF OUTPUT LOAD
 * void onS2RelayChange()  {
  // Add your code here to act upon S2Relay change
   if (s2_Relay == 1){
   //if SW is ON (HIGH), S2 Relay CONNECTS COM to NO (Normally Open). Otherwise, COM in connect to NC (Normally Connected)
   digitalWrite(16,HIGH);
   Serial.println("Relay to NO\n");
   }
   else {
   digitalWrite(16,LOW);
   Serial.println("Relay to NC\n");
   }
   delay(1000);
}*/

/*
  Since S3Relay is READ_WRITE variable, onS3RelayChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onS3RelayChange()  {
  // Add your code here to act upon S3Relay change
   if (s3_Relay == 1){
   //if SW is ON (HIGH), S3 Relay CONNECTS COM to NO (Normally Open). Otherwise, COM in connect to NC (Normally Connected)
   digitalWrite(14,HIGH);
   Serial.println("Relay to NO\n");
   }
   else {
   digitalWrite(14,LOW);
   Serial.println("Relay to NC\n");
   }
   delay(1000);
}


   

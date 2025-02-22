#include "arduino_secrets.h"
#include "thingProperties.h"

// Define relay pins for LinkNode R4
const int RELAY_S2 = 16;  // Relay S2
const int RELAY_S3 = 14;  // Relay S3
const int RELAY_S4 = 12;  // Relay S4

int countWiFiNotification = 0;

void setup() {
  
  // Initialize relay pins as outputs
  pinMode(RELAY_S2, OUTPUT);
  pinMode(RELAY_S3, OUTPUT);
  pinMode(RELAY_S4, OUTPUT); 

  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000); 
  Serial.println("OK thus far");
  delay(1000); 

  // Initially set all relays to OFF (relays are typically active LOW)
  Serial.println("Setting S2/3/4 to Off");

  digitalWrite(RELAY_S2, LOW);
  digitalWrite(RELAY_S3, LOW);
  digitalWrite(RELAY_S4, LOW);  

  // Power Up Sequence (Ground -> Primary power rail -> seconday power rail)
  delay(500);
  Serial.println("Setting S2 to On");
  digitalWrite(RELAY_S2, HIGH);  // Turn ON S2
  // wait half a second for ground to stabilize
  delay(1000);
  Serial.println("Setting S3 to On");
  digitalWrite(RELAY_S3, HIGH);  // Turn ON S3
  // wait 5 seconds for boot to start. If primary (S3) and Secondary (S4) turn on at the same time, BOOT DOES NOT START
  delay(5000);
  Serial.println("Setting S4 to On");
  digitalWrite(RELAY_S4, HIGH);  // Turn ON S4


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
  /*
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
   */
}




/*
  Since S3Relay is READ_WRITE variable, onS3RelayChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onS3RelayChange()  {
  /*// Add your code here to act upon S3Relay change
   if (s3_Relay == 1){
   //if SW is ON (HIGH), S3 Relay CONNECTS COM to NO (Normally Open). Otherwise, COM in connect to NC (Normally Connected)
   digitalWrite(14,HIGH);
   Serial.println("Relay to NO\n");
   }
   else {
   digitalWrite(14,LOW);
   Serial.println("Relay to NC\n");
   }
   delay(1000);*/
}



   

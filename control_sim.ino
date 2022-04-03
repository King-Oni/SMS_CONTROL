#include <SoftwareSerial.h>
#define Relay1 4
#define Relay2 5


//Create software serial object to communicate with SIM800L
SoftwareSerial MySim(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
String message;

void setup() {
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  MySim.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  MySim.println("AT+CMGF=1"); // Configuring TEXT mode

  MySim.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

}

void loop() {

  while (MySim.available()) {
    message = MySim.readString();
    Serial.println(message);
    //Serial.println(message);//[N] Debugging print statement

    //Turn R1 on
    if (message.indexOf("R1ON") >= 0) {
      digitalWrite(Relay1, HIGH);
    }

    //Turn R1 off
    if (message.indexOf("R1OFF") >= 0) {
      digitalWrite(Relay1, LOW);
    }

    //Turn R2 on
    if (message.indexOf("R2ON") >= 0) {
      digitalWrite(Relay2, HIGH);
    }

    //Turn R2 off
    if (message.indexOf("R2OFF") >= 0) {
      digitalWrite(Relay2, LOW);
    }

    delay(250);
  }
}
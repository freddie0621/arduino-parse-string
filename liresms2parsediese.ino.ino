// Example 3 - Receive with start- and end-markers

const byte numChars = 32;
char receivedChars[numChars];
String buffer1;
boolean newData = false;


#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 int i=1;
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
   
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
   
  //Set SMS format to ASCII
  //serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  //serialSIM800.write("AT+CMGS=\"0695307298\"\r\n");
  delay(1000);
   
  //Send SMS content
  //serialSIM800.write("HELLOessaisms6");
 
  
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  //serialSIM800.write((char)26);
  delay(1000);
    
  Serial.println("SMS Sent!");
  deletesms();
}
 
void loop() {
//Serial.println("Receiving text message...");
  serialSIM800.print("AT+CMGF=1\r\n");   // Configure le mode SMS
  // Affiche tous les messages
  serialSIM800.print("AT+CMGL=\"ALL\"\r\n");
  delay(1000);
  serialSIM800.println();


  
  //Serial.write(serialSIM800.read());
    recvWithStartEndMarkers();
    showNewData();
   
  //if (serialSIM800.available()>0){
     // buffer1 = serialSIM800.readStringUntil('\n'); //Saving string then parsing caller number from it
    //Serial.println(buffer1);
   // Serial.println(i++);
    //Serial.write(serialSIM800.read());
 // }
}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '#';
    char endMarker = '#';
    char rc;
 
    while (serialSIM800.available() > 0 && newData == false) {
        rc = serialSIM800.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData(){
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
        deletesms();
        
    }
}
 void deletesms(){
  //serialSIM800.print("AT+CMGD=\"1,4\"\r\n");
  serialSIM800.print("AT+CMGD=1,4\r\n");
        delay(1000);
        serialSIM800.println();
}


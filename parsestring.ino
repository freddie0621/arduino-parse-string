
String results[6];
void setup() {
    Serial.begin(9600);
}
//12:585&52:78
//12:585&52:78&12:585&52:78777&12:585&52:78&12:585&52:78777999
void loop() {
    for(int i=1; i<=3; i++) {
        String servo = Serial.readStringUntil(':');
         Serial.println (servo);
        if(servo != ""){
            //here you could check the servo number
            String pos = Serial.readStringUntil('&');
            //int int_pos=pos.toInt();
            results[i]=pos;
            Serial.println("Pos");
           Serial.println(pos);
        }
    }
 Serial.println("SERVO");
 Serial.println(results[1]);
}

String results[6];
String rc;
int ind1; // , locations
int ind2;
int ind3;
int ind4;
String angle; 
String fuel; 
void setup() {
    Serial.begin(9600);
}
//12:585&52:78
//12:585&52:78&12:585&52:78777&12:585&52:78&12:585&52:78777999
void loop() {
 rc=Serial.readString();
// if ((Serial.available() > 0) && (rc = Serial.readString().indexOf("#")>0)) {
 if (rc.indexOf(":")>0) {
  Serial.println("OK");
//rc = Serial.readString();
//Serial.println(rc.indexOf("#") );
recvWithEndMarker();
 Serial.println("FUEL");
Serial.println(fuel);
 }
}
void recvWithEndMarker() {  
ind1 = rc.indexOf(':');  //finds location of first ,
results[0] = rc.substring(0, ind1);   //captures first data String
Serial.println("angle");
Serial.println(results[0]);
ind2 = rc.indexOf('&', ind1+1 );   //finds location of second ,
fuel = rc.substring(ind1+1, ind2);   //captures second data String
Serial.println("fuel");
Serial.println(fuel);
}


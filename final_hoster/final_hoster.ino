#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

int Buzzer = 6;        // used for Arduino
int Gas_analog = A0;    // used for Arduino
int Gas_digital = 7  ;   // used for Arduino

//int Buzzer = D2;        // used for ESP8266
//int Gas_analog = A0;    // used for ESP8266
//int Gas_digital = D1;   // used for ESP8266

// int Buzzer = 32;        // used for ESP32
//  int Gas_analog = 4;    // used for ESP32
// int Gas_digital = 2;   // used for ESP32

void setup() {
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);      
  pinMode(Gas_digital, INPUT);

  Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println("No valid sensor found");
      while(1);
   }
}

void loop() {
  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
  Serial.print("\t");
  Serial.print("Gas Class: ");
  Serial.print(gassensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
  Serial.println("m/s^2 ");
  
  if (gassensorAnalog > 400) {
    Serial.println("Gas");
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (Buzzer, LOW) ;  //no tone
  }
  else {
    Serial.println("No Gas");
  }
  delay(500);
}

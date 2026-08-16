#include <Wire.h> // For I2C

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();  // Begin I2C transmission as master
  Serial.println();
}

constexpr int pin = A0;

void loop() {
  // put your main code here, to run repeatedly:
  static int val0 = 0;
  const int val1 = map(analogRead(pin), 0, 1023, 0, 4095);
  if(val1!=val0) {
    val0=val1;
    Wire.beginTransmission(5);  //Transmit to slave 5
    Wire.write(val1 / 256);     //1 byte at a time
    Wire.write(val1 % 256);
    Serial.println(val1);
    Wire.endTransmission();
  }

  delay(50);
}

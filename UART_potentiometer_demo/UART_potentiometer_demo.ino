void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
}

constexpr int pin = A0;

void loop() {
  // put your main code here, to run repeatedly:
  static int val0 = 0;
  const int val1 = map(analogRead(pin), 0, 1023, 0, 255); // 8-bit for UART
  if(val1!=val0) {
    val0=val1;
    Serial.write(val1);
  }

  delay(50);
}

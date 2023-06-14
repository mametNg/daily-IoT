#define led 2 // Led pin

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

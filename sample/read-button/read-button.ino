#define pin 7 // D7

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop() {
    int read = digitalRead(pin);
    Serial.println(read);
    delay(500);
}

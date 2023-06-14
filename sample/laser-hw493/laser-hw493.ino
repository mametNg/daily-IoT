#define pin 7 // D7

// LEFT    = OUTPUT
// MID     = VCC
// RIGHT   = GND

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void loop() {
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
    delay(1000);
}

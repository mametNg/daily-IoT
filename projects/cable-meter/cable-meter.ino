#include <SPI.h>

int sellector_1 = 6;
int sellector_2 = 7;
int sellector_3 = 8;
int sellector_4 = 9;
int btnStart = 2;
int btnStop = 3;
int btnReset = 4;
int sensor = 10;
int relay = 11;

int isStart = 0;
int isReset = 0;
int isStop = 0;
int isSelector = 0;
int isRotate = 0;
int isAdd = 0;


void setup() {
  Serial.begin(9600);

  pinMode(btnStart, INPUT);
  pinMode(btnStop, INPUT);
  pinMode(btnReset, INPUT);
  pinMode(sellector_1, INPUT);
  pinMode(sellector_2, INPUT);
  pinMode(sellector_3, INPUT);
  pinMode(sellector_4, INPUT);
  pinMode(sensor, INPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, LOW);
}

void loop() {
  if (isStart == 1)
  {

    if (isSelector >= isRotate)
    {
      // Serial.println("PUTARAN = "+String(isSelector)+" == "+String(isRotate));

      if (isSelector == isRotate)
      {
        Serial.println("PUTARAN HABIS");
        isStart = 0;
        isSelector = 0;
        isRotate = 0;
        digitalWrite(relay, LOW);
      }

      // if (digitalRead(sensor) == HIGH)
      // {
      //   // Serial.println("TAMBAH");
      //   // isRotate++;
      //   isAdd = 1;
      // }

      while (digitalRead(sensor)) {
        isAdd = 1;

        if (digitalRead(btnStop) == HIGH)
        {
          digitalWrite(relay, LOW);
          Serial.println("STOP");
          isStart = 0;
          isStop = 1;
          isAdd = 0;
          delay(1000);
          break;
        }
      }

      if (isAdd)
      {
        isRotate++;
        Serial.println("PUTARAN = "+String(isRotate));
        isAdd = 0;
        delay(10);
      }

      if (digitalRead(btnStop) == HIGH)
      {
        digitalWrite(relay, LOW);
        Serial.println("STOP");
        isStart = 0;
        isStop = 1;
      }
      delay(0);
    }

  } else {

    if (digitalRead(sellector_1) == HIGH && isStop == 0)
    {
      Serial.println("sellector_1");
      isSelector = 994;
      delay(100);
    }
    if (digitalRead(sellector_2) == HIGH && isStop == 0)
    {
      Serial.println("sellector_2");
      isSelector = 497;
      delay(100);
    }
    if (digitalRead(sellector_3) == HIGH && isStop == 0)
    {
      Serial.println("sellector_3");
      isSelector = 331;
      delay(100);
    }
    if (digitalRead(sellector_4) == HIGH && isStop == 0)
    {
      Serial.println("sellector_4");
      isSelector = 232;
      delay(100);
    }

    if (digitalRead(btnStart) == HIGH && isSelector != 0)
    {
      Serial.println("START");
      isStart = 1;
      isStop = 0;
      delay(0);
      digitalWrite(relay, HIGH);
    }

    if (digitalRead(btnReset) == HIGH && isSelector != 0)
    {
      Serial.println("RESET");
      isStart = 0;
      isStop = 0;
      isSelector = 0;
      isRotate = 0;
      delay(0);
    }
  }
}

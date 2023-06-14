//#include <PIDController.h>
#include <SPI.h>
#include <AccelStepper.h>

#define pinRelay1 5     // Motor 1
#define pinRelay2 4     // Motor 2
#define pinStart 7      // Button Start
#define pinStop 8       // Button Stop
#define pinRever 9      // Button Reverse
#define pinLong20M 10   // Button Long20M
#define pinLong15M 11   // Button Long15M
// #define pinManual 12    // Button Manual
#define pinAuto 13      // Button Auto

#define pinSensor1 22   // Sensor Cable Meter
#define pinSensor2 24   // Sensor Motor1 off
#define pinSensor3 26   // Sensor UP speed motor 1
#define pinSensor4 28   // Sensor UP speed motor 1
#define pinSensor5 30   // Sensor UP speed motor 1
#define pinSensor6 32   // Sensor Turn off the system completely

#define stepperF 36   // Stepper Motor 1 front
#define stepperB 38   // Stepper Motor 1 back

int isAuto = 0; // Include with Auto or Manual
int isStart = 0; // Include with Start or Stop
int isLong = 0; // Select 15M or 20M
int isReverse = 0; // Back Rotate Stepper Motor
int isRotate = 0; // Count meter cable
int isAdd = 0; // addjust is rotate++
int isRun = 0; // run motor
int isReload = 0; // run motor

// Motor Forward
AccelStepper motorF(AccelStepper::DRIVER, stepperF);
// Motor Back Forward
AccelStepper motorB(AccelStepper::DRIVER, stepperB);

void setup() {
  Serial.begin(9600);

  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);
  pinMode(pinStart, INPUT);
  pinMode(pinStop, INPUT);
  pinMode(pinRever, INPUT);
  pinMode(pinLong20M, INPUT);
  pinMode(pinLong15M, INPUT);
  // pinMode(pinManual, INPUT);
  pinMode(pinAuto, INPUT);

  pinMode(pinSensor1, INPUT);
  pinMode(pinSensor2, INPUT);
  pinMode(pinSensor3, INPUT);
  pinMode(pinSensor4, INPUT);
  pinMode(pinSensor5, INPUT);
  pinMode(pinSensor6, INPUT);

  pinMode(stepperF, OUTPUT);
  pinMode(stepperB, OUTPUT);

  digitalWrite(pinRelay1, HIGH);
  digitalWrite(pinRelay2, HIGH);


  motorF.setMaxSpeed(350);  
  motorF.setSpeed(350);
  motorB.setMaxSpeed(350);  
  motorB.setSpeed(350);
}

void loop() {
  // Semi Manual
  if (digitalRead(pinAuto) == LOW)
  {
    // Serial.println("Manual");
    isLong = 0;
    isLong = 0;
    isStart = 0;
    isRotate = 0;

    if (digitalRead(pinRever) == HIGH)
    {
      while(true) {
        digitalWrite(stepperF, HIGH);
        motorB.runSpeed();
        if (digitalRead(pinRever) == LOW) break;
      }
    }
  }

  // Semi Auto
  if (digitalRead(pinAuto) == HIGH)
  {
    // Serial.println("Auto");
    // Motor off
    if (!isStart)
    {
      // Serial.println("PLEASE SELECT");
      isRotate = 0;
      if (digitalRead(pinLong15M) == HIGH && !isStart) {
        isLong = 678;
        // Serial.println("Selector 15");
      }
      if (digitalRead(pinLong20M) == HIGH && !isStart) {
        isLong = 895;
        // Serial.println("Selector 20");
      }

      if (digitalRead(pinStart) == HIGH && isLong >=1 && !isStart) {
        isStart = 1;
        // Serial.println("JALANKAN START");
      }

      if (digitalRead(pinSensor3)) isReload = 1;
      if (digitalRead(pinSensor4)) isReload = 1;
      if (digitalRead(pinSensor5)) isReload = 1;

      while(isReload){
        digitalWrite(stepperB, HIGH);
        motorF.runSpeed();
        if (digitalRead(pinSensor2)) isReload = 0;
      }
    }

    // Motor Start
    if (isStart)
    {
      digitalWrite(pinRelay1, LOW);
      digitalWrite(pinRelay2, LOW);

      while(isStart) {
        if (isRotate == isLong)
        {
          isReload = 1;
          isRun = 0;
          isAdd = 0;
          isStart = 0;
          isLong = 0;
          isRotate = 0;
          digitalWrite(pinRelay1, HIGH);
          digitalWrite(pinRelay2, HIGH);
        }

        if (isRun)
        {
          digitalWrite(stepperB, HIGH);
          motorF.runSpeed();
        }

        while(digitalRead(pinSensor1) && isStart) {
          isAdd = 1;
        
          if (isRun)
          {
            digitalWrite(stepperB, HIGH);
            motorF.runSpeed();
          }

          if (digitalRead(pinSensor1) == HIGH)
          {
            isAdd = 1;
          }

          if (digitalRead(pinSensor2) == HIGH)
          {
            isRun = 0;
          }

          if (digitalRead(pinSensor3) == HIGH)
          {
            isRun = 1;
            motorF.setMaxSpeed(350);  
            motorF.setSpeed(350);
          }

          if (digitalRead(pinSensor4) == HIGH)
          {
            motorF.setMaxSpeed(450);  
            motorF.setSpeed(450);
          }

          if (digitalRead(pinSensor5) == HIGH)
          {
            motorF.setMaxSpeed(550);  
            motorF.setSpeed(550);
          }

          if (digitalRead(pinStop) == HIGH)
          {
            // Serial.println("STOP");
            isRun = 0;
            isAdd = 0;
            isStart = 0;
            isLong = 0;
            isRotate = 0;
            digitalWrite(pinRelay1, HIGH);
            digitalWrite(pinRelay2, HIGH);
          }

          if (digitalRead(pinSensor6) == HIGH)
          {
            isRun = 0;
            isAdd = 0;
            isStart = 0;
            isLong = 0;
            isRotate = 0;
            digitalWrite(pinRelay1, HIGH);
            digitalWrite(pinRelay2, HIGH);
          }
        }

        if (digitalRead(pinSensor1) == HIGH)
        {
          isAdd = 1;
        }

        if (digitalRead(pinSensor2) == HIGH)
        {
          isRun = 0;
        }

        if (digitalRead(pinSensor3) == HIGH)
        {
          isRun = 1;
          motorF.setMaxSpeed(350);  
          motorF.setSpeed(350);
        }

        if (digitalRead(pinSensor4) == HIGH)
        {
          motorF.setMaxSpeed(450);  
          motorF.setSpeed(450);
        }

        if (digitalRead(pinSensor5) == HIGH)
        {
          motorF.setMaxSpeed(550);  
          motorF.setSpeed(550);
        }

        if (isAdd)
        {
          isAdd = 0;
          isRotate++;
          // Serial.println("PUTARAN = "+String(isRotate));
        }

        if (digitalRead(pinStop) == HIGH)
        {
          // Serial.println("STOP");
          isRun = 0;
          isAdd = 0;
          isStart = 0;
          isLong = 0;
          isRotate = 0;
          digitalWrite(pinRelay1, HIGH);
          digitalWrite(pinRelay2, HIGH);
        }

        if (digitalRead(pinSensor6) == HIGH)
        {
          isRun = 0;
          isAdd = 0;
          isStart = 0;
          isLong = 0;
          isRotate = 0;
          digitalWrite(pinRelay1, HIGH);
          digitalWrite(pinRelay2, HIGH);
        }
      }
    }
  }
}

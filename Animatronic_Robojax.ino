// C'est un code en C mais c'est pour Arduino

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);  // Pour le debug (si besoin)

  pwm.begin();
  
  pwm.setPWMFreq(60);  

  yield(); // Eviter le code bloquant
}

void loop() {
  pwm.setPWM(0,0,200);
  pwm.setPWM(15,0,200);
  delay(500);
  
  pwm.setPWM(0,0,300);
  pwm.setPWM(15,0,400);
  delay(500);
  
  pwm.setPWM(0,0,400);
  pwm.setPWM(15,0,200);
  delay(500);
  
  pwm.setPWM(0,0,500);
  pwm.setPWM(15,0,400);
  delay(500);
}


/*
#define SERVOMIN  125 // durée minimale pour laquelle le servomoteur n'est pas abimé
#define SERVOMAX  575 // durée maximale pour laquelle le servomoteur n'est pas abimé
*/

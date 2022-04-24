// C'est un code en C mais c'est pour Arduino

#include <Servo.h>

#define FPS 24
#define FRAMES 105
#define PWM_PIN 9
#define PWM_PIN_2 10

// Et il ne faut pas oublier de passer en FLOAT !!! (le tableau de base est en int)
const float Bone[105] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 11, 14, 17, 20, 23, 26, 30, 33, 37, 40, 44, 47, 50, 54, 57, 60, 63, 66, 68, 71, 74, 76, 78, 80, 82, 83, 85, 86, 87, 88, 89, 90, 90, 90,
  90, 89, 89, 88, 87, 86, 84, 83, 81, 79, 77, 74, 72, 69, 66, 63, 59, 56, 52, 49, 45, 41, 37, 33, 29, 25, 21, 17, 13, 9, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
};


const float frameDurationMillis = 1000 / FPS;
const float animationDurationMillis = FRAMES * frameDurationMillis;

Servo myservo;
Servo myservo2;
long startMillis = millis();

void setup() {
  myservo.attach(PWM_PIN);
  myservo2.attach(PWM_PIN_2);
}




void loop() {
  long currentMillis = millis();
  long positionMillis = currentMillis - startMillis;

  if (positionMillis >= animationDurationMillis) {
    startMillis = currentMillis;
  } else {
    long frame = floor(positionMillis / frameDurationMillis);
    float positionValue = pgm_read_float_near(Bone + frame);
    
    myservo2.write(positionValue); // On écrit une position en DEGRES!!!
    myservo.write(positionValue);
    // J'ai qu'un seul tableau de valeur, donc les 2 servos feront la même animation!
  }
}

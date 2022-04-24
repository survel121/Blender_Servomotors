#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define FPS 24
#define FRAMES 105

// Nécessaire dans la fonction AngleToPulse()
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Tableau de la première animation
const float Bone[105] PROGMEM = {
  19, 19, 20, 20, 21, 22, 23, 25, 27, 29, 31, 33, 36, 39, 42, 45, 49, 53, 57, 61, 66, 70, 75, 80, 85, 89, 94, 99, 104, 109, 114, 118, 123, 127, 131, 135, 138, 142, 145, 148, 151, 153, 155, 157, 159, 160, 162, 163, 164, 164,
  165, 165, 165, 164, 164, 163, 162, 161, 160, 158, 156, 155, 152, 150, 148, 145, 142, 139, 136, 133, 129, 126, 122, 118, 114, 110, 106, 102, 98, 94, 90, 86, 82, 78, 74, 71, 67, 64, 61, 58, 55, 52, 50, 48, 46, 44, 42, 40, 39, 38,
  37, 36, 36, 36, 35,
};

// Tableau d'une deuxième animation faite en off
const float Bone2[105] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 11, 14, 17, 20, 23, 26, 30, 33, 37, 40, 44, 47, 50, 54, 57, 60, 63, 66, 68, 71, 74, 76, 78, 80, 82, 83, 85, 86, 87, 88, 89, 90, 90, 90,
  90, 89, 89, 88, 87, 86, 84, 83, 81, 79, 77, 74, 72, 69, 66, 63, 59, 56, 52, 49, 45, 41, 37, 33, 29, 25, 21, 17, 13, 9, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
};

const float frameDurationMillis = 1000 / FPS;
const float animationDurationMillis = FRAMES * frameDurationMillis;

long startMillis = millis();

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  yield();
}

void loop() {
  long currentMillis = millis();
  long positionMillis = currentMillis - startMillis;

  if (positionMillis >= animationDurationMillis) {
    startMillis = currentMillis;
  } else {
    long frame = floor(positionMillis / frameDurationMillis);
    
    float positionValue = pgm_read_float_near(Bone + frame);
    float positionValue2 = pgm_read_float_near(Bone2 + frame);

    pwm.setPWM(15,0,angleToPulse(positionValue2));
    Serial.println(positionValue2);
    pwm.setPWM(0,0,angleToPulse(positionValue));
    Serial.println(positionValue);  // On vérifie que la valeur de positionValue change
  }
}


  // On ajoute la fonction de conversion de l'angle en signal
int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN, SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   return pulse;
}

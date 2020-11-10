#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "misc_func.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *M1 = AFMS.getMotor(1); //Left
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
Adafruit_DCMotor *M2 = AFMS.getMotor(2); //Right



double avg1[10] = {1,1,1,1,1,1,1,1,1,1}; // last 10 inputs of the line sensors. The averages will be calculated from these functions
double avg2[10] = {0,0,0,0,0,0,0,0,0,0};
double avg3[10] = {1,1,1,1,1,1,1,1,1,1};



void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  pinMode(ls1, INPUT); //left
  pinMode(ls2, INPUT); //centre
  pinMode(ls3, INPUT); //right

  M1 -> run(FORWARD);
  M2 -> run(FORWARD);
  M2 -> setSpeed(150);
  M1 -> setSpeed(150);
}

void loop(){

    //read sensor values and add their values into the lists
    update(&avg1[0], &avg2[0], &avg3[0], 10); 

    // loop to find averages of the lists
    double av[3] = {0,0,0};
    for(int i = 0; i <= 10; i++){
        av[0] += avg1[i];
        av[1] += avg2[i];
        av[2] += avg3[i];
    }
    av[0] = av[0]/10;
    av[1] = av[1]/10;
    av[2] = av[2]/10;

    //control algorithm
    double e = av[0] + av[2] - av[2]; // e = av1 + av2 - ev3
    double K = kp*e;

    //change motor powers
    M2 -> setSpeed(150 - K);
    M1 -> setSpeed(150 + K);

    delay(100);
}

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

int dir = 1; //1 corresponds to left, -1 to right
bool change = true;


void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  pinMode(ls1, INPUT); //left
  pinMode(ls2, INPUT); //centre -- in this version of the code, we will only use the centre sensor
  pinMode(ls3, INPUT); //right

  M1 -> run(FORWARD);
  M2 -> run(FORWARD);
  M2 -> setSpeed(150 + kw*dir);
  M1 -> setSpeed(150 - kw*dir);
}

void loop(){
    //this algorithm tries to make the robot follow the line by oscillating along it. The advantage is that it only uses 1 sensor, leaving 3 for detecting junctions and targets
    if (digitalRead(ls2) == LOW && change == false){
        delay(50);
        if (digitalRead(ls2) == LOW){ //to make sure the "low" reading isnt a sudden random drop
            M2 -> setSpeed(150 + kw*dir);
            M1 -> setSpeed(150 - kw*dir);
            change = true;
        }
    }
    if(digitalRead(ls2) == HIGH && change == true){
        delay(50);
        if (digitalRead(ls2) == HIGH){ //to make sure the "high" reading isnt a sudden random spike
            dir = -1*dir;
            M2 -> setSpeed(150 + kw*dir);
            M1 -> setSpeed(150 - kw*dir);
            change = false;
            delay(50);
        }
    }
    
}
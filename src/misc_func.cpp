#include <Arduino.h>
#include "variables.h"
#include "misc_func.h"

//Function to update the lists avg1,avg2,avg3 by deleting the oldest value on one end and inserting the newest value on the other
void shft(double *svg, int len, double IN){ //*svg passes first argument of array into the function, len is the arrays length, IN is 1/0
    for(int j = 0; j < len-1; j++ ){
        svg[j] = svg[j+1];
    }
    svg[-1] = IN;
}

//Function to find the newest sensor values and update avg1,avg2,avg3 all at once 
void update(double *svg1, double *svg2, double *svg3, int len){

    if (digitalRead(ls1) == HIGH) {
      shft(&svg1[0], 10, 1);
    }
    else{
      shft(&svg1[0], 10, 0);
    }
    if (digitalRead(ls2) == HIGH) {
      shft(&svg2[0], 10, 1);
    }
    else{
      shft(&svg2[0], 10, 0);
    }
    if (digitalRead(ls3) == HIGH) {
      shft(&svg2[0], 10, 1);
    }
    else{
      shft(&svg2[0], 10, 0);
    }
}

//Function to do a 180* turn (Assuming midde sensor comes of the line during the turn)
void turn180(){

  if(digitalRead(ls2) == LOW){
     M1 -> run(FORWARD);
     M2 -> run(BACKWARD);
     M1 -> setSpeed(150);
     M2 -> setSpeed(150);
     while(digitalRead(ls2) == LOW){
       delay(100);
     }
  }
  bool x = true;
  while(x == true){
    if(digitalRead(ls2)==LOW){
      M1 -> run(FORWARD);
      M2 -> run(FORWARD);
      M1 -> setSpeed(150);
      M2 -> setSpeed(150);
      x = false;
    }
  }
}

void line_follower_singleswitch(){
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

void setup_auto(int i){

  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  AFMS.begin(); // create with the default frequency 1.6KHz

  pinMode(ls1, INPUT); //left
  pinMode(ls2, INPUT); //centre
  pinMode(ls3, INPUT); //right

  M1 -> run(FORWARD);
  M2 -> run(FORWARD);

  //Which line following algorithm to set up for
  switch (i)
  {
  case 1: //Single swtich
    M2 -> setSpeed(150 + kw*dir);
    M1 -> setSpeed(150 - kw*dir);
    break;
  
  case 2:// "running average method"
    M2 -> setSpeed(150);
    M1 -> setSpeed(150);
    break;
  }
}

void lineFollower_3switch(){

    //read sensor values and add their values into the lists
    update(&avg1[0], &avg2[0], &avg3[0], 10); 

    // loop to find averages of the lists
    double av[3] = {0,0,0};
    for(int i = 0; i < 10; i++){
        av[0] += avg1[i];
        av[1] += avg2[i];
        av[2] += avg3[i];
    }
    av[0] = av[0]/10;
    av[1] = av[1]/10;
    av[2] = av[2]/10;

    //control algorithm
    double e = av[0] + av[1] - av[2]; // e = av1 + av2 - ev3
    double K = kp*e;

    //change motor powers
    M2 -> setSpeed(150 - K);
    M1 -> setSpeed(150 + K);
    delay(100);  
}
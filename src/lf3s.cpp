#include <Arduino.h>
#include "variables.h"
#include "electronics.h"

//Function to update the lists avg1,avg2,avg3 by deleting the oldest value on one end and inserting the newest value on the other
void shft(double *svg, int len, double IN)
{ //*svg passes first argument of array into the function, len is the arrays length, IN is 1/0
  for (int j = 0; j < len - 1; j++)
  {
    svg[j] = svg[j + 1];
  }
  svg[-1] = IN;
}

//Function to find the newest sensor values and update avg1,avg2,avg3 all at once
void update(double *svg1, double *svg2, double *svg3, int len)
{

  if (leftOnLine())
  {
    shft(&svg1[0], 10, 1);
  }
  else
  {
    shft(&svg1[0], 10, 0);
  }
  if (centerOnLine())
  {
    shft(&svg2[0], 10, 1);
  }
  else
  {
    shft(&svg2[0], 10, 0);
  }
  if (rightOnLine())
  {
    shft(&svg2[0], 10, 1);
  }
  else
  {
    shft(&svg2[0], 10, 0);
  }
}

void lf3s()
{
    // "running average method"

    //read sensor values and add their values into the lists
    update(&avg1[0], &avg2[0], &avg3[0], 10);

    // loop to find averages of the lists
    double av[3] = {0, 0, 0};
    for (int i = 0; i < 10; i++)
    {
        av[0] += avg1[i];
        av[1] += avg2[i];
        av[2] += avg3[i];
    }
    av[0] = av[0] / 10;
    av[1] = av[1] / 10;
    av[2] = av[2] / 10;

    //control algorithm
    double e = av[0] + av[1] - av[2]; // e = av1 + av2 - ev3
    double K = kp * e;

    //change motor powers
    ML->setSpeed(150 - K);
    MR->setSpeed(150 + K);
    delay(100);
}

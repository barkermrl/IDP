#include "misc_func.h"
#include <Arduino.h>

void shft(double *svg, int len, double IN){ //*svg passes first argument of array into the function, len is the arrays length, IN is 1/0
    for(int j = 0; j < len-1; j++ ){
        svg[j] = svg[j+1];
    }
    svg[-1] = IN;
}
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
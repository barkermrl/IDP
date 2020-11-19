#include <Arduino.h>
#include "electronics.h"
#include "state.h"
#include "line_following.h"

//State functions that contains all state variables

void getAtJunction()
{
    // if (ROnLine())
    // {
    //     delay(50);
    //     if (ROnLine())
    //     {
    //         atJunction= true;
    //     }
    // }
    /*else*/ if (LOnLine())
    {
        atJunction = true;
    }
    else
    {
        atJunction = false;
    }
}

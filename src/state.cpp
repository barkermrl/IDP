#include <Arduino.h>
#include "electronics.h"

//State functions that contains all state variables

void stateVar()
{
    /***********************
    TODO
    ***********************/
}

int getNumB()
{
    /***********************
    TODO
    ***********************/
};

int getNumR()
{
    /***********************
    TODO
    ***********************/
};

int getTunnelSide()
{
    /***********************
    TODO
    ***********************/
};

int getUntilJunc()
{
    /***********************
    TODO
    ***********************/
};

int getCurrentBlock()
{
    /***********************
    TODO
    ***********************/
};

int getDirection()
{
    /***********************
    TODO
    ***********************/
};


bool getAtJunction()
{
    if (ROnLine())
    {
        delay(50);
        if (ROnLine())
        {
            return true;
        }
    }
    else if (LOnLine())
    {
        delay(50);
        if (LOnLine())
        {
            return true;
        }
    }
    else {
        return false;
    }
}
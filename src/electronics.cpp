#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "variables.h"
#include "electronics.h"
#include "avr/interrupt.h"

#define ISR_PIN 0
#define ISR_PORT PORTA
#define ISR_VECT PORTA_PORT_vect

// Interrupt Vectors 
ISR(ISR_VECT)
{
	/* Insert your PORTA interrupt handling code here */
    // do something //
	/* Clear interrupt flags ** FIXED PORT WARN */
	ISR_PORT.INTFLAGS = (1 << ISR_PIN);
}

// Interrupt Enable Code
int8_t INT_init()
{
    /* We can ignore most of this -> Default round robin scheduling shoule be fine */
	/* IVSEL and CVT are Configuration Change Protected */

	// ccp_write_io((void*)&(CPUINT.CTRLA),0 << CPUINT_CVT_bp /* Compact Vector Table: disabled */
	//		 | 0 << CPUINT_IVSEL_bp /* Interrupt Vector Select: disabled */
	//		 | 0 << CPUINT_LVL0RR_bp /* Round-robin Scheduling Enable: disabled */);

	// CPUINT.LVL0PRI = 0x0 << CPUINT_LVL0PRI_gp; /* Interrupt Level Priority: 0x0 */

	// CPUINT.LVL1VEC = 0x0 << CPUINT_LVL1VEC_gp; /* Interrupt Vector with High Priority: 0x0 */
    
    /* IO Line */
	// <y> Pin direction 
    ISR_PORT.DIRCLR (1<< ISR_PIN);
	// <y> Initial level
	//INT1_set_level(false);
	// <y> Pull configuration
	//INT1_set_pull_mode(PORT_PULL_OFF);
	// <y> Invert I/O on pin
	//INT1_set_inverted(false);
	// <y> Pin Input/Sense Configuration
	ISR_PORT.PIN0CTRL = (1 << 3) | (0x1); // PUEN / BOTHEDGE

	ENABLE_INTERRUPTS();
	return 0;
}

// Variables for sensors
#define ls1 6 //Left sensor
#define ls2 7 //Middle sensor
#define ls3 8 //Right sensor

//Defining Motors:
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ML = AFMS.getMotor(2); //Left
Adafruit_DCMotor *MR = AFMS.getMotor(1); //Right

void electronics_setup()
{
    pinMode(ls1, INPUT); //left
    pinMode(ls2, INPUT); //centre
    pinMode(ls3, INPUT); //right

    pinMode(LED_BUILTIN, OUTPUT); //builtin LED
}

bool leftOnLine() {
    return (digitalRead(ls1) == LOW);
}

bool centerOnLine() {
    return (digitalRead(ls2) == LOW);
}

bool rightOnLine() {
    return (digitalRead(ls3) == LOW);
}

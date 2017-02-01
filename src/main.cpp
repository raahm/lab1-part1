// Author:         Garrett Vanhoy
// Net ID:         gvanhoy
// Date:           24 January 2017
// Assignment:     Lab 0 part 1
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "led.h"
#include "switch.h"
#include "timer.h"

/*
 * Define a set of states that can be used in the state machine using an enum
 */
int main(){

  initSwitchPB3();
  initLED();
  sei(); // enable global interrupts

  /*
  * Implement a state machine in the while loop which achieves the assignment
  * requirements.
  */
  while(1){
    /* After 100 ms, increment the binary number represented by the LEDs
    */
  }

  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed ant released. When the switch is pressed an released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/

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
typedef enum stateType_enum {
  switchReleased, dbPress, switchPressed, dbRelease
} stateType;

volatile stateType state = switchReleased;
volatile int num = 0;
volatile int multiplier = 1;

int main(){

  initSwitchPB3();
  initLED();
  initTimer1();
  sei(); // enable global interrupts
  Serial.begin(9600);

  // DDRB |= (1 << DDB7);

  /*
  * Implement a state machine in the while loop which achieves the assignment
  * requirements.
  */
  while(1){
    /* After 100 ms, increment the binary number represented by the LEDs
    */
    switch(state){
      case switchReleased:
        delayMs(multiplier % 2);
        break;
      case dbPress:
        _delay_ms(20);  // state exists soley to debounce the switch press
        state = switchPressed;
        multiplier++;
        break;
      case switchPressed:
        break;
      case dbRelease:
        _delay_ms(20);  // this state along with the former ensure time passes before states change
        state = switchReleased;
        break;
    }
  }
  return 0;
}

/* Implement an Pin Change Interrupt which handles the switch being
* pressed ant released. When the switch is pressed an released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
// Interrupt Service Routine
ISR(TIMER1_COMPA_vect){
  turnOnLEDWithChar(num);
  num++;
  if(num == 16) {
    num = 0;
  }
}
ISR(PCINT0_vect){
  if(state == switchReleased) {state = dbPress;}
  else {state = dbRelease;}
}

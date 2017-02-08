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
  countSlow, pressSlow, countFast, pressFast
} stateType;

// typedef enum stateType_enum{
//   waitPress, dbPress, waitRelease, dbRelease
// } stateType;
// volatile stateType state = waitPress;
// volatile int multiplier;
volatile stateType state = countSlow;
volatile int num = 0;

int main(){

  initSwitchPB3();
  initLED();
  sei(); // enable global interrupts
  Serial.begin(9600);

  DDRB |= (1 << DDB7);

  /*
  * Implement a state machine in the while loop which achieves the assignment
  * requirements.
  */
  while(1){
    /* After 100 ms, increment the binary number represented by the LEDs
    */
    switch(state){
      case countSlow:
        Serial.println("In state: countSlow\n");
        turnOnLEDWithChar(num);
        _delay_ms(200);
        break;
      case pressSlow:
        Serial.println("In state: pressSlow\n");
        turnOnLEDWithChar(num);
        _delay_ms(200);
        break;
      case countFast:
        Serial.println("In state: countFast\n");
        turnOnLEDWithChar(num);
        _delay_ms(100);
        break;
      case pressFast:
        Serial.println("In state: pressFast\n");
        turnOnLEDWithChar(num);
        _delay_ms(100);
        break;
    }
    num++;
    if(num == 16) {
      num = 0;
    }

  }
  return 0;
}

// while(1){
//     switch(state){
//       case waitPress:
//         break;
//       case dbPress:
//         _delay_ms(50);
//         state = waitRelease;
//         break;
//       case waitRelease:
//         break;
//       case dbRelease:
//         _delay_ms(50);
//         if(multiplier == 1){
//           OCR1AH = 0xF4;
//           OCR1AL = 0x24;
//           multiplier = 2;
//         }
//         else{
//           OCR1AH = OCR1AH >> 1;
//           OCR1AL = OCR1AL >> 1;
//           multiplier = 1;
//         }
//         state = waitPress;
//         break;
//     }
//   }
//
//   return 0;
// }

/* Implement an Pin Change Interrupt which handles the switch being
* pressed ant released. When the switch is pressed an released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
// Interrupt Service Routine
ISR(TIMER1_COMPA_vect){
  PORTB ^= (1 << PORTB7); // toggles the bit
  _delay_ms(20);
}
ISR(PCINT0_vect){
  // Serial.println("Got a change.");
  // if(state == pressSlow){
  //   state = countFast;
  // }
  // else if(state == pressFast){
  //   state = countSlow;
  // }
  if(state == countSlow) {
    _delay_ms(20);
    state = pressSlow;
  } else if(state == pressSlow) {
    _delay_ms(20);
    state = countFast;
  } else if(state == countFast) {
    _delay_ms(20);
    state = pressFast;
  } else {
    _delay_ms(20);
    state = countSlow;
  }
}

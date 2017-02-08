// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here.
* You will need to use CTC mode
*/
void initTimer1(){
  // set the timer mode to be "CTC"
  TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 1. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for 125
* 100 milliseconds
*
* NOTE : USE 256
*/
void delayMs(unsigned int delay){
  // set clock/prescalar for timer 0 to be clk/256
  TCCR1B &= ~(1 << CS10 | 1 << CS11);
  TCCR1B |= (1 << CS12);
  // set the OCR1A to 62,500 - 1
  OCR1AH = 0xF4;
  OCR1AL = 0x24;
  //enable the interrupt for the COMPA event
  TIMSK1 |= (1 << OCIE1A);
}

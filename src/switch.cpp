// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
  PORTB |= (1 << PORTB3);
  DDRB &= ~(1 << DDB3);
  // enable pin-change interrupts
  PCICR |= (1 << PCIE0);
  // enable interrupts on PB3
  PCMSK0 |= (1 << PCINT3);
}

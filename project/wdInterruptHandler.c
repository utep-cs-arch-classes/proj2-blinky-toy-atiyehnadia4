#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char state_count = 0;

  switch(dim_state){
  case 1:
    if((++blink_count == 20)){
      state_machine();
      blink_count = 0;
    }
    break;
  case 2:
    if((++blink_count == 250)){
      state_machine();
      blink_count = 0;
    }
    break;
  default:
    if((++blink_count == 30)){
      state_machine();
      blink_count = 0;
    }
  }
}

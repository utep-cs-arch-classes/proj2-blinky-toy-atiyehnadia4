#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char state_count = 0;

  if(++state_count == tempo){
    int repeat = 1;
    while(repeat <= 5){
      int count = 0;
      buzzer_set_period(0);
      while(count < 3000){
	count++;
      }
      repeat++;
    }
    state_machine();
    state_count = 0;
  }
  
  switch(dim_state){
  case 1:
    if((++blink_count == 20)){
      state_machine();
      blink_count = 0;
    }
    break;
  case 2:
    if((++blink_count == 40)){
      state_machine();
      blink_count = 0;
    }
    break;
  case 3:
    if((++blink_count == 80)){
      state_machine();
      blink_count = 0;
    }
    break;
  case 4:
    if((++blink_count == 100)){
      state_machine();
      blink_count = 0;
    }
    break;
  default:
    if((++blink_count == 40)){
      state_machine();
      blink_count = 0;
    }
  }
}

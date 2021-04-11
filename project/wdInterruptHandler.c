#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch_state = 0;
void music_interrupts(int tempo){
    int repeat = 1;
    while(repeat <= 5){
      int count = 0;
      buzzer_set_period(0);
      while(count < 30000){
	count++;
      }
      repeat++;
    }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char state_count = 0; 

  if(++blink_count == 30 && switch_state == 1){
    red_button_state_machine();
    blink_count = 0;
  }
  else if(blink_count == 30 && switch_state == 2){
    both_button_state_machine();
    blink_count = 0;
  }
  else if(blink_count == 30 && switch_state == 4){
    green_button_state_machine();
    blink_count = 0;
  }  
   
  //if((++blink_count == 2) && switch_state == 2){
    //state_machine();
      // blink_count = 0;
      //}

  //if((++state_count == 250)){
    // change_state();
    // state_count = 0;
    //}
}

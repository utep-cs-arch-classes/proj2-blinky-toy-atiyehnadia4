#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void controller(int state){
  switch(state){
  case 1:
    idle_state();
    state = 2;
    break;
  case 2:
    green_state();
    break;
  case 3:
    red_state();
    break;
  }
}

void idle_state(){
  green_on = 0;
  red_on = 0;
  led_changed = 0;
}

void green_state(){
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  red_on = 1;
  color = R;

  changed = 1;
  led_changed = changed;
  led_update();
}

void red_state(){
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  green_on = 1;
  color = G;

  changed = 1;
  led_changed = changed;
  led_update();
}

void state_advance()
{
  controller(3);
}

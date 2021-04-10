#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void controller(int state){
  char changed = 0;
  switch(state){
  case 1:
    idle_state();
    break;
  case 2:
    green_state();
    break;
  case 3:
    red_state();
    break;
  case 4:
    double_blink_state();
    break;
  }
  changed = 1;
  led_changed = changed;
  led_update();
  
}

void idle_state(){
  green_on = 0;
  red_on = 0;
  led_changed = 0;
}

void green_state(){
  static enum {I = 0, G = 1} color = G;
  switch(color){
  case G:
    red_on = 1;
    green_on = 0;
    color = I;
    break;
  case I:
    idle_state();
    color = G;
    break;
  }
}

void red_state(){
  static enum {I = 0, R = 1} color = R;
  switch(color){
  case R:
    green_on = 1;
    red_on = 0;
    color = I;
    break;
  case I:
    idle_state();
    color = R;
    break;
  }
}

void double_blink_state(){
  static enum {R = 0, G = 1} color = R;
  switch(color){
  case R:
    green_on = 1;
    red_on = 0;
    color = G;
    break;
  case G:
    green_on = 0;
    red_on = 1;
    color = R;
    break;
  }
}

void state_advance()
{
  controller(2);
}

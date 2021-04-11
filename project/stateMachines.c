#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

unsigned char dim_state = 0;
static char state;
static char red = 0;
static char red_speed = 0;

void idle_state(){
  green_on = 0;
  red_on = 0;
  led_changed = 0;
}

void green_blink_state(){
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

void red_blink_state(){
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
  static enum {R = 0, G = 1} color = G;
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

void green_solid_state(){
  static enum {G = 1} color = G;
  green_on = 0;
  red_on = 1;
  color = G;
}

void red_solid_state(){
  static enum {R = 1} color = R;
  red_on = 0;
  green_on = 1;
  color = R;
}

void change_red_button_clicks(int button){
  switch(button){
  case 2:
    red = 1;
    break;
  case 3:
    red = 2;
    break;
  }
}

void red_dim_or_bright(){
  switch(red_speed){
  case 0:
    dim_state = 1;
    red_speed = 1;
    red_blink_state();
    break;
  case 1:
    dim_state = 2;
    red_blink_state();
    change_red_button_clicks(button_clicks1);
    break;
  }
}

void red_state(){
  switch(red){
  case 0:
    red_solid_state();
    change_red_button_clicks(button_clicks1);
    break;
  case 1:
    red_blink_state();
    change_red_button_clicks(button_clicks1);
    break;
  case 2:
    red_dim_or_bright();
    change_red_button_clicks(button_clicks1);
    break;
  case 3:
    green_blink_state();
    //TODO BUZZER
    break;    
  default:
    idle_state();
    break;
  } 
}

void state_machine(){
  char changed = 0;
  switch(switch_state){
  case 1:
    red_state();
    break;
  }
  
  changed = 1;
  led_changed = changed;
  led_update();
}

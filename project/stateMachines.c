#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

unsigned char dim_state = 0;
static char state;
static char red = 0;
static char red_speed = 0;
static int song_counter = 0;

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
  case 4:
    red = 3;
    break;
  default:
    red_solid_state();
    break;
  }
}

void red_dim_or_bright(){
  switch(red_speed){
  case 0:
    dim_state = 1;
    red_blink_state();
    dim_state = 2;
    red_blink_state();
    dim_state = 3;
    red_blink_state();
    dim_state = 1;
    red_blink_state();
    break;
  }
}

void buzzer_song(){
  switch(song_counter){
  case 0:
  case 1:
  case 2:
  case 4:
    buzzer_set_period(750);
    song_counter++;
    break;
  case 3:
    buzzer_set_period(950);
    song_counter++;
    break;
  case 5:
    buzzer_set_period(630);
    song_counter++;
    break;
  case 6:
    buzzer_set_period(1260);
    song_counter++;
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
    green_blink_state();
    change_red_button_clicks(button_clicks1);
    break;
  case 3:
    tempo = 50;
    red_blink_state();
    buzzer_song();
    change_red_button_clicks(button_clicks1);
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

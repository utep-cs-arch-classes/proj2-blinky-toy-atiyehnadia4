#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

static char red = 0;
static char green = 0;
static char both = 0;
static char dim = 0;
static char state = 0;
static int red_song_counter = 0;
static int green_song_counter = 0;
static int both_song_counter = 0;


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
  led_changed = 1;
  led_update();
}

void double_solid_state(){
  static enum {RG = 2} color = RG;
  green_on = 1;
  red_on = 1;
  color = RG;
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
  default:
    buzzer_set_period(0);
    red_solid_state();
    break;
  }
}

void red_buzzer_song(){
  switch(red_song_counter){
  case 0:
    buzzer_set_period(750);
    red_song_counter++;
    break;
  case 1:
  case 2:
  case 11:
  case 12:
    buzzer_set_period(630);
    red_song_counter++;
    break;
  case 3:
  case 4:
  case 13:
    buzzer_set_period(560);
    if(red_song_counter == 14){
      red_song_counter = 0;
    }
    else{
      red_song_counter++;
    }
    break;
  case 5:
  case 7:
  case 9:
    buzzer_set_period(950);
    red_song_counter++;
    break;
  case 6:
  case 8:
  case 10:
    buzzer_set_period(500);
    red_song_counter++;
    break;
  }
}

void red_button_state_machine(){
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
    red_blink_state();
    red_buzzer_song();
    change_red_button_clicks(button_clicks1);
    break;
  }
 
  led_changed = 1;
  led_update();
}


void change_green_button_clicks(int button){
  switch(button){
  case 2:
    green = 1;
    break;
  case 3:
    green = 2;
    break;
  default:
    buzzer_set_period(0);
    green_solid_state();
    break;
  }
}

void green_buzzer_song(){
  switch(green_song_counter){
  case 0:
    buzzer_set_period(750);
    green_song_counter++;
    break;
  case 1:
  case 2:
  case 11:
  case 12:
    buzzer_set_period(630);
    green_song_counter++;
    break;
  case 3:
  case 4:
  case 13:
    buzzer_set_period(560);
    if(green_song_counter == 14){
      green_song_counter = 0;
    }
    else{
      green_song_counter++;
    }
    break;
  case 5:
  case 7:
  case 9:
    buzzer_set_period(950);
    green_song_counter++;
    break;
  case 6:
  case 8:
  case 10:
    buzzer_set_period(500);
    green_song_counter++;
    break;
  }
}

void green_button_state_machine(){
  switch(green){
  case 0:
    green_solid_state();
    change_green_button_clicks(button_clicks4);
    break;
  case 1:
    green_blink_state();
    change_green_button_clicks(button_clicks4);
    break;
  case 2:
    green_blink_state();
    green_buzzer_song();
    change_green_button_clicks(button_clicks4);
    break;
  }
 
  led_changed = 1;
  led_update();
}

void both_buzzer_song(){
  switch(both_song_counter){
  case 0:
  case 1:
  case 2:
  case 3:
    buzzer_set_period(750);
    both_song_counter++;
    break;
  case 4:
    buzzer_set_period(950);
    both_song_counter++;
    break;
  case 5:
    buzzer_set_period(630);
    both_song_counter++;
    break;
  case 6:
    buzzer_set_period(1260);
    both_song_counter++;
    break;
  }
}

void change_both_button_clicks(int button){
  switch(button){
  case 2:
    both = 1;
    break;
  case 3:
    both = 2;
    break;
  default:
    double_solid_state();
    buzzer_set_period(0);    
    break;
  }
}


void both_button_state_machine(){
  switch(both){
  case 0:
    double_solid_state();
    change_both_button_clicks(button_clicks3);
    break;
  case 1:
    double_blink_state();
    change_both_button_clicks(button_clicks3);
    break;
  case 2:
    double_blink_state();
    both_buzzer_song();
    change_both_button_clicks(button_clicks3);
    break;
  }

  led_changed = 1;
  led_update();
}

void dim_green(){
  switch(dim){
   case 0:
     green_blink_state();
     break;
   case 1:
     green_solid_state();
     break;
  }
  led_changed = 1;
  led_update();
}

void dim_red(){
  switch(dim){
   case 0:
     red_blink_state();
     break;
   case 1:
     red_solid_state();
     break;
  }
  led_changed = 1;
  led_update();
}

void dim_both(){
  switch(dim){
  case 0:
    double_blink_state();
    break;
  case 1:
    double_solid_state();
    break;
  }
  led_changed = 1;
  led_update();
}

void change_state(){
  if(dim == 0){
    dim = 1;
  }
  else if(dim == 1){
      dim = 0;

  }
}

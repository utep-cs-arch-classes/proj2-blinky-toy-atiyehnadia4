#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

static char red = 0;
static char green = 0;
static int red_song_counter = 0;
static int green_song_counter = 0;


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
    tempo = 90;
    red_blink_state();
    red_buzzer_song();
    change_red_button_clicks(button_clicks1);
    break;
  }
 
  led_changed = 1;
  led_update();
}


 change_green_button_clicks(int button){
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
    tempo = 90;
    green_blink_state();
    green_buzzer_song();
    change_green_button_clicks(button_clicks4);
    break;
  }
 
  led_changed = 1;
  led_update();
}


//void dim_state_machine(){
//char changed = 0;
//switch(state){

//changed = 1;
//led_changed = changed;
//led_update();
//}

//void change_state(){
//if(state == 0){
//  state = 1;
//}
// else if(state == 1){
    //  state = 2;
// }
// else if(state == 2){
//  state = 3;
// }
//  else if(state == 3){
//  state = 4;
// }
// else{
//  state = 0;
//  }


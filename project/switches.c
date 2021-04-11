#include <msp430.h>
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed; /* effectively boolean */

char switch_state = 0;
char tempo = 0;  
char button_clicks1, button_clicks2, button_clicks3, button_clicks4 = 0;


static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  char switch1_state_down = (p2val & S1) ? 0:1;
  char switch2_state_down = (p2val & S2) ? 0:1;
  char switch3_state_down = (p2val & S3) ? 0:1;
  char switch4_state_down = (p2val & S4) ? 0:1;

  if(switch1_state_down == 0){
    switch_state = 1;
    button_clicks1 += 1;
  }

  else if(switch2_state_down == 0){
    switch_state = 2;
    button_clicks2 += 1;
  }

  else if(switch3_state_down == 0){
    switch_state = 3;
    button_clicks3 += 1;
  }

  else if(switch4_state_down == 0){
    switch_state = 4;
    button_clicks4 += 1;
  }
  switch_state_changed = 1;
  led_update();
}

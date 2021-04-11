#ifndef switches_included
#define switches_included

#define S1 BIT0
#define S2 BIT1
#define S3 BIT2
#define S4 BIT3
#define SWITCHES (S1 | S2 | S3 | S4)		/* only 1 switch on this board */

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed, tempo;

extern char switch_state, button_clicks1, button_clicks2, button_clicks3, button_clicks4;
/* effectively boolean */

#endif // included

# Blinky Buzzy Toy

The toy I implemeneted is a basic toy that blinks buzzes and implements the
buttons on the MSP430 Expansion Board to perform these actions.

## Compiling and Running
   To compile my toy, I clean the directory by utilizing the
   '''bash
   "make clean"
   '''
   function made in the Makefile to ensure the most updated version of toy.elf
   is in the directory.
   After that I utilize the
   '''bash
   "make"
   '''
   fucntion to compile and run everything by
   generating the .elf files and .o files needed for running.
   The final step is to call
   '''bash
   "make load"
   '''
   which loads all the code onto the
   MSP430 and the toy is ready to play with!

   
## How to Use
   ## Suggested use
      Start with either button 1 or 4, followed by button 3, and finish with button 2.

## Button 1
   Button 1 has four functionalities.
   - 1 Single Click will show a solid red light
   - 2 Clicks a blinking red light
   - 3 Clicks plays the Iron Man Song while blinking a red light
   - 4 Clicks returns to the solid red light
## Button 2
   Button 2 has a single function, when pressed both the red and green light
   will appear bright and then dim

## Button 3
   Button 3 has four functionalities.
   - 1 Click will show solid red and green leds
   - 2 Clicks will blink both the red and green LEDS
   -3 Clicks plays the Mario Opening Theme while blinking both green and red
   leds
   -4 Clicks returns to the solid red and green lights.

## Button 4
   Button 4 has four functionalities.
   - 1 Click will show a solid green light
   - 2 Clicks a blinking green light
   - 3 Clicks plays the Iron Man Song while blinking a green light
   - 4 Clicks returns to the solid green light

Please enjoy :)

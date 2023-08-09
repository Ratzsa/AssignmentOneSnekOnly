# Yrkesakademin Trollhättan
# Software Developer Electrical & Autonomous Vehicles

## SV23TR E. Programmering och utveckling av inbyggda system
## YH00260-2020-3

## Assignment 1: Etch-a-sketch & Snake

Using emulation: https://wokwi.com/projects/296234816685212169
Step 1 (G): Rewrite the code to C code. (Completed 2023-06-05)
Step 2 (VG): Implement the game Snake.

This assignment must be done on the Arduino UNO (ATmega328p) to practice programming on low resource hardware.

Joystick controls heavily inspired by and analogRead files from: https://github.com/aspcodenet/avrjoystick/tree/main
Display libraries from: https://github.com/aspcodenet/avrmax72

## INSTRUCTIONS ON GETTING THE GAME TO WORK ON DIFFERENT NUMBER OF SEGMENTS OR ON PHYSICAL HARDWARE
Change the following in config.h:

# Line 11:
#define NUMBER_OF_SEGMENTS 2
Change this to the number of segments you are using.

EITHER
# Line 15:
#define MAX_COLUMNS 16
OR
# Line 16:
#define MAX_ROWS 8
This depends on how the display or displays are connected and placed. For a single display plugged into a breadboard on a regular Arduino, change MAX_COLUMNS to 8. This setting can be a bit trial and error to understand how the displays are aligned and what is up and down.

# Lines 27-36:
#define JOYSTICK_VERTICAL 0
#define JOYSTICK_HORIZONTAL 1

#define MOVE_UP 0
#define MOVE_RIGHT 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3

#define HORIZONTAL_AXIS 0
#define VERTICAL_AXIS 1

These can be complicated to get right, as neither the joystick module nor the display are plugged into a breadboard the same way as shown in the Wokwi project. It might be adjustable with these lines, but it is probably easier to just change the makeMove() function in game.c
Personally I changed *(y)-- to *(y)++ and *(y)++ to *(y)--.
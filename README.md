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

## TODO
Step 2.

## Start
This project will be exclusively the game Snake for the assignment's second step.
For Step 1, Etch-a-sketch, refer to https://github.com/Ratzsa/AssignmentOneSnake
My first plan was to have a 2-dimensional array with the size 10x18, which is 2 fields more in both directions than the LEDs we are using
in the project, with the border "virtual" LEDs being considered "on" at all times. The reason for this was to handle collisions easily.
After some thought that idea is now scrappyed and I will instead only use the 8x16 LEDs available.
# Update 2023-07-14
I have used a config.h file for this project to make it look slightly more readable by moving out a lot of code there, as well as allowing
the user to set up the play area for themself. It also contains the struct definitions used.

## 2023-06-11
Using the main.c file from Step 1 as a base for working controls.
For the game I will need millis.c and millis.h.

## 2023-07-03
Have been struggling with getting anything to work for a month but will now get back to it and take it step by step.
First I will try to get it to set a random LED on physical hardware for 2 seconds, clear that, and set another. This will be done
using millis.

## 2023-07-13
Finally figured out that you can NOT write *x++; to change the value of the variable in x.
Now movement works. Have implemented millis, and moved around some code to use functions and properly use game.c.
Next step is to use the structs for the snake. After that adding apples and get the snake to grow when eating apples. Finally I will add
game over statuses for hitting yourself and hitting walls.
Structs have been put in and seem to be working.

## 2023-07-14
Will start off by ending the game if the snake hits a wall. Changed coordinates of the snake from uint8_t to int8_t to be able to get negative values.
The snake will die at either x or y being -1 or 16/8 respectively, or however large the playing field is.
Implementing death by self collision was relatively simple. Just had to make sure the snake had more than one body part, or it would collide with itself automatically.
Left TODO: Implementing food and make the snake grow when eating. Have tried getting the snake to grow every 7.5 seconds, and that seems to work perfectly fine.
Food should not be a massive problem, but might be a good amount of code to write.
Successfully (?) implemented a win state, which no human will ever achieve but it's there now.
The game now has food. The snake grows when it eats food. One little bug remains. Sometimes the game does not turn on the LED for the food. Not sure how to fix that.

## 2023-07-16
The bug that made the food LED sometimes not work seems to be fixed. It was probably a bit of an overload due to how the function was written.
Have fixed the function, and everything seems to be working as it should. Changed the snake length variable from uint8_t to uint16_t because with only uint8_t you are limited to a playing field of 128 LEDs. Will do some testing to see if the win condition works or if there are any other bugs.
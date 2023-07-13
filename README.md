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

## 2023-06-11
Using the main.c file from Step 1 as a base for working controls.
For the game I will need millis.c and millis.h.

## 2023-07-03
Have been struggling with getting anything to work for a month but will now get back to it and take it step by step.
First I will try to get it to set a random LED on physical hardware for 2 seconds, clear that, and set another. This will be done
using millis.

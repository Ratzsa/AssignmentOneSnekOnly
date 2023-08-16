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
NOTHING I AM DONE

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

Started working on proper unit testing. Found out that I had removed the Makefile I used specifically for unit testing. Was luckily able to get it back from Github.
Unit testing does not work at all at the moment. It objects to #include <util/interrupt.h> in game.c. Also having problems getting definitions into the test file. Both issues should be solvable.

## 2023-07-19
Renamed README.md to DEVELOPMENT.md. Will make a new README.md for instructions on making it work. Was also thinking of making another .md, but I forgot for what.
Replaced (MAX_COLUMNS * MAX_ROWS -1) in the win condition with a macro named MAX_SNAKE_LENGTH.

## 2023-07-21
Started cleaning up the code. Put the initialization stuff in the new initSnake function to get the main function to look cleaner.
Removed one of the while loops in game.c. The original intent was to never go back to main, but now the first/outer while loop is instead part of main.
Switched the win condition to after the lose conditions. Should be fine either way but this way I KNOW I don't win when I should have lost.
Moved struct definitions out of config.h to game.h.
Finished the sort of crappy readme file. Probably not helpful.
Removed some old comments and extra empty lines. But also added extra empty lines to make it more pleasing to look at for myself.
Removed the while loops from the start/end/win screen functions and replaced with a buttonClick function. For some reason this gave me a few weird glitches, possibly related to eachother. It seems that sometimes the snake is moving vertically at the start of the game instead of horizontally. Not sure why, but it doesn't seem to happen often. Will ignore it for now and hope it goes away.
Added a bool in the snakeGame function so that instead of checking the game logic every cycle, it now only checks if the snake has moved. Should make for a much more pleasant gaming experience now when the Arduino is not running on 100% constantly.
Changed setMovement in game.c to a switch instead of a bunch of if statements. Looks way better and was easy to do as previousMove can only have 2 values. No need to test a bunch of if statements if a simple switch is enough. Should have improved performance slightly.
Wanted to use uint8_t instead of int8_t in the SnakeBody struct, but when I do the snake can move to negative squares and that's just not very good.
\* This seems to be fixed after changing
# if(snakeHead.snakeX < 0 || snakeHead.snakeY < 0 || snakeHead.snakeX == MAX_COLUMNS || snakeHead.snakeY == MAX_ROWS)
to
# if(snakeHead.snakeX < 0 || snakeHead.snakeY < 0 || snakeHead.snakeX >= MAX_COLUMNS || snakeHead.snakeY >= MAX_ROWS)
It should also be fixed if I remove
# snakeHead.snakeX < 0 || snakeHead.snakeY < 0
from the if statement. Will do more testing but should be fine now.

## 2023-08-09
Made code look nice! Instead of 50 individual lines of code saying "setMarker(x, y);" there is now an array for each "text" displayed on screen, with a small code block to display the correct LEDs. The code block is repeating and there could be a separate function for it, but have not managed to get a pointer to a multidimensional array working yet. At the same time, a pointer means using more memory.

## 2023-08-16
Function to display the text screens now done. Just need to fix unit testing and everything should be 100% awesome.
/**
 * Main file containg the main function
 * @file main.cpp
 * @author Maxence
 * @version 1.0
*/

/*
INFO:
  - To compile the projet : g++ *.cpp -o executable -lSDL2 -lSDL2_image
  - To show all library of SDL2 : sudo apt-cache search libsdl2

  - Pixel scale : One pixel on texture = 10 pixel on game
    So my background is 63x112
    If I want 16/9 1000/9*16
    630x1120
*/

#include <ctime>

#include "Game.hpp"

#define CONSTANT_g 20 // Should be 9.81 but 20 gives a better experience
#define WINDOW_WIDTH 1120
#define WINDOW_HEIGHT 630
#define FRAMERATE 60
#define WAITTIME (1000/FRAMERATE)
#define SCORE_DIGITS_NUMBER 6
#define BARRIERS_SPEED 225 // px/s

int main(int argc, char **argv) {
  
  srand(time(NULL)); // Init the random module (with the current time as a seed I belive)
  
  Game maingame(WINDOW_WIDTH, WINDOW_HEIGHT, FRAMERATE, CONSTANT_g, SCORE_DIGITS_NUMBER, BARRIERS_SPEED);
  maingame.start();
  
  return 0;
  
}

/*
The regular cactus are sometimes to big to jump in a simple jump
*/
/*

Ok so I just want to create a simple game.
You drive a car and you have to dodge the cars that come in front of you


For the mainloop, the basic thing is just to start counting ticks and then to wait depending on the time spent
Get the time with SDL_GetTicks()

*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Need to compile with -lm
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMERATE 30
#define WAITTIME (1000/FRAMERATE)

// Player car
#define PLAYER_CAR_WIDTH 70
#define PLAYER_CAR_HEIGHT 100
#define PLAYER_CAR_HALF_WIDTH 35
#define PLAYER_CAR_HALF_HEIGHT 50
#define MIN_PLAYER_POS (0+PLAYER_CAR_HALF_WIDTH+10)
#define MAX_PLAYER_POS (WINDOW_WIDTH-PLAYER_CAR_HALF_WIDTH-10)

//To compile : gcc file.c -o executable $(sdl2-config --cflags --libs) -lm

typedef struct color {
  int red;
  int green;
  int blue;
  float alpha;
} Color;

typedef struct car {
  Color color;
  int x;
  int y;
} Car;

struct car generateRandomCar(int x, int y) {
  Car cur_car;
  cur_car.color.red = 100 + rand() % 155;
  cur_car.color.green = 100 + rand() % 155;
  cur_car.color.blue = 100 + rand() % 155;
  cur_car.y = x;
  cur_car.x = y;
  
  return cur_car;
}

//Log function
void GraphicLog(char *errorString) {
  strcat(errorString,SDL_GetError());
  strcat(errorString,"\n");
  SDL_Log(errorString);
  exit(EXIT_FAILURE);
}

int setDrawColor(SDL_Renderer *renderer, Color color) {
  return SDL_SetRenderDrawColor(renderer,color.red ,color.green ,color.blue , color.alpha);
}

void increment(int *value, int amount, int max) {
  (*value) += amount;
  if((*value) > max){
    *value = max;
  }
}

void decrement(int *value, int amount, int min) {
  *value -= amount;
  if((*value) < min){
    *value = min;
  }
}

int main(int argc, char **argv) {
  
  srand(time(NULL)); // Get random number between 0 and n-1 with rand() % n
  
  /*---------------------------------------------------------*/
  //Preparing the window
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    GraphicLog("Error during initalization");
  }
  
  //Creating the window
  window = SDL_CreateWindow("High Road Dodger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  
  if(window==NULL){
    GraphicLog("Problem when openning the window");
  }
  /*---------------------------------------------------------*/
  
  //Setting up the renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  SDL_RenderPresent(renderer);
  
  // Initalization of variables
  int lastTime = 0;
  int timeElapsed = 0;
  int timeToWait = 0;
  bool quit = false;
  SDL_Event event;
  
  Color backgroundColor;
  backgroundColor.red = 50;
  backgroundColor.green = 50;
  backgroundColor.blue = 50;
  backgroundColor.alpha = 1;
  
  Color userCarColor;
  userCarColor.red = 0;
  userCarColor.green = 255;
  userCarColor.blue = 0;
  userCarColor.alpha = 1;
  
  Color otherCarColor;
  otherCarColor.red = 255;
  otherCarColor.green = 0;
  otherCarColor.blue = 0;
  otherCarColor.alpha = 1;
  
  int playerXPos = WINDOW_WIDTH / 2;
  int playerYPos = WINDOW_HEIGHT / 2;
  
  SDL_Rect playerCar;
  playerCar.x = playerXPos - PLAYER_CAR_HALF_WIDTH;
  playerCar.y = playerYPos - PLAYER_CAR_HALF_HEIGHT;
  playerCar.w = PLAYER_CAR_WIDTH;
  playerCar.h = PLAYER_CAR_WIDTH;
  
  int counter = 1;
  SDL_Rect rectToDraw;
  rectToDraw.x = 10;
  rectToDraw.y = 10;
  rectToDraw.w = counter;
  rectToDraw.h = 100;
  
  // Keystates
  bool arrow_left_pressed = false;
  bool arrow_right_pressed = false;

  while(!quit) {
    
    lastTime = SDL_GetTicks();
    
    while(SDL_PollEvent( &event )) {
      
      if(event.type == SDL_QUIT) {
        quit = true;
      }
      
      switch(event.type) {
        case SDL_KEYDOWN:
          if(event.key.repeat == 0) {
            switch(event.key.keysym.sym) {
              case SDLK_LEFT:
                arrow_left_pressed = true;
                break;
              
              case SDLK_RIGHT:
                arrow_right_pressed = true;
                break;
            }
          }
          break;
          
        case SDL_KEYUP:
          if(event.key.repeat == 0) {
            switch(event.key.keysym.sym) {
              case SDLK_LEFT:
                arrow_left_pressed = false;
                break;
              
              case SDLK_RIGHT:
                arrow_right_pressed = false;
                break;
            }
          }
          break;
        
        default:
          break;
      }
    }
    
    if(quit){ // Forced for exit to work apparently
      break;
    }
    
    // Update internal states depending on events
    if(arrow_right_pressed){
      increment(&playerXPos, 10, MAX_PLAYER_POS);
    }
    if(arrow_left_pressed){
      decrement(&playerXPos, 10, MIN_PLAYER_POS);
    }
    
    // Generate the cars
    
    // Screen actions
    //Clear the screen
    
    setDrawColor(renderer, backgroundColor);
    
    SDL_RenderClear(renderer);
    
    playerCar.x = playerXPos - PLAYER_CAR_HALF_WIDTH;
    playerCar.y = playerYPos - PLAYER_CAR_HALF_HEIGHT;
    
    setDrawColor(renderer, userCarColor);
    SDL_RenderFillRect(renderer, &playerCar);
    
    SDL_RenderPresent(renderer);
    
    timeElapsed = SDL_GetTicks() - lastTime; // In ms
    timeToWait = WAITTIME - timeElapsed; // This seems to work
    
    if(timeToWait > 0){
      SDL_Delay(timeToWait);
    }
    
  }
  
  //Clearing our work space
  if(SDL_RenderClear(renderer)!=0){
    GraphicLog("Problème en nettoyant le renderer");
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}

/*

Game loop:
  - Check for events:
    - Quit
    - Keyboard
    
  - Spawn new car if needed
  
  - Update internal state depending on events
  
  - Update screen

*/
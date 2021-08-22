/**
 * The file containg the Game class implementation
 * @file Game.cpp
 * @author Maxence
 * @version 1.0
*/

#include <cstdlib>
#include <cmath> // Need to compile with -lm
#include <cstring>
#include <cstdio>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // To load the texture (IMG_...)

#include "Player.hpp"
#include "Barrier.hpp"
#include "Color.hpp"
#include "Game.hpp"

#define FLOOR_HEIGHT 50 // To add as property leter

Game::Game(int windowWidth, int windowHeight, int frameRate, float constant_g, int numberOfScoreDigits, int barriersSpeed): window(NULL), renderer(NULL), playerTexture(NULL), cactusTexture(NULL), quit(false), lastTime(0), timeElapsed(0), timeToWait(0), backgroundColor(50, 50, 50), playerColor(0, 255, 0), m_player(windowWidth / 2, windowHeight - 50 - FLOOR_HEIGHT, 100, 100, frameRate, constant_g), background(windowWidth/2, windowHeight/2, windowWidth, windowHeight), spaceBarPressed(false), lastBarrierSpawned(0), score(0), jumpsSinceFloor(0), maxJumps(2), gameWindowWidth(windowWidth), gameWindowHeight(windowHeight), gameFrameRate(frameRate), scoreDigitsNumber(numberOfScoreDigits), waitTime(1000 / frameRate), gameBarriersSpeed(barriersSpeed) {
}

void Game::start() {
  setupSDL();
  
  // Main loop
  while(!quit) {
    
    lastTime = SDL_GetTicks();
    
    handleInput();
    
    
    // Computing work
    
    // React to the current input
    if(spaceBarPressed) {
      spaceBarPressed = false;
      if(jumpsSinceFloor < maxJumps) { // Max number of jumps
        switch(jumpsSinceFloor) {
          case 0:
            m_player.jump(15000); // 15000 Newtons
            break;
            
          case 1:
            m_player.jump(15000); // Can change the force of the second jump
            score = (score > 0 ? score - 1 : score);
            break;
            
          default:
            break;
        }
        jumpsSinceFloor++;
      }
    }
    
    // Update player speed:
    /*
    1. Update the position depending on the velocity
    2. Update the velocity depending on the gravity vector
    */
    
    m_player.applySpeed();
    
    m_player.applyGravity();
    
    if(m_player.isOnTheFloor()) {
      jumpsSinceFloor = 0;
    }
    
    m_player.updateRect();
    
    spawnBarrier(); // Maybe
    
    checkForPlayerCollision();

    setDrawColor(renderer, backgroundColor);
    SDL_RenderClear(renderer);

    background.draw(renderer);
    
    moveBarriersAndRemoveIfNeeded();
    
    m_player.draw(renderer);
    
    drawNumberOnScreen(score);
    
    SDL_RenderPresent(renderer);
    
    // Manage framerate
    timeElapsed = SDL_GetTicks() - lastTime; // In ms
    timeToWait = waitTime - timeElapsed;
    
    if(timeToWait > 0){
      SDL_Delay(timeToWait);
    }
  }
  
  destroySDL();
}

void Game::setupSDL() {
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    GraphicLog("Error during initalization");
  }
  
  window = SDL_CreateWindow("Cactus Dodger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWindowWidth, gameWindowHeight, SDL_WINDOW_SHOWN);
  
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  loadTextures();
  
  for(int i(0); i<scoreDigitsNumber; i++) {
    SDL_Rect new_rect;
    new_rect.x = 10 + 40 * i;
    new_rect.y = 10;
    new_rect.w = 30;
    new_rect.h = 50;
    digitsRect.push_back(new_rect);
  }
  
}

void Game::loadTextures() {
  playerTexture = IMG_LoadTexture(renderer, "Textures/Player/player-square.png");
  if(playerTexture == NULL) {
    SDL_Log("Problem loading player texture : %s", IMG_GetError());
  }
  cactusTexture = IMG_LoadTexture(renderer, "Textures/Obstacles/cactus.png");
  if(cactusTexture == NULL) {
    SDL_Log("Problem loading cactus texture : %s", IMG_GetError());
  }
  fireCactusTexture = IMG_LoadTexture(renderer, "Textures/Obstacles/fire-cactus.png");
  if(fireCactusTexture == NULL) {
    SDL_Log("Problem loading fire cactus texture : %s", IMG_GetError());
  }
  backgroundTexture = IMG_LoadTexture(renderer, "Textures/Background/background.png");
  if(backgroundTexture == NULL) {
    SDL_Log("Problem loading background texture : %s", IMG_GetError());
  }

  m_player.setTexture(playerTexture);
  background.setTexture(backgroundTexture);
  
  char string[22];
  
  for(int i(0); i<10; i++) {
    sprintf(string, "Textures/Digits/%d.png", i);
    digitsTextures[i] = IMG_LoadTexture(renderer, string);
    if(digitsTextures[i] == NULL) {
      SDL_Log("Problem loading texture of number %d : %s", i, IMG_GetError());
    }
  }
}

void Game::destroySDL() {
  if(SDL_RenderClear(renderer) != 0){
    GraphicLog("Problème en nettoyant le renderer");
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::handleInput() {
  while(SDL_PollEvent( &event )) {
    if(event.type == SDL_QUIT) {
      quit = true;
    }
    
    switch(event.type) {
      
      
      case SDL_KEYDOWN:
        if(event.key.repeat == 0) {
          switch(event.key.keysym.sym) {
            
            case SDLK_SPACE:
              spaceBarPressed = true;
              
            default:
              break;
          }
        }
        break;
        
      case SDL_KEYUP:
        if(event.key.repeat == 0) {
          switch(event.key.keysym.sym) {
              
            default:
              break;
          }
        }
        break;
      
      default:
        break;
    }
  }
}

void Game::checkForPlayerCollision() {
  for(int index(0); index < barriers.size(); index++) {
    if(m_player.doesCollide(*barriers[index])){
      collisionWithBarrier();
    }
  }
}

void Game::moveBarriersAndRemoveIfNeeded() {
  
  float playerSide = m_player.getX() - m_player.getWidth()/2 - 10; // 10 to make sure barrier won't collide
  
  for(int index(0); index < barriers.size(); index++) {
    
    barriers[index]->move();
    
    // The barrier has passed the player and has not be accounted to the score yet
    if(barriers[index]->hasPassed(playerSide) && !barriers[index]->getPassed()) {
      barriers[index]->setPassed(true);
      score += barriers[index]->getScoreValue();
    }
    
    if(barriers[index]->isVisible(gameWindowWidth)){
      barriers[index]->draw(renderer);
    } else if(barriers[index]->hasPassed(playerSide)){
      delete barriers[index];
      barriers.erase(barriers.begin() + index);
    }
    
    
  }
}

void Game::drawNumberOnScreen(int number) {
  
  int numberString[scoreDigitsNumber];
  char buffer[128];
  std::string numberAsString;
  int padding;
  
  padding = scoreDigitsNumber - (number > 0 ? std::floor(std::log10(number)) + 1 : 0);
  
  numberAsString = std::to_string(number);
  strcpy(buffer, numberAsString.c_str());
  
  for(int i(0); i<padding; i++){ // Add the useless 0s
    numberString[i] = 0;
  }
  for(int i(padding); i<scoreDigitsNumber; i++){ // Turn character into int
    numberString[i] = buffer[i-padding] - 48;
  }
  for(int i(0); i<scoreDigitsNumber; i++){ // Display the digits
    SDL_RenderCopy(renderer, digitsTextures[numberString[i]], NULL, &digitsRect[i]);
  }
}

void Game::spawnBarrier() {
  if(lastBarrierSpawned >= 2 * gameFrameRate) { // Seems alright
    if(rand() % 20 < 1){
      
      int height = 0;
      int width = 0;
      int scoreVal = 1;
      SDL_Texture* barrierTexture = NULL;
    
      int val = (score > 0 ? (int)(10 / (std::floor(std::log10(score)) + 1)): 100000);
      if(rand() % val < 1 ) { // Change 10 to 50
        height = randInt(325/2, 450/2);
        width = randInt(250/3, 350/2);
        scoreVal = 5;
        lastBarrierSpawned = -30; // To give more time after a double obstacle
        barrierTexture = fireCactusTexture;
      } else {
        // Then generate a random barrier with ratio of 1 for
        height = randInt(200/3, 325/2);
        width = randInt(200/3, 250/2);
        lastBarrierSpawned = 0;
        barrierTexture = cactusTexture;
      }
      Barrier* new_barrier = new Barrier(gameWindowWidth+width, gameWindowHeight - height/2 - FLOOR_HEIGHT, width, height, gameBarriersSpeed, scoreVal, gameFrameRate);
      new_barrier->setTexture(barrierTexture);
      barriers.push_back(new_barrier);
    }
  }
  lastBarrierSpawned++;
}

void Game::GraphicLog(const char *errorString) {
  SDL_Log("LOG : %s %s\n", errorString, SDL_GetError());
  // exit(EXIT_FAILURE);
}

void Game::collisionWithBarrier() {
  score = 0;
}

int Game::setDrawColor(SDL_Renderer *renderer, Color color) {
  return SDL_SetRenderDrawColor(renderer,color.getRed() ,color.getGreen() ,color.getBlue() , color.getAlpha());
}

int Game::randInt(int a = 0, int b = 1) {
  if(b <= a) {
    return 0;
  }
  int result =  a + rand() % (b - a);
  return result;
}
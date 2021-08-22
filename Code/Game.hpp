/**
 * The file containg the Game class declaration
 * @file Game.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SDL2/SDL.h>

#include "Sprite.hpp"
#include "Player.hpp"
#include "Barrier.hpp"
#include "Color.hpp"

/** The Game class that manages everything */
class Game {
  
  private:
  
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* playerTexture;
    SDL_Texture* cactusTexture;
    SDL_Texture* fireCactusTexture;
    SDL_Texture* backgroundTexture;
    SDL_Event event;
    
    SDL_Texture* digitsTextures[10];
    std::vector<SDL_Rect> digitsRect;
    
    Color backgroundColor;
    Color playerColor;
    
    Sprite background;

    Player m_player;
    
    std::vector<Barrier *> barriers;
    
    bool quit;
    bool spaceBarPressed;
    bool shiftPressed;
    
    int lastTime;
    int timeElapsed;
    int timeToWait;
    int lastBarrierSpawned; // Time in ticks
    int score;
    int jumpsSinceFloor;
    int maxJumps;
    int gameWindowWidth;
    int gameWindowHeight;
    int gameFrameRate;
    int waitTime;
    int scoreDigitsNumber;
    int gameBarriersSpeed;
  
  public:
    Game(int windowWidth = 0, int windowHeight = 0, int frameRate = 30, float constant_g = 9.81, int numberOfScoreDigits = 6, int barriersSpeed = 225);
    
    void start();
    
    void setupSDL();

    void loadTextures();
    
    void destroySDL();
    
    void checkForPlayerCollision();
    
    void moveBarriersAndRemoveIfNeeded();
    
    void drawNumberOnScreen(int number);
    
    void spawnBarrier();
    
    void GraphicLog(const char *errorString);
    
    void collisionWithBarrier();

    int setDrawColor(SDL_Renderer *renderer, Color color);
    
    int randInt(int a, int b);

    // Input functions

    void recordInput();

    void handleInput();

    void spaceBarFunction();

    void shiftFunction();
  
};

#endif // GAME_H
/**
 * The file containg the Player class declaration
 * @file Player.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.hpp"

/** The class representing the player's sprite */
class Player : public Sprite {
  
  public:
    Player(float x = 0, float y = 0, int width = 0, int height = 0, int frameRate = 30, float constant_g = 9.81);
    float getWeight() const;
    float getSpeedY() const;
    void applyGravity();
    void setSpeedUp(float force);
    void jump(float force);
    void applySpeed();
    bool isOnTheFloor();
  
  private:
    float m_minY;
    int m_mass;
    float m_weightForce;
    float m_speedY;
    float m_speedX;
    int gameFrameRate;
    float gameConstant_g;
  
};

#endif // PLAYER_H
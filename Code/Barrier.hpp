/**
 * The file containg the Barrier class declaration
 * @file Barrier.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef BARRIER_H
#define BARRIER_H

#include "Sprite.hpp"

/** The class for the Obstacles */
class Barrier : public Sprite {
  
  private:
    
    float m_speed;
    bool m_passed;
    int m_scoreValue;
    int gameFrameRate;
  
  public:
    Barrier(float x = 0, float y = 0, int width = 0, int height = 0, float speed = 0, int scoreValue = 0, int frameRate = 30);
    
    bool getPassed() const;
    bool isVisible(int windowWdith) const;
    bool hasPassed(int coordinate) const;
    void setPassed(bool value);
    int getScoreValue() const;
    void move();
  
};

#endif // BARRIER_H
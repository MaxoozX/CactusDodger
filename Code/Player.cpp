/**
 * The file containg the Player class implementation
 * @file Player.cpp
 * @author Maxence
 * @version 1.0
*/

#include "Sprite.hpp"
#include "Player.hpp"

Player::Player(float x, float y, int width, int height, int frameRate, float constant_g): Sprite(x, y, width, height), m_minY(y), m_mass(30), m_speedY(0), m_speedX(0), gameFrameRate(frameRate), gameConstant_g(constant_g) {
  m_weightForce = constant_g * m_mass;
  updateRect();
}

float Player::getWeight() const { return m_weightForce; }
float Player::getSpeedY() const { return m_speedY; }

void Player::applyGravity() {
  if(!isOnTheFloor()) { // If the player doesn't touch the floor
    double acceleration = m_weightForce / gameFrameRate;
    m_speedY += acceleration;
  }
}

void Player::setSpeedUp(float force) {
  m_speedY = -(force / m_mass);
}

void Player::jump(float force) {
  setSpeedUp(force);
}

void Player::applySpeed() {
  if(m_speedY != 0 || m_y != m_minY) {
  }
  
  m_y += m_speedY / gameFrameRate;
  if(isOnTheFloor()) {
    m_y = m_minY;
    m_speedY = 0;
  }
  
}

bool Player::isOnTheFloor() {
  return (m_y >= m_minY);
}
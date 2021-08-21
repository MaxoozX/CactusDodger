/**
 * The file containg the Barrier class implementation
 * @file Barrier.cpp
 * @author Maxence
 * @version 1.0
*/

#include "Barrier.hpp"

Barrier::Barrier(float x, float y, int width, int height, float speed, int scoreValue, int frameRate): Sprite(x, y, width, height), m_speed(speed), m_passed(false), m_scoreValue(scoreValue), gameFrameRate(frameRate) {}

bool Barrier::getPassed() const { return m_passed; }
void Barrier::setPassed(bool value) { m_passed = value; }
int Barrier::getScoreValue() const { return m_scoreValue; }

void Barrier::move() {
  m_x -= m_speed / gameFrameRate;
  updateRect();
}

bool Barrier::isVisible(int windowWdith) const {
  return ((0 - m_width/2) < m_x && m_x < (windowWdith + m_width/2));
}

bool Barrier::hasPassed(int coordinate) const {
  return (m_x + m_width/2 < coordinate);
}
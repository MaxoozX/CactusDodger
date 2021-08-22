/**
 * The file containg the Sprite class implementation
 * @file Sprite.cpp
 * @author Maxence
 * @version 1.0
*/

#include <SDL2/SDL.h>

#include "Sprite.hpp"

Sprite::Sprite(float x, float y, float width, float height): m_x(x), m_y(y), m_width(width), m_height(height), m_texture(NULL) {
  updateRect();
}

float Sprite::getX() const { return m_x; }
float Sprite::getY() const { return m_y; }
int Sprite::getWidth() const { return m_width; }
int Sprite::getHeight() const { return m_height; }

const SDL_Rect* Sprite::getPointerToRect() const { return &m_rect; }
SDL_Texture* Sprite::getPointerToTexture() const { return m_texture; }

void Sprite::setX(float x) { m_x = x; }
void Sprite::setY(float y) { m_y = y; }
void Sprite::setWidth(int width) { m_width = width; }
void Sprite::setHeight(int height) { m_height = height; }

void Sprite::setTexture(SDL_Texture* texture) {
  m_texture = texture;
}

void Sprite::updateRect() {
  m_rect.x = m_x - m_width / 2;
  m_rect.y = m_y - m_height / 2;
  m_rect.w = m_width;
  m_rect.h = m_height;
}

bool Sprite::doesCollide(const Sprite &other) const {
  
  float leftA, leftB;
  float rightA, rightB;
  float topA, topB;
  float bottomA, bottomB;
  
  leftA = m_x;
  rightA = m_x + m_width;
  topA = m_y;
  bottomA = m_y + m_height;
  
  leftB = other.m_x;
  rightB = other.m_x + other.m_width;
  topB = other.m_y;
  bottomB = other.m_y + other.m_height;
  
  return (!(
      ( bottomA < topB )
      || ( topA > bottomB )
      || ( rightA < leftB )
      || ( leftA > rightB )
    ));
  
}

void Sprite::draw(SDL_Renderer* renderer) const {
  SDL_RenderCopy(renderer, getPointerToTexture(), NULL, getPointerToRect());
}
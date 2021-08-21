/**
 * The file containg the Sprite class declaration
 * @file Sprite.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

/** The class representing a graphical object, with coordinates, dimensions, a rect and a texture */
class Sprite {
  
  public:
    Sprite(float x = 0, float y = 0, float width = 0, float height = 0);
    float getX() const;
    float getY() const;
    int getWidth() const;
    int getHeight() const;
    const SDL_Rect* getPointerToRect() const;
    SDL_Texture* getPointerToTexture() const;
    void setX(float x);
    void setY(float y);
    void setWidth(int width);
    void setHeight(int height);
    void setTexture(SDL_Texture* texture);
    void updateRect();
    /** If the other object's rect is in contact with the object's rect */
    bool doesCollide(const Sprite &other) const;
    void draw(SDL_Renderer* renderer) const;
    
  protected:
    float m_x;
    float m_y;
    int m_width;
    int m_height;
    SDL_Rect m_rect;
    SDL_Texture* m_texture;
  
};

#endif // SPRITE_H
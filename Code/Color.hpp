/**
 * The file containg the Color class declaration
 * @file Color.hpp
 * @author Maxence
 * @version 1.0
*/

#ifndef COLOR_H
#define COLOR_H

/** A simple class for RGBA color */
class Color {
  
  private:
    const int m_red;
    const int m_green;
    const int m_blue;
    const float m_alpha;
  
  public:
    Color(int red = 0, int green = 0, int blue = 0, float alpha = 1.0);
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    int getAlpha() const;
  
};

#endif // COLOR_H
#ifndef __DEF_MENU__
#define __DEF_MENU__

#include <SFML/Graphics.hpp>

class Menu
{
 public:
  static Menu* Instance();
  void draw();
  void dispatch(unsigned const int type);
  void setState(int state);
  
 private:
  Menu();
  int state; //0, 1
  int currentButton; //0, 1

  sf::Image background;
  sf::Image button[2];
  sf::IntRect rect[2];
};

#endif

#ifndef DEF_GAME
#define DEF_GAME

#include "../resources/Conf.h"
#include "../resources/Notifications.h"
#include "../scene/World.h"
#include "../tool/LuaInter.h"
#include "../scene/Camera.h"

#include <SFML/System/Randomizer.hpp>
#include <iostream>

class Game
{
 public:

  static Game* Instance();

  void init();
  void draw();
  void update(float time);
  void onEvent(sf::Event *event);
  void setMousePosition(unsigned int x, unsigned int y);
  void setGameState(int state);


 private:
  Game();
  World world;

  float windowScale;
  float windowPaddingLeft;
  float windowPaddingTop;

  int gameState; //1 open menu,  2 playing game,  3 result
};

#endif


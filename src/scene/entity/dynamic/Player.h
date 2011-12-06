#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../Dynamic.h"
#include "../../../resources/Conf.h"
#include <SFML/System/Clock.hpp>

#include <iostream>

class Player : public Dynamic
{
 public:

  Player(float x, float z, float s);
  virtual void update(float time);
  virtual void onNotify(unsigned const int type);
  virtual int echo();
};

#endif


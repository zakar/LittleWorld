#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "../Dynamic.h"
#include "../../World.h"

#include <SFML/System/Randomizer.hpp>
#include <iostream>

class Enemy : public Dynamic
{
 public:

  Enemy(float x, float z, float s);

  virtual void update(float time);

  virtual int echo();
  virtual int getID();

 private:
   int zero_move , last_move_x , last_move_z , id;
};

#endif


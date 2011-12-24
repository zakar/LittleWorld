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

  static int tot;
  static void clear() { tot = 0; }

 private:
   int circle_move , id , zero_move , last_x , last_z;
   float last_move_x , last_move_z;
};

#endif


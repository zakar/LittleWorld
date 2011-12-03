#ifndef DEF_ENTITY
#define DEF_ENTITY

#include "../math/Vector3.h"
#include "../tool/LuaInter.h"

#include <iostream>

class Entity
{
 public:

  Entity(float s);

  float getX();
  float getY();
  float getZ();

  float getSize();
  Vector3 getPosition();

  void setLightned(bool v);
  bool isVisible();

 public:
  //data that object need
  int texid;
  float tex[4][2];

 protected:
  float size;
  Vector3 position;
  
 private:
  bool visible;
  bool lightned;
};

#endif


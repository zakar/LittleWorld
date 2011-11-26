#ifndef DEF_ENTITY
#define DEF_ENTITY

#include "../math/Vector3.h"

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

 protected:
  float size;
  Vector3 position;

 private:
  bool visible;
  bool lightned;
};

#endif


#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "../math/Vector3.h"
#include "../scene/Entity.h"
#include <SFML/Graphics.hpp>

#include <iostream>

class Object
{
 public:

  Object(Entity *e);

  virtual void draw();
  virtual void outline();

  void setVisibility(bool v);

  float getX();
  float getY();
  float getZ();
  float getSize();

  Vector3 getPosition();

  bool isVisible();

  static void genTex2D(const char *file, GLuint *texid, GLsizei width, GLsizei height );

 protected:

  Entity *entity;

  bool visible;
};

#endif


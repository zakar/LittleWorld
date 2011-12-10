#ifndef DEF_SPRITE
#define DEF_SPRITE

#include "../Object.h"
#include "../../resources/Structs.h"
#include "../../resources/Conf.h"

#include <iostream>
#include <SFML/Graphics.hpp>

// TODO Have an instance of obj instead of the struct and the long constructor

class Sprite : public Object
{
 public:

  Sprite(Entity *e);
  virtual ~Sprite();

  virtual void draw();
  virtual void outline();

  void setData(float *RGBA, int totalVertex, float *vertex, float *normal);
  void getTexFromEntity(void);

 private:

  unsigned int totalVertex;
  unsigned int totalIndexes;

  Vertex vertices[4];
  GLubyte indexes[4];
};

#endif


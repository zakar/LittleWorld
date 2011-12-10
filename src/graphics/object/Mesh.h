#ifndef DEF_MESH
#define DEF_MESH

#include "Light.h"
#include "../Object.h"
#include "../../resources/Structs.h"
#include "../../resources/Conf.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Mesh : public Object
{
 public:

  Mesh(Entity *e);
  virtual ~Mesh();

  virtual void draw();
  virtual void outline();

  void setData(float size, float height, float *RGBA);

  void drawShadow(Light *pLight);

 private:

  void updatePlaneEquations();
  void updateConnectivity();

  unsigned int totalVertex;
  unsigned int totalTriangles;
  unsigned int totalIndexes;

  Vertex vertices[24];
  Triangle triangles[12];
  GLubyte indexes[36];
};

#endif



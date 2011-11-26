#ifndef DEF_MANAGER
#define DEF_MANAGER

#include "../resources/Conf.h"
#include "../math/Vector3.h"
#include <iostream>

class Manager
{
 public:
  static Manager* Instance();
  
  void updateGrid(const Vector3 &position, float s, int type);
  void updatePath(const Vector3 &position);
  bool checkHit(const Vector3 &position, float s);
  void fetchSpeed(const Vector3 &position, Vector3 &speed);

 private:
  const static int w[9][2];
  void calRange(int &x0, int &y0, int &x1, int &y1, const Vector3 &position, float s);
  void calPosition(int &x, int &y, const Vector3 &position);

  Manager();
  int grid[GRID_WIDTH][GRID_HEIGHT];
  int path[GRID_WIDTH][GRID_HEIGHT];
};

#endif

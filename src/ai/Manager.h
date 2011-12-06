#ifndef DEF_MANAGER
#define DEF_MANAGER

#include "../resources/Conf.h"
#include "../math/Vector3.h"
#include "Match.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

class Manager
{
 public:
  static Manager* Instance();
  
  void updateGrid(const Vector3 &position, float s, int type);
  bool updatePath(const Vector3 &position, const float &size);
  bool checkHit(const Vector3 &position, float s);
  void fetchSpeed(const Vector3 &position, Vector3 &speed, const int &flag);

  bool check( const Vector3 &position , const float &size ); 
  void collect( const int &flag , const Vector3 &position );
  void updatePos( const int &flag , const Vector3 &poosition );
  void attack();

  void solve();
  void clearMatch();

 private:
  const static int w[9][2];
  void calRange(int &x0, int &y0, int &x1, int &y1, const Vector3 &position, float s);
  void calPosition(int &x, int &y, const Vector3 &position);
  void makeCircle( const Vector3 &position , const float &size );
  void findPath( const int &flag );

  Manager();
  int circle_pos[MAX_PT+1][2];
  int grid[GRID_WIDTH][GRID_HEIGHT];
  int path[MAX_PT+1][GRID_WIDTH][GRID_HEIGHT];
  int dis[MAX_PT+1][GRID_WIDTH][GRID_HEIGHT];
  int list[MAX_EMY];
  int reach[MAX_PT];
  int update_tot;
  int xlen , ylen;
};

#endif

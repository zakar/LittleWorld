#include "Manager.h"
#include <cstring>

using namespace std;

const int Manager::w[9][2] = { {0,0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1,1}, {-1,-1}, {1,-1}, {-1,1} };

Manager::Manager() 
{
  memset(path, 0, (sizeof path));
  memset(grid, 0, (sizeof grid));
}

Manager* Manager::Instance()
{
  static Manager* ins = new Manager;
  return ins;
}
  
void Manager::updateGrid(const Vector3 &position, float s, int type)
{
  int x0, y0, x1, y1;
  calRange(x0, y0, x1, y1, position, s);
  for (int i = x0; i < x1; ++i)
    for (int j = y0; j < y1; ++j) grid[i][j] = type;
}

void Manager::updatePath(const Vector3 &position)
{
  static int col = 0;
  static int vis[GRID_WIDTH][GRID_HEIGHT] = {0};
  static int que[GRID_WIDTH*GRID_HEIGHT];
  int st = 0, ed = 1;

  int sx, sy;
  calPosition(sx, sy, position);
  que[st] = sx * GRID_HEIGHT + sy;

  memset(path, 0x0, (sizeof path));
  col ^= 1;
  for (int x, y; st < ed; ++st) {
    x = que[st]/GRID_HEIGHT;
    y = que[st]%GRID_HEIGHT;
    
    for (int xx, yy, l = 1; l < 9; ++l) {
      xx = x + w[l][0];
      yy = y + w[l][1];
      if (0 <= xx && xx < GRID_WIDTH && 0 <= yy && yy < GRID_HEIGHT && !grid[xx][yy] && vis[xx][yy] != col) {
	vis[xx][yy] = col;
	path[xx][yy] = ((l-1)^1)+1;
	que[ed++] = xx * GRID_HEIGHT + yy;
      }
    }
  }
}

bool Manager::checkHit(const Vector3 &position, float s)
{
  int x0, y0, x1, y1;
  calRange(x0, y0, x1, y1, position, s);
  if (x0 < 0 || x1 >= GRID_WIDTH || y0 < 0 || y1 >= GRID_HEIGHT) return 0;

  for (int i = x0; i < x1; ++i)
    for (int j = y0; j < y1; ++j) 
      if (grid[i][j]) return 1;

  return 0;
}

void Manager::fetchSpeed(const Vector3 &position, Vector3 &speed)
{
  int x, y;
  calPosition(x, y, position);

  int idx = path[x][y];

  speed.x = w[idx][0] * 100.0;
  speed.z = w[idx][1] * 100.0;
  speed.y = 0.0;
}

void Manager::calPosition(int &x, int &y, const Vector3 &position)
{
  x = (int)(position.x / GRID_UNIT);
  y = (int)(position.z / GRID_UNIT);
}

void Manager::calRange(int &x0, int &y0, int &x1, int &y1, const Vector3 &position, float s)
{
  s /= 2.0;
  x0 = (int)((position.x - s) / GRID_UNIT);
  x1 = (int)((position.x + s) / GRID_UNIT) + 1;
  y0 = (int)((position.z - s) / GRID_UNIT);
  y1 = (int)((position.z + s) / GRID_UNIT) + 1;
}


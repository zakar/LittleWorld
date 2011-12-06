#include "Manager.h"
#include <cstring>
#include <cstdio>

using namespace std;

const int Manager::w[9][2] = { {0,0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1,1}, {-1,-1}, {1,-1}, {-1,1} };

Manager::Manager() 
{
  memset(path, 0, (sizeof path));
  memset(grid, 0, (sizeof grid));
  update_tot = xlen = ylen = 0;
  memset( circle_pos , 0 , sizeof(circle_pos) );
  memset( reach , 0 , sizeof(reach) );
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

bool Manager::check( const Vector3 &position , const float &size )
{
	int lx = GRID_WIDTH , ly = GRID_HEIGHT , ux = 0 , uy = 0;
	for ( int i = 0; i < 8; i++ ) {
		lx = circle_pos[i][0] < lx ? circle_pos[i][0] : lx;
		ly = circle_pos[i][1] < ly ? circle_pos[i][1] : ly;
		ux = circle_pos[i][0] > ux ? circle_pos[i][0] : ux;
		uy = circle_pos[i][1] > uy ? circle_pos[i][1] : uy;
	}
	int sx , sy;
	calPosition(sx,sy,position);
	lx += 2*(size/GRID_UNIT);
	ly += 2*(size/GRID_UNIT);
	ux -= 2*(size/GRID_UNIT);
	uy -= 2*(size/GRID_UNIT);
	return ( lx < sx && sx < ux && ly < sy && sy < uy );
}

void Manager::makeCircle( const Vector3 &position , const float &size ) 
{
	int xx , yy , sx , sy , h = 0;
	calPosition(xx,yy,position);
	for ( int i = -1; i <= 1; i++ ) {
		for ( int j = -1; j <= 1; j++ ) {
			if ( !i && !j ) continue;
			Vector3 tmp(position);
			tmp.x -= i*size*3;
			tmp.z -= j*size*3;
			calPosition(sx,sy,tmp);
			sx = sx < 0 ? 0 : ( sx > GRID_WIDTH ? GRID_WIDTH : sx );
			sy = sy < 0 ? 0 : ( sy > GRID_HEIGHT ? GRID_HEIGHT : sy );
			circle_pos[h][0] = sx;
			circle_pos[h++][1] = sy;
			xlen = xlen > abs(xx-sx) ? xlen : abs(xx-sx);
			ylen = ylen > abs(yy-sy) ? ylen : abs(yy-sy);
		}
	}
	memset( reach , 0 , sizeof(reach) );
	circle_pos[MAX_PT][0] = xx;
	circle_pos[MAX_PT][1] = yy;
}

void Manager::attack()
{
	int flag = 0;
	for ( int i = 0; i < MAX_PT; i++ ) flag += reach[i];
	printf( "%d\n" , flag );
	if ( flag >= 4 ) {
		findPath(MAX_PT);
		for ( int i = 0; i < MAX_EMY; i++ ) {
			if ( list[i] != -1 ) list[i] = 8;
		}
	}
}

void Manager::findPath( const int &flag ) 
{
	static int que[GRID_WIDTH*GRID_HEIGHT];
	static int vis[GRID_WIDTH][GRID_HEIGHT];
	static int col = 0;
	int sx = circle_pos[flag][0] , sy = circle_pos[flag][1];
	int hd = 0 , tl = 0;
	col = 9-flag;
	que[tl++] = sx * GRID_HEIGHT + sy;
	vis[sx][sy] = col;
	dis[flag][sx][sy] = 0;
	while ( hd < tl && tl < MAX_STEPS ) {
		int x = que[hd]/GRID_HEIGHT , y = que[hd++]%GRID_HEIGHT;
		for ( int l = 1; l < 9 && tl < MAX_STEPS; l++ ) {
			int xx = x + w[l][0] , yy = y + w[l][1];
			if ( flag == 8 && ( abs(xx-sx) >= xlen && abs(yy-sy) >= ylen ) ) continue;
			if ( 0 <= xx && xx < GRID_WIDTH && 0 <= yy && y < GRID_HEIGHT && grid[xx][yy] != 2 && vis[xx][yy] != col ) {
				if ( grid[xx][yy] == 3 && flag < MAX_PT ) continue;
				vis[xx][yy] = col;
				path[flag][xx][yy] = ((l-1)^1)+1;
				dis[flag][xx][yy] = dis[flag][x][y] + 1;
				que[tl++] = xx * GRID_HEIGHT + yy;
			}
		}
	}
}

bool Manager::updatePath( const Vector3 &position , const float &size )
{
/*
  static int col = 0;
  static int vis[GRID_WIDTH][GRID_HEIGHT] = {0};
  static int que[GRID_WIDTH*GRID_HEIGHT];
  int sx, sy;
  for ( int flag = 0; flag < 8; flag++ ) {
	int st = 0 , ed = 1;
	Vector3 tmp(position);
  	tmp.x += dirt[flag][0] * size;
	tmp.z += dirt[flag][1] * size;
	calPosition(sx,sy,tmp);
	que[st] = sx * GRID_HEIGHT + sy;
	if ( update_tot > 10 ) {
	  	memset(path, 0x0, (sizeof path));
		memset(dis,-1,sizeof(dis));
		update_tot = 0;
	} else update_tot++;
	col ^= 1;
	dis[flag][sx][sy] = 0;
  	for (int x, y; st < ed && ed < MAX_STEPS; ++st) {
    	x = que[st]/GRID_HEIGHT;
    	y = que[st]%GRID_HEIGHT;
    	for (int xx, yy, l = 1; l < 9 && ed < MAX_STEPS; ++l) {
      		xx = x + w[l][0];
      		yy = y + w[l][1];
      		if (0 <= xx && xx < GRID_WIDTH && 0 <= yy && yy < GRID_HEIGHT && grid[xx][yy] != 2 && vis[xx][yy] != col) {
				vis[xx][yy] = col;
				path[flag][xx][yy] = ((l-1)^1)+1;
				dis[flag][xx][yy] = dis[flag][x][y] + 1;
				que[ed++] = xx * GRID_HEIGHT + yy;
      		}
    	}
  	}	
  }
  */
  memset( dis , 0 , sizeof(dis) );
  memset( path , 0 , sizeof(path) );
//  if ( !check(position,size) ) {
  	makeCircle(position,size);
  	for ( int i = 0; i < MAX_PT; i++ ) findPath(i);
//	return true;
//  }
  return false;
}

void Manager::collect( const int &flag , const Vector3 &position ) 
{
	int sx , sy , j , k , f = 0;
	calPosition(sx,sy,position);
	for ( int i = 0; i < MAX_PT; i++ ) {
		Match::Instance(MAX_PT,MAX_EMY)->addEdge(i,flag,dis[i][sx][sy]);
	}
}

void Manager::solve()
{
	int ans[MAX_PT];
	memset( ans , -1 , sizeof(ans) );
	Match::Instance(MAX_PT,MAX_EMY)->solve(ans);
	memset( list , -1 , sizeof(list) );
	for ( int i = 0; i < MAX_PT; i++ ) {
		if ( ans[i] == -1 ) continue;
		list[ans[i]] = i;
	}
}

void Manager::clearMatch()
{
	Match::Instance(MAX_PT,MAX_EMY)->clear();
}

bool Manager::checkHit(const Vector3 &position, float s)
{
  int x0, y0, x1, y1;
  calRange(x0, y0, x1, y1, position, s);
  if (x0 < 0 || x1 >= GRID_WIDTH || y0 < 0 || y1 >= GRID_HEIGHT) return 1;

  for (int i = x0; i < x1; ++i)
    for (int j = y0; j < y1; ++j) 
      if (grid[i][j]==2||grid[i][j]==1) return 1;

  return 0;
}

void Manager::updatePos( const int &flag , const Vector3 &position )
{
	if ( flag == -1 ) {
		int sx , sy;
		calPosition(sx,sy,position);
		circle_pos[MAX_PT][0] = sx;
		circle_pos[MAX_PT][1] = sy;
		return;
	}
	int d = list[flag];
	if ( d != -1 ) {
		int sx , sy;
		calPosition(sx,sy,position);
		if ( abs(circle_pos[d][0]-sx) < 20 && abs(circle_pos[d][1]-sy) < 20 ) {
			reach[d] = 1;
		}
	}
}

void Manager::fetchSpeed( const Vector3 &position , Vector3 &speed , const int &flag )
{
/*  int x , y , p1 = -1 , p2 = -1 , p3 = -1 , p4 = -1;
  calPosition(x, y, position);

  for ( int i = 0; i < 8; i++ ) {
    if ( dis[i][x][y] == -1 ) continue;
  	if ( p1 == -1 || dis[i][x][y] < dis[p1][x][y] ) p1 = i;
	else if ( p2 == -1 || dis[i][x][y] < dis[p2][x][y] ) p2 = i;
	else if ( p3 == -1 || dis[i][x][y] < dis[p3][x][y] ) p3 = i;
	else if ( p4 == -1 || dis[i][x][y] < dis[p4][x][y] ) p4 = i;
  }
  int t = rand()%4 , p = t == 0 ? p1 : ( t == 1 ? p2 : ( t == 2 ? p3 : p4 ) );
  int idx = path[p][x][y];
  speed.x = w[idx][0] * 100.0;
  speed.z = w[idx][1] * 100.0;*/
  int x , y , d = list[flag];
  calPosition(x,y,position);
  if ( d != -1 ) {
		int idx = path[d][x][y];
		speed.x = w[idx][0] * 100.0;
		speed.z = w[idx][1] * 100.0;
  } else {
		speed.x = speed.z = 0;
  }
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


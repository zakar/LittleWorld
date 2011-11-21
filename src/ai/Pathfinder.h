#ifndef PATHFINDER
#define PATHFINDER

#include "../resources/Conf.h"
#include "../resources/Structs.h"
#include "../scene/Entity.h"
#include "../math/Vector3.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        void registerEntity(Entity *entity);

        std::vector<Vector3*> getPath(float fromX, float fromY, float toX, float toY, float s);


    private:

        Tile grid[GRID_HEIGHT][GRID_WIDTH];

        int getGScore(Tile *t1, Tile *t2);
        int getHScore(Tile *t1, Tile *t2);

        void computeScores(Tile *t1, Tile *t2);

        bool isEmpty(float x, float y, float s);
        bool isPathWalkable(float x1, float y1, float x2, float y2, float s);

        std::vector<Vector3*> aStar(float x1, float y1, float x2, float y2, float s);
        std::list<Tile*> getTraversingTiles(float x1, float y1, float x2, float y2, float s);

        int toGrid(float i);
        int toGrid(float i, float s);
	void occupyRange(int &x0, int &y0, int &x1, int &y1, float x, float y, float s);
	bool inRange(int x0, int y0, int x1, int y1);
};

inline int Pathfinder::toGrid(float i)
{
    return std::floor(i / GRID_UNIT);
}

inline int Pathfinder::toGrid(float i, float s)
{
    return std::floor((i - std::fmod(i, s)) / GRID_UNIT);
}

inline void Pathfinder::occupyRange(int &x0, int &y0, int &x1, int &y1, float x, float y, float s)
{
  x0 = toGrid(x - s / 2.f);
  x1 = toGrid(x + s / 2.f) + (std::fmod(x+s/2.f, GRID_UNIT) > 0.f);
  y0 = toGrid(y - s / 2.f);
  y1 = toGrid(y + s / 2.f) + (std::fmod(y+s/2.f, GRID_UNIT) > 0.f);
}

inline bool Pathfinder::inRange(int x0, int y0, int x1, int y1)
{
  return 0 <= x0 && x1 < GRID_WIDTH && 0 <= y0 && y1 < GRID_HEIGHT;
}

#endif


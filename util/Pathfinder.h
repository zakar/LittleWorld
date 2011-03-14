#ifndef DEF_UTIL_PATHFINDER
#define DEF_UTIL_PATHFINDER

#include "../object/StaticObject.h"
#include "Position.h"
#include "Point.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
    public:

        Pathfinder();

        void addStaticObject(StaticObject *o);

        std::vector<Position*> getPath(float x1, float y1, float x2, float y2, float s);



    private:

        std::vector<Position*> aStar(float x1, float y1, float x2, float y2);
        std::list<Point*> getTraversingPoints(float x1, float y1, float x2, float y2);

        int getGScore(Point *p1, Point *p2);

        bool isGridOk(int x, int y);

        std::map<int, std::map<int, Point*> > grid;
};

#endif

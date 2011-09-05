#include "Object.h"

using namespace std;

Object::Object(Entity *e)
{
    entity = e;
}

void Object::draw()
{
}

void Object::outline()
{
}

float Object::getX() { return entity->getX(); }
float Object::getY() { return entity->getY(); }
float Object::getZ() { return entity->getZ(); }


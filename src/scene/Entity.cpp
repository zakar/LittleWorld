#include "Entity.h"

using namespace std;

Entity::Entity(float s) : size(s)
{
  visible  = false;
  lightned = false;
}

Entity::~Entity()
{
}

void Entity::setLightned(bool v)   { lightned = v; }

float Entity::getX()               { return position.x; }
float Entity::getY()               { return position.y; }
float Entity::getZ()               { return position.z; }
float Entity::getSize()            { return size; }

bool Entity::isVisible()           { return visible; }

Vector3 Entity::getPosition()      { return position; }

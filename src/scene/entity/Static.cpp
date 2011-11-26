#include "Static.h"

Static::Static(float s, bool b) : Entity(s)
{
  walkable = b;
}

bool Static::isCanWalk()
{
  return walkable;
}

void Static::update(float time)
{
}


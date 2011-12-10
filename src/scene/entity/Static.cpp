#include "Static.h"

Static::Static(float s, bool b) : Entity(s)
{
  walkable = b;
}

Static::~Static()
{
}

bool Static::isCanWalk()
{
  return walkable;
}

void Static::update(float time)
{
}


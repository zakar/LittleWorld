#include "Goal.h"

Goal::Goal(float x, float z, float s, bool w) : Static(s, w)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;

  LuaInter::Instance()->getGoalTex(&texid, tex);

  Manager::Instance()->updateGrid(position, s, 3);
}

Goal::~Goal()
{
}


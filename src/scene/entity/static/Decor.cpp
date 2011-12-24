#include "Decor.h"

Decor::Decor(float x, float z, float s, bool w) : Static(s, w)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;

  LuaInter::Instance()->getFloorTex(&texid, tex);

  if (!w)
    Manager::Instance()->updateGrid(position, s, 2);
}

Decor::~Decor()
{
}

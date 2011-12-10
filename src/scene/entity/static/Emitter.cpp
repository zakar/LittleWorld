#include "Emitter.h"

using namespace std;

Emitter::Emitter(float x, float y, float z) : Static(0.f, false)
{
  position.x = x;
  position.y = y;
  position.z = z;
}

Emitter::~Emitter()
{
}

#ifndef DEF_STATIC
#define DEF_STATIC

#include "../Entity.h"
#include "../../ai/Manager.h"

class Static : public Entity
{
 public:
  Static(float s, bool b);
  virtual void update(float time);

 private:
  bool walkable;
  bool isCanWalk();
};

#endif


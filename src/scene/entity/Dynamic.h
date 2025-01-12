#ifndef DEF_DYNAMIC
#define DEF_DYNAMIC

#include "../Entity.h"
#include "../../math/Vector3.h"
#include "../../math/Vector3Util.h"
#include "../../ai/Manager.h"

#include <iostream>

class World;

class Dynamic : public Entity
{
 public:

  Dynamic(float s);
  virtual ~Dynamic();

  virtual void update(float time);
  virtual void onNotify(unsigned const int type);
  virtual int getID();
  virtual int echo();

 protected:
  Vector3 speed;
};

#endif


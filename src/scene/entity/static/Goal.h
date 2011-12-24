#ifndef DEF_GOAL
#define DEF_GOAL

#include "../Static.h"

class Goal : public Static
{
 public:
  Goal(float x, float z, float s, bool w);
  virtual ~Goal();
};

#endif

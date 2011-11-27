#ifndef __LUAINTER__
#define __LUAINTER__

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

class World;
class Vector3;

class LuaInter
{
 public:
  static LuaInter *Instance();

  void init(World* w);
  void addEntity(void);

  void getPlayTexid(const Vector3 &speed, int *texid);
  void getEnemyTexid(const Vector3 &speed, int *texid);
  void getFloorTexid(int *texid);
  
 private:
  LuaInter();
  lua_State *L;
};

#endif

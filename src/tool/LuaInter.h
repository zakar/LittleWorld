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

  void getPlayTex(const Vector3 &speed, int *texid, float tex[][2]);
  void getEnemyTex(const Vector3 &speed, int *texid);
  void getFloorTex(int *texid, float tex[][2]);
  
 private:
  LuaInter();
  lua_State *L;
};

#endif

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
  void initWorld();
  void addEntity(void);

  void getPlayTex(const Vector3 &speed, int *texid, float tex[][2], bool *alpha_test);
  void getEnemyTex(const Vector3 &speed, int *texid, float tex[][2], bool *alpha_test, int id);
  void getFloorTex(int *texid, float tex[][2]);
  void getGoalTex(int *texid, float tex[][2]);
  void getBackGroundTex(int state, int *backgroundTexId);
  
 private:
  LuaInter();
  lua_State *L;
};

#endif

#ifndef __LUAINTER__
#define __LUAINTER__

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
#include "../scene/World.h"
#include <cstdio>

class LuaInter
{
 public:
  LuaInter();
  void init(World* w);
  void addEntity();
  
 private:
  lua_State *L;
};

#endif

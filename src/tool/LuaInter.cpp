#include "LuaInter.h"

static World* world;

static int addWallDecor(lua_State *L)
{
  float x, z, s;
  x = lua_tonumber(L, 1);
  z = lua_tonumber(L, 2);
  s = lua_tonumber(L, 3);
  world->addWallDecor(x, z, s);
  return 0;
}

static int addPlayer(lua_State *L)
{
  float x, z;
  bool b;
  x = lua_tonumber(L, 1);
  z = lua_tonumber(L, 2);
  b = lua_toboolean(L, 3);
  world->addPlayer(x, z, b);
  return 0;
}

static int addEnemy(lua_State *L)
{
  float x, z;
  x = lua_tonumber(L, 1);
  z = lua_tonumber(L, 2);
  world->addEnemy(x, z);
  return 0;
}

static int addFloorDecor(lua_State *L)
{
  float x, z;
  x = lua_tonumber(L, 1);
  z = lua_tonumber(L, 2);
  world->addFloorDecor(x, z);
  return 0;
}

static int addLight(lua_State *L)
{
  float x, y, z, r, g, b;
  x = lua_tonumber(L, 1);
  y = lua_tonumber(L, 2);
  z = lua_tonumber(L, 3);
  r = lua_tonumber(L, 4);
  g = lua_tonumber(L, 5);
  b = lua_tonumber(L, 6);
  world->addLight(x, y, z, r, g, b);
  return 0;
}

static const luaL_Reg worldfunc[] = {
  {"addWallDecor", addWallDecor},
  {"addLight", addLight},
  {"addFloorDecor", addFloorDecor},
  {"addPlayer", addPlayer},
  {"addEnemy", addEnemy},
  {NULL, NULL}
};

LuaInter::LuaInter()
{
}

void LuaInter::init(World* w)
{
  world = w;

  L = luaL_newstate();
  luaL_openlibs(L);
  luaL_register(L, "World", worldfunc);

  if (luaL_dofile(L, "./src/tool/config.lua"))
    lua_error(L);
}

void LuaInter::addEntity()
{
  lua_getglobal(L, "addEntity");
  if (lua_pcall(L, 0, 0, 0)) 
    lua_error(L);
  lua_settop(L, 0);
}


#include "LuaInter.h"
#include "../scene/World.h"
#include "../math/Vector3.h"
#include <cstring>
#include <assert.h>

static World* world;

static void fillTablef(lua_State *L, float *arr)
{
  int tab = lua_gettop(L);
  int len = lua_objlen(L, tab);
  for (int i = 0; i < len; ++i) {
    lua_pushinteger(L, i+1);
    lua_gettable(L, tab);
    arr[i] = lua_tonumber(L, tab+1);
    lua_settop(L, tab);
  }
  lua_settop(L, tab-1);
}

static int addTexture(lua_State *L)
{
  GLuint texid;
  GLsizei width, height;

  width = lua_tointeger(L, 2);
  height = lua_tointeger(L, 3);
  Object::genTex2D(lua_tostring(L, 1), &texid, width, height);
  lua_settop(L, 0);
  lua_pushinteger(L, texid);
  return 1;
}

static void addSprite(lua_State *L, Entity *e)
{
  float RGBA[4];
  float vertex[12];
  float normal[12];
  int totalVertex;
  lua_settop(L, 1);

  lua_getfield(L, 1, "RGBA");
  fillTablef(L, RGBA);
  lua_getfield(L, 1, "vertex");
  fillTablef(L, vertex);
  lua_getfield(L, 1, "normal");
  fillTablef(L, normal);
  lua_getfield(L, 1, "totalVertex");
  totalVertex = lua_tointeger(L, lua_gettop(L));
  
  world->addSprite(e, RGBA, totalVertex, vertex, normal);
}

static void addMesh(lua_State *L, Entity *e)
{
  float RGBA[4];
  float size, height;
  lua_getfield(L, 1, "RGBA");
  fillTablef(L, RGBA);
  lua_getfield(L, 1, "size");
  size = lua_tonumber(L, lua_gettop(L));
  lua_getfield(L, 1, "height");
  height = lua_tonumber(L, lua_gettop(L));

  world->addMesh(e, size, height, RGBA);
}

static int addEntity(lua_State *L)
{
  float x, z, s;
  char entity[8], object[8];
  lua_getfield(L, 1, "x");
  x = lua_tonumber(L, 2);
  lua_getfield(L, 1, "z");
  z = lua_tonumber(L, 3);
  lua_getfield(L, 1, "s");
  s = lua_tonumber(L, 4);
  lua_getfield(L, 1, "Entity");
  strcpy(entity, lua_tostring(L, 5));
  lua_getfield(L, 1, "Object");
  strcpy(object, lua_tostring(L, 6));

  Entity *e;
  if (strcmp(entity, "Player") == 0) 
    e = world->addPlayer(x, z, s);
  else if (strcmp(entity, "Enemy") == 0)
    e = world->addEnemy(x, z, s);
  else if (strcmp(entity, "Floor") == 0)
    e = world->addFloorDecor(x, z, s);
  else 
    e = world->addWallDecor(x, z, s);

  if (strcmp(object, "Sprite") == 0)
    addSprite(L, e);
  else
    addMesh(L, e);

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
  {"addLight", addLight},
  {"addEntity", addEntity},
  {"addTexture", addTexture},
  {NULL, NULL}
};

LuaInter::LuaInter()
{
}

LuaInter* LuaInter::Instance()
{
  static LuaInter* ins = new LuaInter;
  return ins;
}

void LuaInter::init(World* w)
{
  world = w;

  L = luaL_newstate();
  luaL_openlibs(L);

  luaL_register(L, "World", worldfunc);

  if (luaL_dofile(L, "./src/tool/config.lua"))
    lua_error(L);

  if (luaL_dofile(L, "./src/tool/callback.lua"))
    lua_error(L);

}

void LuaInter::initWorld()
{
  lua_getglobal(L, "initWorld");
  if (lua_pcall(L, 0, 0, 0)) 
    lua_error(L);
  lua_settop(L, 0);
}

void LuaInter::getPlayTex(const Vector3 &speed, int *texid, float tex[][2], bool *alpha_test)
{
  lua_getglobal(L, "playerTexFunc");
  lua_pushnumber(L, speed.x);
  lua_pushnumber(L, speed.z);
  if (lua_pcall(L, 2, 3, 0))
    lua_error(L);

  int bottom = lua_gettop(L);
  if (lua_isnil(L, bottom)) 
    *alpha_test = false;
  else {
    *alpha_test = lua_toboolean(L, bottom);
    lua_pop(L, 1);
  }
  
  bottom = lua_gettop(L);
  for (int i = 0; i < 4; ++i) {
    lua_pushinteger(L, 2*i + 1);
    lua_gettable(L, bottom);
    tex[i][0] = lua_tonumber(L, -1);

    lua_pushinteger(L, 2*i + 2);
    lua_gettable(L, bottom);
    tex[i][1] = lua_tonumber(L, -1);

    lua_pop(L, 2);
  }
  lua_pop(L, 1);

  *texid = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void LuaInter::getEnemyTex(const Vector3 &speed, int *texid, float tex[][2], bool *alpha_test)
{
  lua_getglobal(L, "enemyTexFunc");
  lua_pushnumber(L, speed.x);
  lua_pushnumber(L, speed.z);
  if (lua_pcall(L, 2, 3, 0))
      lua_error(L);

  int bottom = lua_gettop(L);
  if (lua_isnil(L, bottom)) 
    *alpha_test = false;
  else {
    *alpha_test = lua_toboolean(L, -1);
    lua_pop(L, 1);
  }
  
  bottom = lua_gettop(L);
  for (int i = 0; i < 4; ++i) {
    lua_pushinteger(L, 2*i + 1);
    lua_gettable(L, bottom);
    tex[i][0] = lua_tonumber(L, -1);

    lua_pushinteger(L, 2*i + 2);
    lua_gettable(L, bottom);
    tex[i][1] = lua_tonumber(L, -1);

    lua_pop(L, 2);
  }
  lua_pop(L, 1);

  *texid = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void LuaInter::getFloorTex(int *texid, float tex[][2])
{
  lua_getglobal(L, "floorTexFunc");
  if (lua_pcall(L, 0, 2, 0))
    lua_error(L);

  int bottom = lua_gettop(L);
  
  *texid = lua_tointeger(L, -2);
  for (int i = 0; i < 4; ++i) {
    lua_pushinteger(L, 2*i + 1);
    lua_gettable(L, bottom);
    tex[i][0] = lua_tonumber(L, -1);

    lua_pushinteger(L, 2*i + 2);
    lua_gettable(L, bottom);
    tex[i][1] = lua_tonumber(L, -1);

    lua_pop(L, 2);
  }
  
  lua_pop(L, 2);
}

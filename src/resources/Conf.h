#ifndef DEF_UTIL_CONF
#define DEF_UTIL_CONF

#define DEBUG true

#define WORLD_WIDTH 2048
#define WORLD_HEIGHT 2048
#define GRID_UNIT 2
#define GRID_WIDTH (WORLD_WIDTH/GRID_UNIT)
#define GRID_HEIGHT (WORLD_HEIGHT/GRID_UNIT)

#define SCREEN_WIDTH 1024.f
#define SCREEN_HEIGHT 512.f

#define USE_VBO false
#define DRAW_OUTLINE false
#define USE_TEX true

#define MAX_STEPS 150000

#define MAX_PT 8
#define MAX_EMY 20

enum NOTIFICATION {
  ON_KEY_LEFT_DOWN,
  ON_KEY_RIGHT_DOWN,
  ON_KEY_UP_DOWN,
  ON_KEY_DOWN_DOWN,
  ON_KEY_RETURN_DOWN
};

#endif


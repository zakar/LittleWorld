#ifndef DEF_UTIL_CONF
#define DEF_UTIL_CONF

#define DEBUG true

#define WORLD_WIDTH 2048
#define WORLD_HEIGHT 2048
#define GRID_UNIT 2
#define GRID_WIDTH (WORLD_WIDTH/GRID_UNIT)
#define GRID_HEIGHT (WORLD_HEIGHT/GRID_UNIT)

#define SCREEN_WIDTH 800.f
#define SCREEN_HEIGHT 600.f

#define USE_VBO false
#define DRAW_OUTLINE false

enum NOTIFICATION {
  ON_KEY_LEFT_DOWN,
  ON_KEY_RIGHT_DOWN,
  ON_KEY_UP_DOWN,
  ON_KEY_DOWN_DOWN
};

#endif


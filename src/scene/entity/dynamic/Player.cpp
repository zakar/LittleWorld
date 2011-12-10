#include "Player.h"

using namespace std;

Player::Player(float x, float z, float s) : Dynamic(s)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;
  Manager::Instance()->updateGrid(position, s, 3 );
}

Player::~Player()
{
}

void Player::onNotify(unsigned const int type)
{
  switch (type) {
  case ON_KEY_LEFT_DOWN:
    speed.x = 0.f;
    speed.z = 300.f;
    break;

  case ON_KEY_RIGHT_DOWN:
    speed.x = 0.f;
    speed.z = -300.f;
    break;

  case ON_KEY_UP_DOWN:
    speed.x = -300.f;
    speed.z = 0.f;
    break;

  case ON_KEY_DOWN_DOWN:
    speed.x = 300.f;
    speed.z = 0.f;
    break;
  }
}

void Player::update(float time)
{
  Manager::Instance()->updateGrid(position, size, 0);
  position += speed*time;
  speed *= 0.8;
  Manager::Instance()->updateGrid(position, size, 3);

  LuaInter::Instance()->getPlayTex(speed, &texid, tex, &alpha_test);
}

int Player::echo() {  return 0;  }

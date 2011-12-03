#include "Player.h"

using namespace std;

Player::Player(float x, float z, float s) : Dynamic(s)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;
  //  Manager::Instance()->updateGrid(position, s, 1);
  timer.Reset();
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
  if (Manager::Instance()->checkHit(position + speed*time, size)) {
    speed = Vector3::zero;
  }
  
  position += speed*time;
  speed *= 0.8;

  LuaInter::Instance()->getPlayTex(speed, &texid, tex);

  if (timer.GetElapsedTime() > 1.0) {
    Manager::Instance()->updatePath(position);
    timer.Reset();
  }
}

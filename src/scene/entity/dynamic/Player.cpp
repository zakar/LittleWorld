#include "Player.h"
#include <cmath>
#include "../../../game/Game.h"

using namespace std;

Player::Player(float x, float z, float s) : Dynamic(s)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;
  Manager::Instance()->updateGrid(position, s, 3 );
  playerStop.Reset();
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
  if ( Manager::Instance()->checkHit(position+speed*time,size) ) {
	speed.x = speed.z = 0;
  }
  position += speed*time;
  speed *= 0.8;
  Manager::Instance()->updateGrid(position, size, 3);

  if (fabs(speed.x) > 1.0 || fabs(speed.z) > 1.0)
    playerStop.Reset();

  if (playerStop.GetElapsedTime() > 3.0) {
    Game::Instance()->setGameState(1);
    return;
  }

  LuaInter::Instance()->getPlayTex(speed, &texid, tex, &alpha_test);
}

int Player::echo() {  return 0;  }

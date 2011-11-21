#include "Player.h"
#include <cstdio>

using namespace std;

Player::Player(World *w, float x, float z, float s) : Dynamic(w, s)
{
  speed = 200.f;

  position.x = x;
  position.y = 0.f;
  position.z = z;
}

void Player::onNotify(unsigned const int type)
{
  if (type ==  Notifications::ON_MOUSE_LEFT_DOWN) {
    setPath(world->getPath(&position, world->getMouseX(), world->getMouseY(), getSize()));
  }

  if (type ==  Notifications::ON_KEY_LEFT_DOWN) {
    setPath(world->getPath(&position, position.x, position.z + speed/2.f, getSize()));
    puts("L");
  }

  if (type == Notifications::ON_KEY_RIGHT_DOWN) {
    setPath(world->getPath(&position, position.x, position.z - speed/2.f, getSize()));
    puts("R");
  }
	    
  if (type == Notifications::ON_KEY_UP_DOWN) {
    setPath(world->getPath(&position, position.x - speed/2.f, position.z, getSize()));
    puts("U");
  }
  
  if (type == Notifications::ON_KEY_DOWN_DOWN) {
    setPath(world->getPath(&position, position.x + speed/2.f, position.z, getSize()));
    puts("D");
  }

  move(1.0);
}

void Player::update(float time)
{
  move(time);
}


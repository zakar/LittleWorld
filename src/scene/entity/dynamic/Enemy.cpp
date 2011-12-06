#include "Enemy.h"

using namespace std;

Enemy::Enemy(float x, float z, float s) : Dynamic(s)
{
  static int tot = 0;
  position.x = x;
  position.y = 0.f;
  position.z = z;
  zero_move = last_move_x = last_move_z = 0;
  id = tot;
  tot++;
}

int Enemy::echo() {  return 1;  }

int Enemy::getID() {  return id;  }


void Enemy::update(float time)
{
  Manager::Instance()->updateGrid(position, size, 0);
  Manager::Instance()->fetchSpeed(position, speed, id);
  if (Manager::Instance()->checkHit(position + speed*time, size)) {
    speed = Vector3::zero;
  }
  if ( speed.x == 0 && speed.z == 0 ) {
    zero_move++;
    speed.x = last_move_x * 100.0;
    speed.z = last_move_z * 100.0;
    if (Manager::Instance()->checkHit(position + speed*time, size)) {
      speed = Vector3::zero;
    }
    if ( zero_move > 5 ) {
      last_move_x = (rand()%3-1);
      last_move_z = (rand()%3-1);
      zero_move = 0;
    }
  } else {
    zero_move = 0;
    last_move_x = int(speed.x)/100;
    last_move_z = int(speed.z)/100;
  }
  if ( position.x+speed.x*time >= 0 && position.x+speed.x*time <= WORLD_WIDTH && position.z+speed.z*time >= 0 && position.z+speed.z*time <= WORLD_HEIGHT ) position += speed * time;
  Manager::Instance()->updateGrid(position, size, 1);
}


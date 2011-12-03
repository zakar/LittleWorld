#include "Enemy.h"

using namespace std;

Enemy::Enemy(float x, float z, float s) : Dynamic(s)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;
}

void Enemy::update(float time)
{
  Manager::Instance()->fetchSpeed(position, speed);
  
  if (Manager::Instance()->checkHit(position + speed*time, size)) {
    speed = Vector3::zero;
  }
  
  position += speed * time;
}


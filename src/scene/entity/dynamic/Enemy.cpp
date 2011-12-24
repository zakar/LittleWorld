#include "Enemy.h"

using namespace std;

int Enemy::tot = 0;

Enemy::Enemy(float x, float z, float s) : Dynamic(s)
{
  position.x = x;
  position.y = 0.f;
  position.z = z;
  circle_move = last_move_x = last_move_z = last_x = last_z = zero_move = 0;
  id = tot;
  tot++;
}

int Enemy::echo() {  return 1;  }

int Enemy::getID() {  return id;  }


void Enemy::update(float time)
{
  Manager::Instance()->updateGrid(position, size, 0);
  bool match = Manager::Instance()->fetchSpeed(position, speed, id);
  /*
  */
  if ( !Manager::Instance()->checkHit( position + speed*time , size ) ) circle_move = 0;
  else {
	  Vector3 next;
	  next.x = last_move_x;
	  next.y = 0;
	  next.z = last_move_z;
	  if ( circle_move && !Manager::Instance()->checkHit( position + next*time , size ) ) {
		  speed.x = last_move_x;
		  speed.z = last_move_z;
	  } else {
		 circle_move = 1;
		 Vector3 tmp(speed);
		 tmp.z = 0;
		 Vector3 d1 , d2;
		 if ( Manager::Instance()->checkHit( position + tmp*time , size ) ) {
			 d1.x = d2.x = d1.y = d2.y = 0;
			 if ( speed.z >= 0 ) d1.z = 100;
			 else d1.z = -100;
		 } else {
			 d1.z = d2.z = d1.y = d2.y = 0;
			 if ( speed.x >= 0 ) d1.x = 100;
			 else d1.x = -100;
		 }
	//	 if ( Manager::Instance()->checkHit( position + d1*time , size ) ) speed = d1;
	//	 else if ( Manager::Instance()->checkHit( position + d2*time , size ) ) speed = d2;
	//	 else {
//			int d = rand()%2;
//			speed = (!d) ? d1 : d2;
	//	 }
		 speed = d1;
		 last_move_x = speed.x;
		 last_move_z = speed.z;
	  }
  }
  if (Manager::Instance()->checkHit(position + speed*time, size)) {
    speed = Vector3::zero;
  }
  if ( speed.x == 0 && speed.z == 0 ) {
    zero_move++;
	
    speed.x = last_x * 100.0;
    speed.z = last_z * 100.0;
    if ( zero_move > 5 ) {
      last_x = (rand()%3-1);
      last_z = (rand()%3-1);
      zero_move = 0;
    }
  } else {
    zero_move = 0;
    last_x = int(speed.x)/100;
    last_z = int(speed.z)/100;
  }
  
  if ( match ) {
	 speed.x *= 1.5;
	 speed.z *= 1.5;
  }
  
  if ( position.x+speed.x*time >= 0 && position.x+speed.x*time <= WORLD_WIDTH && position.z+speed.z*time >= 0 && position.z+speed.z*time <= WORLD_HEIGHT && !Manager::Instance()->checkHit( position + speed*time , size ) ) position += speed * time;
  Manager::Instance()->updateGrid(position, size/2, 1);
}


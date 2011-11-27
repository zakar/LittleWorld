#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
  Camera::Instance()->draw(&meshList, &spriteList, &lightList);
}

void World::update(float time)
{
  for (vector<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
      (*i)->update(time);
    }

  Camera::Instance()->update(time);
}

void World::dispatch(unsigned const int type)
{
  for (vector<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
      (*i)->onNotify(type);
    }
}

float World::getMouseX() { return mouseX; }
float World::getMouseY() { return mouseY; }

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
  // Apply transformation
  mouseY = (mouseScreenY * 2.f - mouseScreenX) / 2.f;
  mouseX = mouseScreenX + mouseY;

  // Scale
  mouseY *= 2.f;
  mouseX *= 2.f;

  // Add camera offset
  mouseX += Camera::Instance()->getX();
  mouseY += Camera::Instance()->getZ();
}


Entity* World::addPlayer(float x, float z, float size)
{
  dynamicList.push_back(new Player(x, z, size));
  Camera::Instance()->setFocus(dynamicList.back());
  return dynamicList.back();
}

Entity* World::addEnemy(float x, float z, float size)
{
  dynamicList.push_back(new Enemy(x, z, size));
  return dynamicList.back();
}

Entity* World::addWallDecor(float x, float z, float size)
{
  staticList.push_back(new Decor(x, z, size, false));
  return staticList.back();
}

Entity* World::addFloorDecor(float x, float z, float size)
{
  staticList.push_back(new Decor(x, z, size, true));
  return staticList.back();
}

void World::addSprite(Entity *e, float *RGBA, int totalVertex, float *vertex, float *texCoord)
{
  Sprite *sprite = new Sprite(e);
  sprite->setData(RGBA, totalVertex, vertex, texCoord);
  spriteList.push_back(sprite);
}

void World::addMesh(Entity *e, float size, float height, float *RGBA)
{
  Mesh *mesh = new Mesh(e);
  mesh->setData(size, height, RGBA);
  meshList.push_back(mesh);
}


void World::addLight(float x, float y, float z, float r, float g, float b)
{
  staticList.push_back(new Emitter(x, y, z));
  lightList.push_back(new Light(staticList.back(), r, g, b));
}



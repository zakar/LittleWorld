#include "World.h"

using namespace std;

unsigned const int World::ON_MOUSE_LEFT_DOWN = 1;
unsigned const int World::ON_WINDOW_RESIZED  = 2;

World::World()
{
}

void World::draw()
{
    camera.draw(&meshList, &spriteList, &lightList);
}

void World::update(float time)
{
    for (list<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
        (*i)->update(time);
    }

    camera.update(time);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Apply transformation
    mouseY = (mouseScreenY * 2.f - mouseScreenX) / 2.f;
    mouseX = mouseScreenX + mouseY;

    // Scale
    mouseY *= 2.f;
    mouseX *= 2.f;

    // Add camera offset
    mouseX += camera.getX();
    mouseY += camera.getZ();
}

void World::dispatch(unsigned const int type)
{
    for (list<Dynamic*>::iterator i = dynamicList.begin(); i != dynamicList.end(); ++ i)
    {
        (*i)->onNotify(type);
    }
}

void World::addPlayer(bool focus)
{
    dynamicList.push_back(new Player(this, 64.f));
    meshList.push_back(new Mesh(dynamicList.back(), 64.f, 64.f, 1.f, 1.f, 0.f, 1.f));

    if (focus) camera.setFocus(dynamicList.back());
}

void World::addEnemy(float x, float z)
{
}

void World::addWallTile(float x, float z, float h)
{
    staticList.push_back(new Tile(this, x, z, 128.f, true));
    meshList.push_back(new Mesh(staticList.back(), 128.f, h, 1.f, 1.f, 1.f, 1.f));
}

void World::addFloorTile(float x, float z)
{
    staticList.push_back(new Tile(this, x, z, 128.f, true));
    meshList.push_back(new Mesh(staticList.back(), 128.f, 8.f, 1.f, 1.f, 1.f, 1.f));
}

void World::addLight(float x, float z, float y, float r, float v, float b)
{
}


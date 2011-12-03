#ifndef DEF_WORLD
#define DEF_WORLD

#include "../resources/Conf.h"
#include "../math/Vector3.h"

#include "entity/Dynamic.h"
#include "entity/dynamic/Enemy.h"
#include "entity/dynamic/Player.h"

#include "entity/Static.h"
#include "entity/static/Emitter.h"
#include "entity/static/Decor.h"

#include "Camera.h"
#include "../ai/Manager.h"

#include <vector>
#include <iostream>

class World
{
    public:

        World();

        void draw();
        void update(float time);
        void updateMousePosition(float mouseScreenX, float mouseScreenY);
        void dispatch(unsigned const int type);

	Entity* addPlayer(float x, float z, float size);
	Entity* addEnemy(float x, float z, float size);
	Entity* addWallDecor(float x, float z, float size);
	Entity* addFloorDecor(float x, float z, float size);

	void addSprite(Entity *e, float *RGBA, int totalVertex, float *vertex, float *normal);
	void addMesh(Entity *e, float size, float height, float *RGBA);

        void addLight(float x, float z, float y, float r, float g, float b);

        float getMouseX();
        float getMouseY();


    private:

        float mouseX;
        float mouseY;

	std::vector<Dynamic*> dynamicList;
        std::vector<Static*>  staticList;
        std::vector<Mesh*>    meshList;
        std::vector<Sprite*>  spriteList;
        std::vector<Light*>   lightList;
};

#endif


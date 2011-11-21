#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "../resources/Conf.h"

#include "../math/Vector3.h"
#include "../math/Matrix4x4f.h"
#include "../math/Frustum.h"

#include "../graphics/Object.h"
#include "../graphics/object/Mesh.h"
#include "../graphics/object/Light.h"
#include "../graphics/object/Sprite.h"

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(std::vector<Mesh*> *meshes, std::vector<Sprite*> *sprites, std::vector<Light*> *lights);
        void setFocus(Entity *o);

        float getX();
        float getY();
        float getZ();


    private:

        void drawObject(Object *o);
        void outlineObject(Object *o);
        void drawAllMeshes(std::vector<Mesh*> *objects);
        void outlineAllMeshes(std::vector<Mesh*> *objects);
        void drawAllSprites(std::vector<Sprite*> *objects);
        void outlineAllSprites(std::vector<Sprite*> *objects);
        void drawAllLights(std::vector<Light*> *objects);
        void outlineAllLights(std::vector<Light*> *objects);
        void drawAllShadows(std::vector<Mesh*> *objects, Light *l);
        void updateMeshesVisibility(std::vector<Mesh*> *objects);
        void updateSpritesVisibility(std::vector<Sprite*> *objects);
        void updateViewFrustum();
        void setupLight(Light *l);

        Entity* focus;

        Vector3 position;

        Frustum viewFrustum;

        float speed;
        float tolerance;
        float inertia;
};

#endif


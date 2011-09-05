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
#include <list>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(std::list<Mesh*> *meshes, std::list<Sprite*> *sprites, std::list<Light*> *lights);
        void setFocus(Entity *o);

        float getX();
        float getY();
        float getZ();


    private:

        void drawAllMeshes(std::list<Mesh*> *objects);
        void outlineAllMeshes(std::list<Mesh*> *objects);
        //void drawAllShadows(std::list<Object*> *objects, Light *l);
        //void drawAllLigthned(std::list<Object*> *objects);
        //void updateAllShadows(std::list<Object*> *objects, Light *l);
        //void updateObjectsVisibility(std::list<Object*> *objects);
        //void updateObjectsLightning(std::list<Object*> *objects, Light *l);
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


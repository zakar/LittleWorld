#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "Object.h"
#include "util/primitive/Vector2.h"
#include "util/Conf.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(std::list<Object*> objects);
        void setFocus(Object *o);
        void toScreenPosition(Vector2 *p);

        float getX();
        float getY();


    private:

        void translateCamera();
        void translateObject(Object* o);

        Object* focus;

        Vector2 position;

        float speed;
        float tolerance;
        float inertia;
};

#endif

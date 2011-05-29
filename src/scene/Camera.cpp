#include "Camera.h"

using namespace std;

Camera::Camera()
{
    speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;

    position.x = 0.f;
    position.y = 0.f;
}

void Camera::draw(list<Object*> objects)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    translateCamera();

    // Lighting
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    glPushMatrix();
    translateObject(focus);

    GLfloat LightAmb[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat LightPos[] = {0.f, 0.f, 40.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glPopMatrix();

    // Draw all objects
    glColorMask(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);

    for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
    {
        glPushMatrix();
        translateObject(*i);

        (*i)->draw();
        (*i)->drawOutline();
        (*i)->updateShadows
        (
            (focus->getX() - (*i)->getX()) - (focus->getY() - (*i)->getY()),
            ((focus->getX() - (*i)->getX()) + (focus->getY() - (*i)->getY())) / 2.f
        );

        glPopMatrix();
    }

    // Draw projected shadows to stencil buffer
    glColorMask(0, 0, 0, 0);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
    {
        glPushMatrix();
        translateObject(*i);

        (*i)->drawShadow();

        glPopMatrix();
    }

    for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
    {
        if ((*i)->shadowEnabled() && (*i)->getHeight() > 0.f)
        {
            glPushMatrix();
            translateObject(*i);

            glStencilFunc(GL_EQUAL, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

            (*i)->draw();

            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            (*i)->drawWallShadows(objects);

            glPopMatrix();
        }
    }

    glPopMatrix();

    // Fill stencil buffer
    glColorMask(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);

    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
        glVertex2f(0.f, Conf::SCREEN_HEIGHT);
    glEnd();

    glDisable(GL_STENCIL_TEST);

    // Contrast
    glBlendFunc( GL_DST_COLOR, GL_ONE );
    glColor4f(1.8f, 1.8f, 1.8f, 1.f);
    glBegin(GL_QUADS);
        glVertex2f(0.f, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, 0.f);
        glVertex2f(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
        glVertex2f(0.f, Conf::SCREEN_HEIGHT);
    glEnd();
    glDisable(GL_BLEND);
}

void Camera::update(float time)
{
    if (position.x - focus->getX() > tolerance)
    {
        position.x -= (position.x - (focus->getX() + tolerance)) / (inertia / time);
    }
    else if (focus->getX() - position.x > tolerance)
    {
        position.x += ((focus->getX() - tolerance) - position.x) / (inertia / time);
    }

    if (position.y - focus->getY() > tolerance)
    {
        position.y -= (position.y - (focus->getY() + tolerance)) / (inertia / time);
    }
    else if (focus->getY() - position.y > tolerance)
    {
        position.y += ((focus->getY() - tolerance) - position.y) / (inertia / time);
    }
}

void Camera::toScreenPosition(Vector2 *p)
{
    float nx = p->x;
    float ny = p->y;
    p->x = nx - ny;
    p->y = (nx + ny) / 2.f;
    p->x += position.y - position.x + 288.f + (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f);
    p->y += ((position.x + position.y - (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f)) / -2.f) - 64.f;
}

void Camera::setFocus(Object *o)
{
    focus = o;
}

float Camera::getX()
{
    return position.x;
}

float Camera::getY()
{
    return position.y;
}

void Camera::translateCamera()
{
    glTranslatef
    (
        position.y - position.x + 288.f + (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f), // Origin is centered on the screen
        ((position.x + position.y - (Conf::SCREEN_WIDTH / 2.f) - (Conf::SCREEN_HEIGHT / 2.f)) / -2.f) - 64.f, // So minus alf screen width and height
        0.f
    );
}

void Camera::translateObject(Object *o)
{
    glTranslatef
    (
        // World to screen's X coordinate
        o->getX() - o->getY(),

        // World to screen's Y coordinate
        (o->getX() + o->getY()) / 2.f,

        // Z index is calc using screen's Y coord lowered to tiles screen height + object's index
        (o->getHeight() == 0.f) ? -1.f : -1.f / (((o->getX() + o->getY()) / 2.f) / 64.f + o->getIndex())
    );
}


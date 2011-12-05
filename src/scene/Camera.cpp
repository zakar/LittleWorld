#include "Camera.h"
#include <cstdio>

using namespace std;

Camera::Camera()
{
  tolerance = 50.f;
  inertia   = 0.3f;

  position.x = 0.f;
  position.y = 0.f;
  position.z = 0.f;

  angleX = 30.0;
  angleY = -45.0;
}

Camera* Camera::Instance()
{
  static Camera* ins = new Camera;
  return ins;
}

void Camera::draw(std::vector<Mesh*> *meshes, std::vector<Sprite*> *sprites, std::vector<Light*> *lights)
{
  glLoadIdentity();
  glRotatef(angleX, 1.f, 0.f, 0.f);
  glRotatef(angleY, 0.f, 1.f, 0.f);
  glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

  glPushMatrix();
  glTranslatef(position.x * -1.f,  position.y * -1.f, position.z * -1.f);

  updateViewFrustum();
  updateMeshesVisibility(meshes);
  updateSpritesVisibility(sprites);

  GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);

  glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT);
  drawAllMeshes(meshes);
  drawAllSprites(sprites);
  glDepthMask(GL_FALSE);
  
  int id = 0;
   for (vector<Light*>::iterator l = lights->begin(); l != lights->end(); ++l, ++id) {
    if ((*l)->getIntensityAtPosition(position) < 0.004f) continue;
    setupLight(*l, id);
    glEnable(GL_LIGHT0 + id);
  }

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL); 
  glDepthFunc(GL_EQUAL);

  glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
  glClear(GL_COLOR_BUFFER_BIT);

  drawAllMeshes(meshes);
  drawAllSprites(sprites);
 
  glDisable(GL_LIGHTING);
  for (int i = 0; i < id; ++i) 
    glDisable(GL_LIGHT0 + i);
  glDisable(GL_COLOR_MATERIAL);


  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);


#if DRAW_OUTLINE
  glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  outlineAllMeshes(meshes);
  outlineAllSprites(sprites);
  outlineAllLights(lights);

  glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
  glDisable(GL_BLEND);
#endif

  glPopMatrix();
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

  if (position.z - focus->getZ() > tolerance)
    {
      position.z -= (position.z - (focus->getZ() + tolerance)) / (inertia / time);
    }
  else if (focus->getZ() - position.z > tolerance)
    {
      position.z += ((focus->getZ() - tolerance) - position.z) / (inertia / time);
    }
}

void Camera::updateViewFrustum()
{
  Matrix4x4f projMatrix;
  Matrix4x4f viewMatrix;

  glGetFloatv(GL_PROJECTION_MATRIX, projMatrix.m);
  glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix.m);

  viewFrustum.update(projMatrix * viewMatrix);
}

void Camera::setFocus(Entity *e)
{
  focus = e;
  position.x = e->getX();
  position.z = e->getZ();
}

float Camera::getX()
{
  return position.x;
}

float Camera::getY()
{
  return position.y;
}

float Camera::getZ()
{
  return position.z;
}

void Camera::drawObject(Object *o)
{
  if (o->isVisible())
    {
      glPushMatrix();
      glTranslatef(o->getX(), o->getY(), o->getZ());
      o->draw();
      glPopMatrix();
    }
}

void Camera::outlineObject(Object *o)
{
  if (o->isVisible())
    {
      glPushMatrix();
      glTranslatef(o->getX(), o->getY(), o->getZ());
      o->outline();
      glPopMatrix();
    }
}

void Camera::drawAllMeshes(std::vector<Mesh*> *objects)
{
  for (vector<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      drawObject(*o);
    }
}

void Camera::outlineAllMeshes(std::vector<Mesh*> *objects)
{
  for (vector<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      outlineObject(*o);
    }
}

void Camera::drawAllSprites(std::vector<Sprite*> *objects)
{
  for (vector<Sprite*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      drawObject(*o);
    }
}

void Camera::outlineAllSprites(std::vector<Sprite*> *objects)
{
  for (vector<Sprite*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      outlineObject(*o);
    }
}

void Camera::drawAllLights(std::vector<Light*> *objects)
{
  for (vector<Light*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      outlineObject(*o);
    }
}

void Camera::outlineAllLights(std::vector<Light*> *objects)
{
  for (vector<Light*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      outlineObject(*o);
    }
}

void Camera::setupLight(Light *l, int id)
{
  glPushMatrix();
  glTranslatef(l->getX(), l->getY(), l->getZ());
  l->setup(id);
  glPopMatrix();
}

void Camera::drawAllShadows(std::vector<Mesh*> *objects, Light *l)
{
  for (vector<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      glPushMatrix();
      glTranslatef((*o)->getX(), (*o)->getY(), (*o)->getZ());
      (*o)->drawShadow(l);
      glPopMatrix();
    }
}

void Camera::updateMeshesVisibility(std::vector<Mesh*> *objects)
{
  for (vector<Mesh*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      (*o)->setVisibility(viewFrustum.sphereInFrustum((*o)->getPosition(), (*o)->getSize()));
    }
}

void Camera::updateSpritesVisibility(std::vector<Sprite*> *objects)
{
  for (vector<Sprite*>::iterator o = objects->begin(); o != objects->end(); ++ o)
    {
      (*o)->setVisibility(viewFrustum.sphereInFrustum((*o)->getPosition(), (*o)->getSize()));
    }
}

void Camera::rotateCamera(float detx, float dety)
{
  angleX += detx;
  if (angleX > 360.0) angleX -= 360.0;
  if (angleX < 0.0) angleX += 360.0;

  angleY += dety;
  if (angleY > 360.0) angleY -= 360.0;
  if (angleY < 0.0) angleY += 360.0;
}

#include "Light.h"

using namespace std;

Light::Light(Entity *e, float r, float g, float b) : Object(e)
{
  red   = r;
  green = g;
  blue  = b;

  ca = 0.1f;
  la = 0.004f;
  qa = 0.00005f;
}

Light::~Light()
{
}

void Light::draw()
{
  glColor4f(red, green, blue, 1.f);

  glBegin(GL_TRIANGLES);
  glVertex3f( 0.f,  32.f,  0.f);
  glVertex3f( 16.f,  0.f,  16.f);
  glVertex3f(-16.f,  0.f,  16.f);

  glVertex3f( 0.f,  32.f,  0.f);
  glVertex3f(-16.f,  0.f,  16.f);
  glVertex3f(-16.f,  0.f, -16.f);

  glVertex3f( 0.f,  32.f,  0.f);
  glVertex3f(-16.f,  0.f, -16.f);
  glVertex3f( 16.f,  0.f, -16.f);

  glVertex3f( 0.f,  32.f,  0.f);
  glVertex3f( 16.f,  0.f, -16.f);
  glVertex3f( 16.f,  0.f,  16.f);

  glVertex3f( 0.f, -32.f,  0.f);
  glVertex3f(-16.f,  0.f,  16.f);
  glVertex3f( 16.f,  0.f,  16.f);

  glVertex3f( 0.f, -32.f,  0.f);
  glVertex3f(-16.f,  0.f, -16.f);
  glVertex3f(-16.f,  0.f,  16.f);

  glVertex3f( 0.f, -32.f,  0.f);
  glVertex3f( 16.f,  0.f, -16.f);
  glVertex3f(-16.f,  0.f, -16.f);

  glVertex3f( 0.f, -32.f,  0.f);
  glVertex3f( 16.f,  0.f,  16.f);
  glVertex3f( 16.f,  0.f, -16.f);
  glEnd();
}

void Light::outline()
{
  glColor4f(red, green, blue, 1.f);

  glBegin(GL_LINES);
  glVertex3f( 16.f,  16.f, -16.f);
  glVertex3f(-16.f, -16.f,  16.f);

  glVertex3f(-16.f, -16.f, -16.f);
  glVertex3f( 16.f,  16.f,  16.f);

  glVertex3f( 16.f, -16.f, -16.f);
  glVertex3f(-16.f,  16.f,  16.f);

  glVertex3f(-16.f,  16.f, -16.f);
  glVertex3f( 16.f, -16.f,  16.f);
  glEnd();
}

void Light::setup(int id)
{
  GLfloat LightPos[] = {0.f, 0.f, 0.f, 1.f}; // TODO 100.f was the y position ...
  GLfloat LightAmb[] = {red, green, blue, 1.f};
  GLfloat LightDif[] = {red, green, blue, 1.f};

  glLightfv(GL_LIGHT0 + id, GL_POSITION, LightPos);
  glLightfv(GL_LIGHT0 + id, GL_AMBIENT, LightAmb);
  glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, LightDif);

  glLightf(GL_LIGHT0 + id, GL_CONSTANT_ATTENUATION, ca);
  glLightf(GL_LIGHT0 + id, GL_LINEAR_ATTENUATION, la);
  glLightf(GL_LIGHT0 + id, GL_QUADRATIC_ATTENUATION, qa);
}

float Light::getIntensityFromDistance(float distance)
{
  return 1 / (ca + la * distance + qa * pow(distance, 2));
}

float Light::getIntensityAtPosition(Vector3 p)
{
  return getIntensityFromDistance(Vector3Util::dist(getPosition(), p));
}


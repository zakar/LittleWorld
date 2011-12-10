#include "Object.h"

using namespace std;

Object::Object(Entity *e)
{
    entity = e;
    visible = false;
}

Object::~Object()
{
}

void Object::draw()
{
}

void Object::outline()
{
}

void Object::setVisibility(bool v)
{
    visible = v;
}

float Object::getX()    { return entity->getX(); }
float Object::getY()    { return entity->getY(); }
float Object::getZ()    { return entity->getZ(); }
float Object::getSize() { return entity->getSize(); }

bool Object::isVisible() { return visible; }

Vector3 Object::getPosition() { return entity->getPosition(); }

void Object::genTex2D(const char *file, GLuint *texid, GLsizei width, GLsizei height)
{
  sf::Image img;
  img.LoadFromFile(file);

  glGenTextures(1, texid);
  glBindTexture(GL_TEXTURE_2D, *texid);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		  GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		  GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, img.GetPixelsPtr());
}

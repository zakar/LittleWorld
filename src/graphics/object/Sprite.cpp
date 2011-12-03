#include "Sprite.h"

using namespace std;

Sprite::Sprite(Entity *e) : Object(e)
{
}

void Sprite::getTexFromEntity(void)
{
  for (int i = 0; i < 4; ++i) {
    vertices[i].tex[0] = entity->tex[i][0];
    vertices[i].tex[1] = entity->tex[i][1];
  }
}

void Sprite::setData(float *RGBA, int totalVertex, float *vertex, float *normal)
{
  this->totalVertex = totalVertex;
  this->totalIndexes = totalVertex;

  for (int i = 0; i < totalVertex; ++i) {
    vertices[i].location[X_POS] = vertex[3*i];
    vertices[i].location[Y_POS] = vertex[3*i+1];
    vertices[i].location[Z_POS] = vertex[3*i+2];

    vertices[i].normal[X_POS]   = normal[3*i];
    vertices[i].normal[Y_POS]   = normal[3*i+1];
    vertices[i].normal[Z_POS]   = normal[3*i+2];
  }

  for (int i = 0; i < totalVertex; i++) {
    indexes[i] = i;
    vertices[i].color[0] = RGBA[0];
    vertices[i].color[1] = RGBA[1];
    vertices[i].color[2] = RGBA[2];
    vertices[i].color[3] = RGBA[3];
  }
}


void Sprite::draw()
{
  getTexFromEntity();
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, entity->texid);
  glBegin(GL_QUADS);
  for (unsigned int i = 0; i < totalIndexes; ++i) {

    glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
    glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
    glTexCoord2f(vertices[indexes[i]].tex[0], vertices[indexes[i]].tex[1]);
    glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Sprite::outline()
{
  for (unsigned int i = 0; i < totalIndexes; i ++)
    {
      if (i%3 == 0)
        {
	  if (i != 0)
            {
	      glEnd();
            }
	  glBegin(GL_LINE_LOOP);
        }
      glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
      glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
      glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
    }
  glEnd();
}


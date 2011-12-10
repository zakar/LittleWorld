#include "Sprite.h"

using namespace std;

Sprite::Sprite(Entity *e) : Object(e)
{
}

Sprite::~Sprite()
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
#if USE_TEX
  getTexFromEntity();
  if (entity->alpha_test) {
    glAlphaFunc(GL_GREATER, 0.01);
    glEnable(GL_ALPHA_TEST);
  }
    
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, entity->texid);
#endif

  glBegin(GL_QUADS);
  for (unsigned int i = 0; i < totalIndexes; ++i) {
    int idx = indexes[i];

    glColor4f(vertices[idx].color[0], vertices[idx].color[1], vertices[idx].color[2], vertices[idx].color[3]);
    glNormal3f(vertices[idx].normal[0], vertices[idx].normal[1], vertices[idx].normal[2]);

#if USE_TEX
    glTexCoord2f(vertices[idx].tex[0], vertices[idx].tex[1]);
#endif

    glVertex3f(vertices[idx].location[0], vertices[idx].location[1], vertices[idx].location[2]);
  }
  glEnd();

#if USE_TEX
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_ALPHA_TEST);
#endif
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


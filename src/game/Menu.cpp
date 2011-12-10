#include "Menu.h"
#include "Game.h"
#include "../tool/LuaInter.h"
#include "../resources/Conf.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Menu::Menu()
{
}

Menu* Menu::Instance()
{
  static Menu* ins = new Menu();
  return ins;
}

void Menu::setState(int state)
{
  this->state = state;
}

void Menu::dispatch(unsigned const int type)
{
  if (type == ON_KEY_RETURN_DOWN) {
    if (state == 1) 
      Game::Instance()->setGameState(2);
    else
      Game::Instance()->setGameState(1);
  }
}

void Menu::draw()
{
  LuaInter::Instance()->getBackGroundTex(state, &backgroundTexId);

  glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, backgroundTexId);

  glBegin(GL_QUADS);
  glTexCoord2f(1.0, 1.0);
  glVertex2f(SCREEN_WIDTH / -2.0, SCREEN_HEIGHT / -2.0);

  glTexCoord2f(0.0, 1.0);
  glVertex2f(SCREEN_WIDTH / -2.0, SCREEN_HEIGHT / 2.0);

  glTexCoord2f(0.0, 0.0);
  glVertex2f(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);

  glTexCoord2f(1.0, 0.0);
  glVertex2f(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / -2.0);

  glEnd();

  glDisable(GL_TEXTURE_2D);
  glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}


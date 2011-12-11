#include "Menu.h"
#include "Game.h"
#include "Application.h"
#include "../tool/LuaInter.h"
#include "../resources/Conf.h"
#include <SFML/Graphics.hpp>

static const char *backgroundTex[2] = { "./design/background1.jpg", "./design/background2.jpg" };
static const char *buttonTex[2][2] = {
  { "./design/t_start.png", "./design/t_exit.png" },
  { "./design/cfg_back.png", "./design/t_exit.png" },
};


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
  background.LoadFromFile(backgroundTex[state]);
  button[0].LoadFromFile(buttonTex[state][0]);
  button[1].LoadFromFile(buttonTex[state][1]);
  currentButton = 0;
}

void Menu::dispatch(unsigned const int type)
{
  switch (type) {
  case ON_KEY_RETURN_DOWN: 
    if (state == 0) {
      if (currentButton == 0)
	Game::Instance()->setGameState(2);
      else
	Application::Instance()->Close();
    } else {
      if (currentButton == 0)
	Game::Instance()->setGameState(0);
      else
	Application::Instance()->Close();
    }
    break;
    
  case ON_KEY_UP_DOWN:
  case ON_KEY_DOWN_DOWN:
    currentButton ^= 1;
    break;
  }
}

void Menu::draw()
{
  glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

  sf::Sprite backgroundS(background);
  sf::Sprite buttonS0(button[0]);
  sf::Sprite buttonS1(button[1]);

  buttonS0.SetPosition(100 + 100 * (currentButton == 0), 100);
  buttonS1.SetPosition(100 + 100 * (currentButton == 1), 200);

  Application::Instance()->Draw(backgroundS);
  Application::Instance()->Draw(buttonS0);
  Application::Instance()->Draw(buttonS1);

  glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}



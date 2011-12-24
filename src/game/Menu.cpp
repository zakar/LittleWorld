#include "Menu.h"
#include "Game.h"
#include "Application.h"
#include "../tool/LuaInter.h"
#include "../resources/Conf.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

static const char *backgroundTex[3] = { "./design/background1.jpg", 
					"./design/background2.jpg",
					"./design/background3.png" };
static const char *buttonTex[3][2] = {
  { "./design/t_start.png", "./design/t_exit.png" },
  { "./design/t_start.png", "./design/t_exit.png" },
  { "./design/t_start.png", "./design/t_exit.png" },  
};

static const int rectCoord[2][4] = {
  {0, 39, 160, 0}, {147, 39, 360, 0}
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

  for (int i = 0; i < 2; ++i) {
    button[i].LoadFromFile(buttonTex[state][i]);
    rect[i] = sf::IntRect(rectCoord[i][0], rectCoord[i][1],
			  rectCoord[i][2], rectCoord[i][3]);
  }  
  currentButton = 0;
}

void Menu::dispatch(unsigned const int type)
{
  switch (type) {
  case ON_KEY_RETURN_DOWN: 
    if (state == 0) {
      if (currentButton == 0)
	Game::Instance()->setGameState(3);
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

  buttonS0.SetSubRect(rect[(int)(currentButton == 0)]);
  buttonS1.SetSubRect(rect[(int)(currentButton == 1)]);

  buttonS0.SetPosition(100, 100);
  buttonS1.SetPosition(100, 200);

  Application::Instance()->Draw(backgroundS);
  Application::Instance()->Draw(buttonS0);
  Application::Instance()->Draw(buttonS1);

  glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}



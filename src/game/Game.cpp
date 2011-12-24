#include "Game.h"
#include "Menu.h"

using namespace std;
using namespace sf;

Game::Game()
{
  windowScale       = 1.f;
  windowPaddingLeft = 0.f;
  windowPaddingTop  = 0.f;
}

Game* Game::Instance()
{
  static Game* ins = new Game();
  return ins;
}

void Game::init()
{
  LuaInter::Instance()->init(&world);
  setGameState(OPENING);
}

void Game::draw()
{
  if (gameState == PLAYING)
    world.draw();
  else {
    Menu::Instance()->draw();
  }
}

void Game::update(float time)
{
  if (gameState == PLAYING) {
    world.update(time);
    if (gameState != PLAYING) { //update完且发现切换到Menu，这时才清除掉world中的entity
      world.clearAll();
      Manager::Instance()->clear();
      Enemy::clear();
    }
  }
}

void Game::onEvent(Event *event)
{
  if (event->Type == Event::KeyPressed) {
    if (gameState == PLAYING) {
      switch (event->Key.Code) {
      case Key::Left:
	world.dispatch(ON_KEY_LEFT_DOWN);
	break;
      case Key::Right:
	world.dispatch(ON_KEY_RIGHT_DOWN);
	break;
      case Key::Down:
	world.dispatch(ON_KEY_DOWN_DOWN);
	break;
      case Key::Up:
	world.dispatch(ON_KEY_UP_DOWN);
	break;
      case Key::I: 
	Camera::Instance()->rotateCamera(1.0, 0.0);
	break;
      case Key::K:
	Camera::Instance()->rotateCamera(-1.0, 0.0);
	break;
      case Key::J:
	Camera::Instance()->rotateCamera(0.0, 1.0);
	break;
      case Key::L:
	Camera::Instance()->rotateCamera(0.0, -1.0);
	break;
      }
    } else {
      switch (event->Key.Code) {
      case Key::Up:
	Menu::Instance()->dispatch(ON_KEY_UP_DOWN);
	break;
      case Key::Down:
	Menu::Instance()->dispatch(ON_KEY_DOWN_DOWN);
	break;
      case Key::Return:
	Menu::Instance()->dispatch(ON_KEY_RETURN_DOWN);
	break;
      }
    }
  }


  // RESIZE
  if (event->Type == Event::Resized) {
      world.dispatch(ON_WINDOW_RESIZED);
      if ((float)event->Size.Width / (float)event->Size.Height > SCREEN_WIDTH / SCREEN_HEIGHT) {
	windowScale = SCREEN_HEIGHT / event->Size.Height;
      }
      else {
	windowScale = SCREEN_WIDTH / event->Size.Width;
      }
      windowPaddingLeft = ((float)event->Size.Width - (SCREEN_WIDTH / windowScale)) / -2.f;
      windowPaddingTop  = ((float)event->Size.Height - (SCREEN_HEIGHT / windowScale)) / -2.f;
      cout << windowScale << endl;
  }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
  world.updateMousePosition((x + windowPaddingLeft) * windowScale - SCREEN_WIDTH / 2.f, (y + windowPaddingTop) * windowScale - SCREEN_HEIGHT / 2.f);
}

void Game::setGameState(int state)
{
  //从Menu切换到World可以直接初始化状态
  //从World到Menu的切换是在update过程中切换的，因此要等update完才可以初始化状态
  if (state == PLAYING) { 
    LuaInter::Instance()->initWorld();
  }
  
  gameState = state;
  if (gameState != PLAYING) {
    Menu::Instance()->setState(gameState);
  }
}

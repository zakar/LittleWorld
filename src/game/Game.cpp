#include "Game.h"

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
  setGameState(2);
}

void Game::draw()
{
  world.draw();
}

void Game::update(float time)
{
  world.update(time);
}

void Game::onEvent(Event *event)
{
  if (event->Type == Event::KeyPressed) {
    if (event->Key.Code == Key::Left) {
      world.dispatch(ON_KEY_LEFT_DOWN);
    } else

    if (event->Key.Code == Key::Right) {
      world.dispatch(ON_KEY_RIGHT_DOWN);
    } else

    if (event->Key.Code == Key::Down) {
      world.dispatch(ON_KEY_DOWN_DOWN);
    } else

    if (event->Key.Code == Key::Up) {
      world.dispatch(ON_KEY_UP_DOWN);
    } else

    if (event->Key.Code == Key::I) {
      Camera::Instance()->rotateCamera(1.0, 0.0);
    } else

    if (event->Key.Code == Key::K) {
      Camera::Instance()->rotateCamera(-1.0, 0.0);
    } else

    if (event->Key.Code == Key::J) {
      Camera::Instance()->rotateCamera(0.0, 1.0);
    } else

    if (event->Key.Code == Key::L) {
      Camera::Instance()->rotateCamera(0.0, -1.0);
    }
  }

  // RESIZE
  if (event->Type == Event::Resized)
    {
      world.dispatch(Notifications::ON_WINDOW_RESIZED);

      if ((float)event->Size.Width / (float)event->Size.Height > SCREEN_WIDTH / SCREEN_HEIGHT)
        {
	  windowScale = SCREEN_HEIGHT / event->Size.Height;
        }
      else
        {
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
  if (state == 2) {
    LuaInter::Instance()->initWorld();
  } else if (state == 3) {
    world.clearAll();
  }
  
  gameState = state;
}

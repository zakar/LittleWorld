#include "Game.h"

using namespace std;
using namespace sf;

Game::Game()
{
  windowScale       = 1.f;
  windowPaddingLeft = 0.f;
  windowPaddingTop  = 0.f;
}

void Game::init()
{
  lua.init(&world);
  lua.addEntity();

  for (unsigned int x(0); x < WORLD_WIDTH / 128; x ++)
    {
      for (unsigned int y(0); y < WORLD_HEIGHT / 128; y ++)
        {
  	  world.addFloorDecor(x * 128.f, y * 128.f);
        }
    }

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
  // MOUSE
  if (event->Type == Event::MouseButtonPressed) {
    if (event->MouseButton.Button == Mouse::Left) {
      world.dispatch(Notifications::ON_MOUSE_LEFT_DOWN);
    }
  }

  if (event->Type == Event::KeyPressed) {
    if (event->Key.Code == Key::Left) {
      world.dispatch(Notifications::ON_KEY_LEFT_DOWN);
    }

    if (event->Key.Code == Key::Right) {
      world.dispatch(Notifications::ON_KEY_RIGHT_DOWN);
    }

    if (event->Key.Code == Key::Down) {
      world.dispatch(Notifications::ON_KEY_DOWN_DOWN);
    }

    if (event->Key.Code == Key::Up) {
      world.dispatch(Notifications::ON_KEY_UP_DOWN);
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


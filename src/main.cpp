/************************************
*
* Author: vincent.cogne@gmail.com
*
************************************/

#include "game/Game.h"
#include "game/Application.h"
#include "resources/Conf.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include <unistd.h>

using namespace sf;

float frameCount = 0.f;
float FPS = 60.0;

void setupWindow(float width, float height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > SCREEN_WIDTH / SCREEN_HEIGHT)
    {
        // TODO compute back and front clip plane better
        space = abs(((SCREEN_HEIGHT / (height / width)) - SCREEN_WIDTH) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f - space,
            SCREEN_WIDTH / 2.f + space,
            SCREEN_HEIGHT / -2.f,
            SCREEN_HEIGHT / 2.f,
            SCREEN_HEIGHT * (SCREEN_HEIGHT / height) * -1,
            SCREEN_HEIGHT
        );
    }
    else
    {
        space = abs(((SCREEN_WIDTH / (width / height)) - SCREEN_HEIGHT) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f,
            SCREEN_WIDTH / 2.f,
            SCREEN_HEIGHT / -2.f - space,
            SCREEN_HEIGHT / 2.f + space,
            SCREEN_HEIGHT * (SCREEN_WIDTH / width) * -1.f,
            SCREEN_HEIGHT
        );
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onWindowResized(float width, float height)
{
    setupWindow(width, height);
}

int main()
{
    Application::Instance()->Init();

    // Setup window
    setupWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Gather a pointer to the input system
    const Input& input = Application::Instance()->GetInput();

    // Create a clocks for measuring the time elapsed
    Clock gameClock;
    Clock clock;

    // Create the game object
    Game::Instance()->init();

    // Start game loop
    while (Application::Instance()->IsOpened())
    {
        // Give the game mouse screen related's position
      Game::Instance()->setMousePosition(input.GetMouseX(), input.GetMouseY());

        // Process events
        Event event;
        while (Application::Instance()->GetEvent(event))
        {
            // Close window : exit
            if (event.Type == Event::KeyPressed && event.Key.Code == Key::Escape)
            {
                Application::Instance()->Close();
            }

            switch (event.Type)
            {
                case Event::Closed:
		  Application::Instance()->Close();
                    break;

                case Event::Resized:
   		    Game::Instance()->onEvent(&event);
                    onWindowResized(event.Size.Width, event.Size.Height);
                    break;

                case Event::KeyPressed:
		    Game::Instance()->onEvent(&event);

                // case Event::MouseButtonPressed:
                // case Event::LostFocus:
                // case Event::GainedFocus:
                // case Event::TextEntered:
                // case Event::KeyReleased:
                // case Event::MouseWheelMoved:
                // case Event::MouseButtonReleased:
                // case Event::MouseMoved:
                // case Event::MouseEntered:
                // case Event::MouseLeft:
                // case Event::JoyButtonPressed:
                // case Event::JoyButtonReleased:
                // case Event::JoyMoved:
                // case Event::Count:
                //     break;
            }
        }

	if (gameClock.GetElapsedTime() > 1.0/FPS) {

	  //Update
	  Game::Instance()->update(gameClock.GetElapsedTime());
	  gameClock.Reset();

	  // Framerate
	  frameCount ++;
	  if (clock.GetElapsedTime() >= 1.f) {
	    std::cout << "Framerate: " << (frameCount * clock.GetElapsedTime()) << " FPS" << std::endl;
	    frameCount = 0;
	    clock.Reset();
	  }

	  //Draw...
	  Game::Instance()->draw();

	  // Finally, display the rendered frame on screen
	  Application::Instance()->Display();
	}
	usleep((unsigned int)(100000 * 1.0/FPS));
    }

    return EXIT_SUCCESS;
}










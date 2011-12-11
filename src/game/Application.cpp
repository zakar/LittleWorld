#include "Application.h"
#include "../resources/Conf.h"

Application::Application()
{
  Settings = new sf::WindowSettings();
  Settings->AntialiasingLevel = 4;
  Settings->StencilBits = 8;

  application = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", (sf::Style::Close | sf::Style::Resize), *Settings);
  application->PreserveOpenGLStates(true);
  application->UseVerticalSync(false);
  application->SetFramerateLimit(0);
}

void Application::Init() {
    // Setup rendering
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_FRONT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Default values
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Clear values
    glClearDepth(GL_ONE);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}

Application* Application::Instance()
{
  static Application *ins = new Application();
  return ins;
}

Application::~Application()
{
  delete Settings;
  delete application;
}

void Application::Display()
{
  application->Display();
}

void Application::Draw(sf::Sprite &sprite)
{
  application->Draw(sprite);
}

bool Application::IsOpened()
{
  return application->IsOpened();
}

bool Application::GetEvent(sf::Event &event)
{
  return application->GetEvent(event);
}

void Application::Close()
{
  application->Close();
}

const sf::Input& Application::GetInput()
{
  return application->GetInput();
}

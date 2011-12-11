#ifndef __DEF_RENDERER__
#define __DEF_RENDERER__

#include <SFML/Graphics.hpp>

class Application
{
 public:
  static Application* Instance();
  ~Application();
  void Init();
  void Display();
  void Draw(sf::Sprite &sprite);
  bool IsOpened();
  bool GetEvent(sf::Event &event);
  void Close();
  const sf::Input& GetInput();
 private:
  Application();
  sf::WindowSettings *Settings;
  sf::RenderWindow *application;
};

#endif

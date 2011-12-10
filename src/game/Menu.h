#ifndef __DEF_MENU__
#define __DEF_MENU__

class Menu
{
 public:
  static Menu* Instance();
  void draw();
  void dispatch(unsigned const int type);
  void setState(int state);
  
 private:
  Menu();
  int state; //1, 3

  int backgroundTexId;
  int buttonTexId[2];
};

#endif

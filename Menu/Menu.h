#ifndef MENU_H
#define MENU_H 1

#include <iostream>
#include <string>
#include <iomanip>
#include "../Canvas/Canvas.h"

using namespace std;

class Menu{
  private:

  public:
    static void printMenu();
    static bool startGame();
    static bool quit();

    Menu();
    ~Menu();
};
#endif

#ifndef MENU_H
#define MENU_H 1

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "../Canvas/Canvas.h"

using namespace std;

class Menu{
  private:

  public:
    static bool startGame();
    static bool quit();
    static void clearSave();
    static void readSave();
    static void writeSave();
    static bool runAgain();
    static bool checkWin();

    static bool checking;

    Menu();
    ~Menu();
};
#endif

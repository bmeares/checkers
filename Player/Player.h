
#ifndef PLAYER_H
#define PLAYER_H 1

#include <iostream>
#include <string>

using namespace std;

class Player{
  private:
    static string choice;

  public:

    static bool yesOrNo();
    static void readSave(fstream&);
    static void writeSave(fstream&);
    static void clearSave();

    Player();
    ~Player();
};
#endif

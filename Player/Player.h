
#ifndef PLAYER_H
#define PLAYER_H 1

#include <iostream>
#include <string>
#include <vector>
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

class Player{
  private:
    static string choice;

  public:

    static bool yesOrNo();
    static void clearSave();
    static void turn();
    static void chooseMove(Square&, vector<Square>);
    static Square& select();

    Player();
    ~Player();
};
#endif

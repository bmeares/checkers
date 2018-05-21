
#ifndef AI_H
#define AI_H 1

#include <iostream>
#include <string>
#include <vector>
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

class AI{
  private:
    static string choice;

  public:

    static void turn();
    static void chooseMove(Square&, vector<Square>);
    static Square& select();

    AI();
    ~AI();
};
#endif

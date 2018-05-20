#ifndef MECHANICS_H
#define MECHANICS_H 1

#include <iostream>
#include <string>
#include <iomanip>
#include "../Player/Player.h"
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

namespace Mechanics{

  void playerTurn();
  bool gameState();
  void findPossibleMoves(Square&);

}

#endif

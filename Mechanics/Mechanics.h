#ifndef MECHANICS_H
#define MECHANICS_H 1

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "../Player/Player.h"
#include "../Player/AI.h"
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

namespace Mechanics{

  bool gameState();
  bool runAgain();
  vector<Square> findPossibleMoves(Square&, string);
  vector<Square> findKingMoves(Square&, string);
  vector<Square> fillKingAvail(Square&, int, int, string, int);
  bool hasMoves(vector<Square>&);
  void move(Square&, vector<Square>, string, int);

  void readSave(fstream&);
  void writeSave(fstream&);
  void clearSave();

  bool jumpTests(string, Square&, int, int, int, string, bool);
  bool canJumpL(bool, bool, bool, bool);
  bool canJumpR(bool, bool, bool, bool);
  bool hasKing(string, vector<Square>, int);
  bool atOneFromEdge(int);
  bool atEdge(int);
  void resetJumpSqrs();
  void fixOptionLabels(vector<Square>);

  extern vector<Square> JumpSqrs;
//  extern Square JumpedSqr;

}

#endif

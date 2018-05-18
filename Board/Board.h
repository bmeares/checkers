#ifndef BOARD_H
#define BOARD_H 1

#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include "../pieces/Piece.h"
#include "Square.h"
#include "../Canvas/Canvas.h"

//#include <iomanip>

using namespace std;
using matrix = vector<vector<Square>>;

class Board{
  private:
    static matrix grid;


  public:

    static matrix Grid(){return grid;}
    static void populate();
    static Square& selectSquare(bool);

    Board();
    ~Board();
};
#endif

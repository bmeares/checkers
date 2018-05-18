#include "Mechanics.h"

void Mechanics::playerTurn(){
  Square sqr = Board::selectSquare();
  if(sqr.hasPiece())
    cout << "This square has a piece." << endl;
  else
    cout << "This square does not have a piece." << endl;
}

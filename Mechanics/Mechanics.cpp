#include "Mechanics.h"

bool Mechanics::gameState(){
  Canvas::clearScreen();
  Canvas::drawBoard();
  playerTurn();

  cout << "Run again? ";

  return Player::yesOrNo();

}

void Mechanics::playerTurn(){
  cout << "Select which piece to move.\n" << endl;
  Square fromSqr = Board::selectSquare(true);
//  fromSqr.setPieceColor("selected");
  Canvas::drawBoard();
  cout << "Select which square to move to:\n" << endl;
  Square toSqr = Board::selectSquare(false);
}

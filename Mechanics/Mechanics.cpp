#include "Mechanics.h"

bool Mechanics::gameState(){
  Canvas::clearScreen();
  Canvas::drawBoard();
  playerTurn();

  cout << "Run again? ";

  bool runagain = Player::yesOrNo();
  if(runagain){
    Board::populate();
    Canvas::drawBoard();
  }
  return runagain;
}

void Mechanics::playerTurn(){
  cout << "Select which piece to move.\n" << endl;
  Square fromSqr = Board::selectFromSquare();
  fromSqr.setPieceColor("selected");
  Canvas::drawBoard();
//  cout << "Select which square to move to:\n" << endl;
//  Square toSqr = Board::selectToSquare();
  findPossibleMoves(fromSqr);
}

void Mechanics::findPossibleMoves(Square& fromSqr){

  //TODO finish

//  cout << "inside findPossibleMoves(). Calling loops!" << endl;
//  cout << "fromSqr row is " << fromSqr.getRow() << endl;

  bool isWhite = false;
  bool hasPiece = false;
  bool withinColRange = false;
  int rowAbove = fromSqr.getRow() - 1;
  int option = 1;
//  int colLeft = fromSqr.getCol() - 1;
//  int colRight = fromSqr.getCol() + 1;
 //  bool nearPiece = false;

  for(int i = 0; i < 8; i++){

    isWhite = (Board::Grid().at(rowAbove).at(i).getColor()
      == "white");
    hasPiece = (Board::Grid().at(rowAbove).at(i).hasPiece());
    withinColRange = ((Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == 1) || (Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == -1));

    // cout << "test: " << Board::Grid().at(5).at(0).getCol() << endl;
    // cin.ignore();

        // cout << "dif is " << Board::Grid().at(fromSqr.getRow() - 1).at(i).getRow()
        //   - fromSqr.getRow() << endl;

      // cout << "fromSqr row is " << fromSqr.getRow() << endl;
      // cout << "Board::Grid().at(fromSqr.getRow() - 1).at(i).getRow() is " << Board::Grid().at(fromSqr.getRow() - 1).at(i).getRow() << endl;
      // cin.ignore();

    if(isWhite && !hasPiece && withinColRange){
      Board::Grid().at(rowAbove).at(i).setPieceColor("des");
      Board::Grid().at(rowAbove).at(i).setPieceOption(option);
      option++;
      // cout << "Found a move!!!" << endl;
      // cin.clear();
      // cin.ignore();
    }
  }


  Canvas::drawBoard();
}

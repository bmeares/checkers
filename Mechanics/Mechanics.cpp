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
  vector<Square> availMoves = findPossibleMoves(fromSqr);
  chooseMove(fromSqr, availMoves);
  Canvas::drawBoard();

}

vector<Square> Mechanics::findPossibleMoves(Square& fromSqr){

  //TODO finish

  bool isWhite = false;
  bool hasPiece = false;
  bool withinColRange = false;
  int rowAbove = fromSqr.getRow() - 1;
  int option = 1;
  vector<Square> availMoves;
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

    if(isWhite && !hasPiece && withinColRange){
      Board::Grid().at(rowAbove).at(i).setPieceColor("des");
      Board::Grid().at(rowAbove).at(i).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowAbove).at(i));
      option++;
    }
  }


  Canvas::drawBoard();
  return availMoves;
}

void Mechanics::chooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  cout << "Choose which move you would like to make (number): ";
  cin >> option;
//  cout << "availMoves.at(" << option - 1 << ").getPieceOption() = " << availMoves.at(option - 1).getPieceOption() << endl;

  /* Switch choice and selection */
  int fromRow = fromSqr.getRow();
  int fromCol = fromSqr.getCol();
  Square toSqr = availMoves.at(option - 1);
//  Square tempSqr = fromSqr;
  int choiceRow = availMoves.at(option - 1).getRow();
  int choiceCol = availMoves.at(option - 1).getCol();
  Board::Grid().at(choiceRow).at(choiceCol) = fromSqr;

  /* Set old selection to empty square */
//  Board::Grid().at(fromRow).at(fromCol) = toSqr;
  Board::Grid().at(fromRow).at(fromCol).setPieceColor("");
  Board::Grid().at(fromRow).at(fromCol).setPieceStatus(false);
  Board::Grid().at(fromRow).at(fromCol).setColor("white");

}

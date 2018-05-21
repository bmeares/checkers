#include "Mechanics.h"

bool Mechanics::gameState(){
  Canvas::clearScreen();
  Canvas::drawBoard();
  bool playing = true;

  while(playing){
    Player::turn();
    AI::turn();
  }

  return runAgain();
}

vector<Square> Mechanics::findPossibleMoves(Square& fromSqr, string player){

  bool isWhite = false;
  bool hasPiece = false;
  bool withinColRange = false;
  bool jumpL = false;
  bool jumpR = false;
  int rowAbove = 0;
  int rowTwoAbove = 0;
  int option = 1;
  vector<Square> availMoves;

  if(player == "player"){
    rowAbove = fromSqr.getRow() - 1;
    rowTwoAbove = fromSqr.getRow() - 2;
  }
  else if(player == "ai"){
    rowAbove = fromSqr.getRow() + 1;
    rowTwoAbove = fromSqr.getRow() + 2;
  }

  for(int i = 0; i < 8; i++){

    isWhite = (Board::Grid().at(rowAbove).at(i).getColor()
      == "white");
    hasPiece = (Board::Grid().at(rowAbove).at(i).hasPiece());
    withinColRange = ((Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == 1) || (Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == -1));
    jumpL = jumpTests("left", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);
    jumpR = jumpTests("right", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);

    if(isWhite && !hasPiece && withinColRange){
      Board::Grid().at(rowAbove).at(i).setPieceDes(true);
      Board::Grid().at(rowAbove).at(i).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowAbove).at(i));
      option++;
    }
    if(jumpL){
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i - 1));
      option++;
    }
    if(jumpR){
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i + 1));
      option++;
    }


  }

  Canvas::drawBoard();
  return availMoves;
}

bool Mechanics::canJumpL(bool whiteSqr, bool negOneColAway, bool twoColAwayOpen, bool negOneColAwayOpponent){

  bool canJumpLeft = false;

  if( whiteSqr && negOneColAway && twoColAwayOpen && negOneColAwayOpponent)
  {
    canJumpLeft = true;
  }

  return canJumpLeft;
}

bool Mechanics::canJumpR(bool whiteSqr, bool oneColAway, bool twoColAwayOpen, bool oneColAwayOpponent){
  bool canJumpRight = false;

  if( whiteSqr && oneColAway && twoColAwayOpen && oneColAwayOpponent)
  {
    canJumpRight = true;
  }

  return canJumpRight;
}

bool Mechanics::jumpTests(string side, Square& fromSqr, int rowAbove, int rowTwoAbove, int i, string player, bool withinColRange){
  bool opposite = false;
  bool whiteSqr = false;
  bool oneColAway = false;
  bool oneColAwayOpponent = false;
  bool negOneColAway = false;
  bool negOneColAwayOpponent = false;
  bool twoColAwayOpen = false;
  bool jump = false;

  if((player == "player" && Board::Grid().at(rowAbove).at(i).getPieceColor() == "black")
  || (player == "ai" && Board::Grid().at(rowAbove).at(i).getPieceColor() == "white"))
    opposite = true;
  whiteSqr = (Board::Grid().at(rowAbove).at(i).getColor() == "white");
  oneColAway = (Board::Grid().at(rowAbove).at(i).getCol() - fromSqr.getCol() == 1);
  negOneColAway = (Board::Grid().at(rowAbove).at(i).getCol() - fromSqr.getCol() == -1);

  if(oneColAway){
    twoColAwayOpen = !(Board::Grid().at(rowTwoAbove).at(i - 1).hasPiece());
    oneColAwayOpponent = Board::Grid().at(rowAbove).at(i).hasPiece() && opposite;
  }

  if(negOneColAway && fromSqr.getCol() > 1){
    twoColAwayOpen = !(Board::Grid().at(rowTwoAbove).at(i - 1).hasPiece());
    negOneColAwayOpponent = Board::Grid().at(rowAbove).at(i).hasPiece() && opposite;
  }

  if(side == "left")
    jump = canJumpL(whiteSqr, negOneColAway, twoColAwayOpen, negOneColAwayOpponent);
  if(side == "right")
    jump = canJumpR(whiteSqr, oneColAway, twoColAwayOpen, oneColAwayOpponent);

  return jump;
}


bool Mechanics::hasMoves(vector<Square>& availMoves){
  bool hasMoves = false;
  if(availMoves.size() > 0)
    hasMoves = true;
  else
    hasMoves = false;
  return hasMoves;
}

void Mechanics::move(Square& fromSqr, vector<Square> availMoves, string color, int option){
  int fromRow = fromSqr.getRow();
  int fromCol = fromSqr.getCol();
  Square toSqr = availMoves.at(option - 1);
  int choiceRow = availMoves.at(option - 1).getRow();
  int choiceCol = availMoves.at(option - 1).getCol();

  int optionRow;
  int optionCol;

  for(uint i = 0; i < availMoves.size(); i++){
    optionRow = availMoves.at(i).getRow();
    optionCol = availMoves.at(i).getCol();
    Board::Grid().at(optionRow).at(optionCol).setPieceDes(false);
    Board::Grid().at(optionRow).at(optionCol).setPieceSelected(false);
    Board::Grid().at(optionRow).at(optionCol).setPieceStatus(false);
    Board::Grid().at(optionRow).at(optionCol).setColor("white");
  }

  Board::Grid().at(fromRow).at(fromCol).setPieceSelected(false);
  Board::Grid().at(fromRow).at(fromCol).setPieceDes(false);
  Board::Grid().at(fromRow).at(fromCol).setPieceStatus(false);
  Board::Grid().at(fromRow).at(fromCol).setColor("white");

  // fromSqr.setPieceColor(color);
  // fromSqr.setPieceStatus(true);
  // fromSqr.setPieceSelected(false);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceColor(color);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceStatus(true);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceSelected(false);

}

bool Mechanics::runAgain(){
  cout << "Run again? ";
  bool runagain = Player::yesOrNo();
  if(runagain){
    Board::populate();
    Canvas::drawBoard();
  }
  return runagain;
}

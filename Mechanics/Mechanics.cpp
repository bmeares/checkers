#include "Mechanics.h"

bool Mechanics::gameState(){
  Canvas::clearScreen();
  Canvas::drawBoard();
  bool playing = true;
  fstream save;

  while(playing){

//    readSave(save);

    if(Canvas::playing == "P1"){
      Player::turn();
      clearSave();
      save.open("board.save", fstream::in | fstream::out | std::ios_base::app);
      writeSave(save);
      save.close();
    }

    if(Canvas::playing == "P2"){
      AI::turn();
      clearSave();
      save.open("board.save", fstream::in | fstream::out | std::ios_base::app);
      writeSave(save);
      save.close();
    }


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
  bool oneFromEdge = false;
  bool onEdge = false;

  if(player == "player"){
    rowAbove = fromSqr.getRow() - 1;
    rowTwoAbove = fromSqr.getRow() - 2;
  }
  else if(player == "ai"){
    rowAbove = fromSqr.getRow() + 1;
    rowTwoAbove = fromSqr.getRow() + 2;
  }

  oneFromEdge = atOneFromEdge(rowTwoAbove);
  onEdge = atEdge(rowAbove);

  for(int i = 0; i < 8; i++){

    isWhite = (Board::Grid().at(rowAbove).at(i).getColor()
      == "white");
    hasPiece = (Board::Grid().at(rowAbove).at(i).hasPiece());
    withinColRange = ((Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == 1) || (Board::Grid().at(rowAbove).at(i).getCol()
     - fromSqr.getCol() == -1));
    jumpL = jumpTests("left", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);
    jumpR = jumpTests("right", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);

    if(isWhite && !hasPiece && withinColRange && !onEdge){
      Board::Grid().at(rowAbove).at(i).setPieceDes(true);
      Board::Grid().at(rowAbove).at(i).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowAbove).at(i));
      option++;
    }
    if(jumpL && !oneFromEdge){
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceOption(option);
      Board::Grid().at(rowTwoAbove).at(i - 1).setJumpStatus(true);
      JumpedSqr = Board::Grid().at(rowAbove).at(i);
      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i - 1));
      option++;
    }
    if(jumpR && !oneFromEdge){
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceOption(option);
      Board::Grid().at(rowTwoAbove).at(i + 1).setJumpStatus(true);
      JumpedSqr = Board::Grid().at(rowAbove).at(i);
      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i + 1));
      option++;
    }


  }

  Canvas::drawBoard();
  return availMoves;
}

Square Mechanics::JumpedSqr;

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
    twoColAwayOpen = !(Board::Grid().at(rowTwoAbove).at(i + 1).hasPiece());
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
  int jumpedRow = JumpedSqr.getRow();
  int jumpedCol = JumpedSqr.getCol();

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

  Board::Grid().at(choiceRow).at(choiceCol).setPieceColor(color);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceStatus(true);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceSelected(false);

  if(Board::Grid().at(choiceRow).at(choiceCol).getJumpStatus()){
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceSelected(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceDes(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceStatus(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceSelected(false);
  }

  if(hasKing(color, availMoves, option)){ //TODO
    cout << "has king" << endl;
    cin.ignore();
  }
}

bool Mechanics::hasKing(string color, vector<Square> availMoves, int option){
  int choiceRow = availMoves.at(option - 1).getRow();
//  int choiceCol = availMoves.at(option - 1).getCol();
  bool isKing = false;

  if(color == "white"){
    if(choiceRow == 0)
      isKing = true;
  }
  if(color == "black"){
    if(choiceRow == 7)
      isKing = true;
  }

  return isKing;
}

bool Mechanics::atOneFromEdge(int rowTwoAbove){
  return (rowTwoAbove < 1 || rowTwoAbove > 6);
}

bool Mechanics::atEdge(int rowAbove){
  return (rowAbove < 1 || rowAbove > 6);
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

void Mechanics::writeSave(fstream& save){

  bool startData = true;
  bool endData = true;

  save << startData;
  save << "\n";

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      save << Board::Grid().at(i).at(j).hasPiece();
      save << " ";
      save << Board::Grid().at(i).at(j).getColor();
      save << " ";
      save << Board::Grid().at(i).at(j).getPieceColor();
      save << " ";
      save << Board::Grid().at(i).at(j).getPieceOption();
      save << " ";
      save << Board::Grid().at(i).at(j).getPieceSelected();
      save << " ";
      save << Board::Grid().at(i).at(j).getPieceDes();
      save << " ";
      save << Board::Grid().at(i).at(j).getRow();
      save << " ";
      save << Board::Grid().at(i).at(j).getCol();
      save << " ";
      save << Board::Grid().at(i).at(j).getJumpStatus();
      save << " ";
      save << Board::Grid().at(i).at(j).getPieceKing();
      save << " ";
    }
    save << "\n";
  }
  save << JumpedSqr.hasPiece();
  save << " ";
  save << JumpedSqr.getColor();
  save << " ";
  save << JumpedSqr.getPieceColor();
  save << " ";
  save << JumpedSqr.getPieceOption();
  save << " ";
  save << JumpedSqr.getPieceSelected();
  save << " ";
  save << JumpedSqr.getPieceDes();
  save << " ";
  save << JumpedSqr.getRow();
  save << " ";
  save << JumpedSqr.getCol();
  save << " ";
  save << JumpedSqr.getJumpStatus();
  save << " ";
  save << JumpedSqr.getPieceKing();
  save << "\n";

  save << Canvas::playing;
  save << "\n";

  save << endData;
}

void Mechanics::readSave(fstream& save){
  Board::populate();

  bool startData = false;
  save >> startData;

  bool hasPiece = false;
  string color = "";
  string pieceColor = "";
  int option = 0;
  bool selected = false;
  bool des = false;
  int row = 0;
  int col = 0;
  bool jump = false;
  bool king = false;

  if(startData){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        save >> hasPiece;
        Board::Grid().at(i).at(j).setPieceStatus(hasPiece);
        save >> color;
        Board::Grid().at(i).at(j).setColor(color);
        save >> pieceColor;
        Board::Grid().at(i).at(j).setPieceColor(pieceColor);
        save >> option;
        Board::Grid().at(i).at(j).setPieceOption(option);
        save >> selected;
        Board::Grid().at(i).at(j).setPieceSelected(selected);
        save >> des;
        Board::Grid().at(i).at(j).setPieceDes(des);
        save >> row;
        Board::Grid().at(i).at(j).setRow(row);
        save >> col;
        Board::Grid().at(i).at(j).setCol(col);
        save >> jump;
        Board::Grid().at(i).at(j).setJumpStatus(jump);
        save >> king;
        Board::Grid().at(i).at(j).setPieceKing(king);
      }
    }
    save >> hasPiece;
    JumpedSqr.setPieceStatus(hasPiece);
    save >> color;
    JumpedSqr.setColor(color);
    save >> pieceColor;
    JumpedSqr.setPieceColor(pieceColor);
    save >> option;
    JumpedSqr.setPieceOption(option);
    save >> selected;
    JumpedSqr.setPieceSelected(selected);
    save >> des;
    JumpedSqr.setPieceDes(des);
    save >> row;
    JumpedSqr.setRow(row);
    save >> col;
    JumpedSqr.setCol(col);
    save >> jump;
    JumpedSqr.setJumpStatus(jump);
    save >> king;
    JumpedSqr.setPieceKing(king);

    save >> Canvas::playing;

  }
}

void Mechanics::clearSave(){
  ofstream deleteFile;
  deleteFile.open("board.save", std::ofstream::out | std::ofstream::trunc);
  deleteFile.close();
}

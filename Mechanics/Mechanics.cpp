#include "Mechanics.h"

bool Mechanics::gameState(){
  Canvas::clearScreen();
  Canvas::drawBoard();
  bool playing = true;
  fstream save;

  while(playing){

//    readSave(save);

    if(Canvas::playing == "@@"){
      Player::turn();
      clearSave();
      save.open("board.save", fstream::in | fstream::out | std::ios_base::app);
      writeSave(save);
      save.close();
    }

    if(Canvas::playing == "##"){
      AI::turn();
      clearSave();
      save.open("board.save", fstream::in | fstream::out | std::ios_base::app);
      writeSave(save);
      save.close();
    }


  }

  return runAgain();
}

vector<Square> Mechanics::JumpSqrs = {Square(), Square(), Square(), Square()};

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
  bool isKing = false;

  isKing = fromSqr.getPieceKing();

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

    if(!onEdge){

      isWhite = (Board::Grid().at(rowAbove).at(i).getColor()
        == "white");
      hasPiece = (Board::Grid().at(rowAbove).at(i).hasPiece());
      withinColRange = ((Board::Grid().at(rowAbove).at(i).getCol()
       - fromSqr.getCol() == 1) || (Board::Grid().at(rowAbove).at(i).getCol()
       - fromSqr.getCol() == -1));


      jumpL = jumpTests("left", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);
      jumpR = jumpTests("right", fromSqr, rowAbove, rowTwoAbove, i, player, withinColRange);
    }

    if(isWhite && !hasPiece && withinColRange && !onEdge){
      Board::Grid().at(rowAbove).at(i).setPieceDes(true);
      Board::Grid().at(rowAbove).at(i).setPieceOption(option);
      availMoves.push_back(Board::Grid().at(rowAbove).at(i));
      option++;
    }

    if(jumpL && !oneFromEdge && !onEdge){
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i - 1).setPieceOption(option);
      Board::Grid().at(rowTwoAbove).at(i - 1).setJumpStatus(true);

      int j = 0;
      while(JumpSqrs.at(j).getJumpStatus()){
         j++;
      }
      JumpSqrs.at(j) = Board::Grid().at(rowAbove).at(i);
      JumpSqrs.at(j).setJumpStatus(true);
      Board::Grid().at(rowAbove).at(i).setJumpStatus(true);

      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i - 1));
      option++;
    }
    if(jumpR && !oneFromEdge && !onEdge){
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceDes(true);
      Board::Grid().at(rowTwoAbove).at(i + 1).setPieceOption(option);
      Board::Grid().at(rowTwoAbove).at(i + 1).setJumpStatus(true);
      int j = 0;
      while(JumpSqrs.at(j).getJumpStatus()){
         j++;
      }
      JumpSqrs.at(j) = Board::Grid().at(rowAbove).at(i);
      JumpSqrs.at(j).setJumpStatus(true);
      Board::Grid().at(rowAbove).at(i).setJumpStatus(true);

      availMoves.push_back(Board::Grid().at(rowTwoAbove).at(i + 1));
      option++;
    }
  }

  if(isKing){
    availMoves = findKingMoves(fromSqr, player);
  }

  fixOptionLabels(availMoves);

  Canvas::drawBoard();
  return availMoves;
}

vector<Square> Mechanics::findKingMoves(Square& fromSqr, string player){
  bool onBottom = false;
  //bool onefromBottom = false;
  bool onTop = false;
  //bool onefromTop = false;
  //bool isWhite = false;
  //bool hasPiece = false;
  //bool withinColRange = false;
  //bool jumpL = false;
  //bool jumpR = false;
  vector<Square> availMoves;
  int rowAbove = fromSqr.getRow() - 1;
  int rowTwoAbove = fromSqr.getRow() - 2;
  int rowBelow = fromSqr.getRow() + 1;
  int rowTwoBelow = fromSqr.getRow() + 2;
  int singleRow = 0;
  int doubleRow = 0;
//  int option = 1;

  onTop = atEdge(rowAbove);
  onBottom = atEdge(rowBelow);

  //onefromTop = atEdge(rowTwoAbove);
  //onefromBottom = atEdge(rowTwoBelow);

  if(onBottom){
    singleRow = rowAbove;
    doubleRow = rowTwoAbove;
  }
  if(onTop){
    singleRow = rowBelow;
    doubleRow = rowTwoBelow;
  }

  if(onBottom || onTop){
    availMoves = fillKingAvail(fromSqr, singleRow, doubleRow, player, 1);
  }

  else{
    availMoves = fillKingAvail(fromSqr, rowAbove, rowTwoAbove, player, 1);
    vector<Square> availBottom = fillKingAvail(fromSqr, rowBelow, rowTwoBelow, player, availMoves.size());
    availMoves.insert(availMoves.end(),availBottom.begin(), availBottom.end());
  }

  return availMoves;
}

vector<Square> Mechanics::fillKingAvail(Square& fromSqr, int singleRow, int doubleRow, string player, int option){
  bool onBottom = false;
  //bool onefromBottom = false;
  bool onTop = false;
  //bool onefromTop = false;
  bool isWhite = false;
  bool hasPiece = false;
  bool withinColRange = false;
  bool jumpL = false;
  bool jumpR = false;
  vector<Square> availMoves;
  //int rowAbove = fromSqr.getRow() - 1;
  //int rowTwoAbove = fromSqr.getRow() - 2;
  //int rowBelow = fromSqr.getRow() + 1;
  //int rowTwoBelow = fromSqr.getRow() + 2;
//  int singleRow = 0;
//  int doubleRow = 0;
  //int option = 1;

  for(int i = 0; i < 8; i++){
    isWhite = (Board::Grid().at(singleRow).at(i).getColor()
      == "white");
    hasPiece = (Board::Grid().at(singleRow).at(i).hasPiece());
    withinColRange = ((Board::Grid().at(singleRow).at(i).getCol()
     - fromSqr.getCol() == 1) || (Board::Grid().at(singleRow).at(i).getCol()
     - fromSqr.getCol() == -1));

    if(!onBottom && !onTop){
     jumpL = Mechanics::jumpTests("left", fromSqr, singleRow, doubleRow, i, player, withinColRange);
     jumpR = Mechanics::jumpTests("right", fromSqr, singleRow, doubleRow, i, player, withinColRange);
    }

     if(isWhite && !hasPiece && withinColRange){
       Board::Grid().at(singleRow).at(i).setPieceDes(true);
       Board::Grid().at(singleRow).at(i).setPieceOption(option);
       availMoves.push_back(Board::Grid().at(singleRow).at(i));
       option++;
     }
     if(jumpL){
       Board::Grid().at(doubleRow).at(i - 1).setPieceDes(true);
       Board::Grid().at(doubleRow).at(i - 1).setPieceOption(option);
       Board::Grid().at(doubleRow).at(i - 1).setJumpStatus(true);

       int j = 0;
       while(JumpSqrs.at(j).getJumpStatus()){
          j++;
       }
       JumpSqrs.at(j) = Board::Grid().at(singleRow).at(i);
       JumpSqrs.at(j).setJumpStatus(true);
       Board::Grid().at(singleRow).at(i).setJumpStatus(true);

       availMoves.push_back(Board::Grid().at(doubleRow).at(i - 1));
       option++;
     }
     if(jumpR){
       Board::Grid().at(doubleRow).at(i + 1).setPieceDes(true);
       Board::Grid().at(doubleRow).at(i + 1).setPieceOption(option);
       Board::Grid().at(doubleRow).at(i + 1).setJumpStatus(true);
       int j = 0;
       while(JumpSqrs.at(j).getJumpStatus()){
          j++;
       }
       JumpSqrs.at(j) = Board::Grid().at(singleRow).at(i);
       JumpSqrs.at(j).setJumpStatus(true);
       Board::Grid().at(singleRow).at(i).setJumpStatus(true);

       availMoves.push_back(Board::Grid().at(doubleRow).at(i + 1));
       option++;
     }
   }
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
  bool oneFromEdge = false;
  bool onEdge = false;

  oneFromEdge = atOneFromEdge(rowTwoAbove);
  onEdge = atEdge(rowAbove);

  cout << "Inside jumpTests! about to call tests..." << endl;

  if(!oneFromEdge && !onEdge){
    if((player == "player" && Board::Grid().at(rowAbove).at(i).getPieceColor() == "black")
    || (player == "ai" && Board::Grid().at(rowAbove).at(i).getPieceColor() == "white"))
      opposite = true;
    whiteSqr = (Board::Grid().at(rowAbove).at(i).getColor() == "white");
    oneColAway = (Board::Grid().at(rowAbove).at(i).getCol() - fromSqr.getCol() == 1);
    negOneColAway = (Board::Grid().at(rowAbove).at(i).getCol() - fromSqr.getCol() == -1);
  }

  if(oneColAway && !oneFromEdge && !onEdge){
    twoColAwayOpen = !(Board::Grid().at(rowTwoAbove).at(i + 1).hasPiece());
    oneColAwayOpponent = Board::Grid().at(rowAbove).at(i).hasPiece() && opposite;
  }

  if(negOneColAway && fromSqr.getCol() > 1 && !oneFromEdge && !onEdge){
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
  int jumpedRow = JumpSqrs.at(option - 1).getRow();
  int jumpedCol = JumpSqrs.at(option - 1).getCol();

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

  /* Reset old space */
  Board::Grid().at(fromRow).at(fromCol).setPieceSelected(false);
  Board::Grid().at(fromRow).at(fromCol).setPieceDes(false);
  Board::Grid().at(fromRow).at(fromCol).setPieceStatus(false);
  Board::Grid().at(fromRow).at(fromCol).setColor("white");

  /* Set new space to fromSqr*/
  Board::Grid().at(choiceRow).at(choiceCol).setPieceColor(color);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceStatus(true);
  Board::Grid().at(choiceRow).at(choiceCol).setPieceSelected(false);
  if(fromSqr.getPieceKing())
    Board::Grid().at(choiceRow).at(choiceCol).setPieceKing(true);

  /* Delete jumped piece */
  if(Board::Grid().at(choiceRow).at(choiceCol).getJumpStatus()){
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceDes(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceStatus(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceSelected(false);
    Board::Grid().at(jumpedRow).at(jumpedCol).setPieceColor("none");
  }

  if(hasKing(color, availMoves, option)){ //TODO
    Board::Grid().at(choiceRow).at(choiceCol).setPieceKing(true);
  }

  resetJumpSqrs();
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
  return (rowTwoAbove < 0 || rowTwoAbove > 7);
}

bool Mechanics::atEdge(int rowAbove){
  return (rowAbove < 0 || rowAbove > 7);
}

void Mechanics::resetJumpSqrs(){
  for(int i = 0; i < 4; i++){
    JumpSqrs.at(i).setJumpStatus(false);
  }
}

void Mechanics::fixOptionLabels(vector<Square> availMoves){
  int option = 1;
  for(uint i = 0; i < availMoves.size(); i++){
    availMoves.at(i).setPieceOption(option);

    int availRow = availMoves.at(i).getRow();
    int availCol = availMoves.at(i).getCol();

    Board::Grid().at(availRow).at(availCol).setPieceOption(option);
    option++;
  }
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

  for(int j = 0; j < 4; j++){
    save << JumpSqrs.at(j).hasPiece();
    save << " ";
    save << JumpSqrs.at(j).getColor();
    save << " ";
    save << JumpSqrs.at(j).getPieceColor();
    save << " ";
    save << JumpSqrs.at(j).getPieceOption();
    save << " ";
    save << JumpSqrs.at(j).getPieceSelected();
    save << " ";
    save << JumpSqrs.at(j).getPieceDes();
    save << " ";
    save << JumpSqrs.at(j).getRow();
    save << " ";
    save << JumpSqrs.at(j).getCol();
    save << " ";
    save << JumpSqrs.at(j).getJumpStatus();
    save << " ";
    save << JumpSqrs.at(j).getPieceKing();
    save << "\n";
  }

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

    for(int j = 0; j < 4; j++){
      save >> hasPiece;
      JumpSqrs.at(j).setPieceStatus(hasPiece);
      save >> color;
      JumpSqrs.at(j).setColor(color);
      save >> pieceColor;
      JumpSqrs.at(j).setPieceColor(pieceColor);
      save >> option;
      JumpSqrs.at(j).setPieceOption(option);
      save >> selected;
      JumpSqrs.at(j).setPieceSelected(selected);
      save >> des;
      JumpSqrs.at(j).setPieceDes(des);
      save >> row;
      JumpSqrs.at(j).setRow(row);
      save >> col;
      JumpSqrs.at(j).setCol(col);
      save >> jump;
      JumpSqrs.at(j).setJumpStatus(jump);
      save >> king;
      JumpSqrs.at(j).setPieceKing(king);
    }

    save >> Canvas::playing;

  }
}

void Mechanics::clearSave(){
  ofstream deleteFile;
  deleteFile.open("board.save", std::ofstream::out | std::ofstream::trunc);
  deleteFile.close();
}

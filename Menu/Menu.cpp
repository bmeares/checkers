#include "Menu.h"

bool Menu::checking = false;

bool Menu::startGame(){
  double version = 0.32;
  int numPlayers = 0;
  bool choosing = true;
  Canvas::clearScreen();
  cout << "\n Welcome to Simple Checkers! You're playing version "
    << fixed << setprecision(2) << version << ".";
  cout << "\n\n How many players? (0, 1, or 2) ";

  while(choosing){
    choosing = false;

    cin >> numPlayers;

    if(numPlayers > 2 || numPlayers < 0 || cin.fail()){
      cout << "\nPlease choose 0, 1, or 2 players." << endl;
      cin.clear();
      cin.ignore();
      choosing = true;
    }

    if(numPlayers == 1){
      AI::singlePlayer = true;
      srand(time(NULL));
    }
    else if(numPlayers == 0){
      Player::noPlayers = true;
      AI::singlePlayer = true;
    }
  }

  Board::populate();
  return true;
}

bool Menu::quit(){
  Canvas::clearScreen();
  cout << "\n Your game has been saved." << endl;
  cout << "\n Quit game? ";

  bool no = Player::yesOrNo();

  if(no)
    exit(1);

  return no;
}

bool Menu::runAgain(){
  cout << " Run again? ";
  bool runagain = Player::yesOrNo();
  if(runagain){
    Board::populate();
    Canvas::drawBoard();
  }
  return runagain;
}

bool Menu::checkWin(){
  bool playing = true;
  bool playerLost = false;
  bool playerHasMoves = true;
  bool aiLost = false;
  bool aiHasMoves = true;
  bool foundMoves = false;

  Square fromSqr;
  vector<Square> availMoves;

  checking = true;

  /* Check if Player has any moves left */
  for(uint i = 0; i < Player::getRemainingSqrs().size(); i++){
    fromSqr = Player::quietSelect(i);
    availMoves = Mechanics::findPossibleMoves(fromSqr, "player");
    Mechanics::resetJumpSqrs();

    if(!Mechanics::hasMoves(availMoves)){
      playerHasMoves = false;
    }
    else{
      playerHasMoves = true;
      foundMoves = true;
    }
 }

  playerHasMoves = foundMoves;

  playerLost = ((Player::getNumPieces() < 1) || !playerHasMoves);

  /* Check if AI has any moves left */
  foundMoves = false;
  for(uint i = 0; i < AI::getRemainingSqrs().size(); i++){
    fromSqr = AI::quietSelect(i);
    availMoves = Mechanics::findPossibleMoves(fromSqr, "ai");
    Mechanics::resetJumpSqrs();

    if(!Mechanics::hasMoves(availMoves)){
      aiHasMoves = false;
    }
    else{
      aiHasMoves = true;
      foundMoves = true;
    }
  }

  aiHasMoves = foundMoves;

  aiLost = ((AI::getNumPieces() < 1)
  || !aiHasMoves);


  if(playerLost){
    Canvas::clearScreen();
    Canvas::clearScreen();
    Canvas::clearScreen();
    cout << "\n GAME OVER\n" << endl;
    cout << " ## wins!\n" << endl;
    playing = Menu::runAgain();
  }
  else if(aiLost){
    Canvas::clearScreen();
    Canvas::clearScreen();
    Canvas::clearScreen();
    cout << "\n GAME OVER\n" << endl;
    cout << " @@ wins!\n" << endl;
    playing = Menu::runAgain();
  }

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      Board::Grid().at(i).at(j).setPieceSelected(false);
      Board::Grid().at(i).at(j).setPieceDes(false);
    }
  }

  checking = false;
  return playing;
}

void Menu::writeSave(){

  bool startData = true;
  bool endData = false;
  bool keepReading = true;
//  bool stopReading = false;

  fstream save;
  save.open("board.save", fstream::in | fstream::out | std::ios_base::app);

  save << startData;
  save << "\n";

  /* Save Board */
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

  /* Save JumpSqrs */
  for(int j = 0; j < 4; j++){
    save << Mechanics::JumpSqrs.at(j).hasPiece();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getColor();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getPieceColor();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getPieceOption();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getPieceSelected();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getPieceDes();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getRow();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getCol();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getJumpStatus();
    save << " ";
    save << Mechanics::JumpSqrs.at(j).getPieceKing();
    save << "\n";
  }

  save << Canvas::playing;
  save << "\n";

  /* Save number of pieces */
  save << Player::getNumPieces();
  save << " ";
  save << AI::getNumPieces();
  save << "\n";

  /* Save AI choices */
  if(AI::getRemainingSqrs().size() < 1)
    keepReading = false;

  save << keepReading;
  save << " ";
  for(uint i = 0; i < AI::getRemainingSqrs().size(); i++){
    save << AI::getRemainingSqrs().at(i).hasPiece();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getColor();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getPieceColor();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getPieceOption();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getPieceSelected();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getPieceDes();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getRow();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getCol();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getJumpStatus();
    save << " ";
    save << AI::getRemainingSqrs().at(i).getPieceKing();
    save << " ";

    if(i == AI::getRemainingSqrs().size() - 1){
      keepReading = false;
    }
    save << keepReading;
    save << " ";
  }
  save << "\n" << endl;

  /* Save Player choices */
  keepReading = true;
  if(Player::getRemainingSqrs().size() < 1)
    keepReading = false;

  save << keepReading;
  save << " ";
  for(uint i = 0; i < Player::getRemainingSqrs().size(); i++){
    save << Player::getRemainingSqrs().at(i).hasPiece();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getColor();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getPieceColor();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getPieceOption();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getPieceSelected();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getPieceDes();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getRow();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getCol();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getJumpStatus();
    save << " ";
    save << Player::getRemainingSqrs().at(i).getPieceKing();
    save << " ";

    if(i == Player::getRemainingSqrs().size() - 1){
      keepReading = false;
    }
    save << keepReading;
    save << " ";
  }

  save << "\n";
  save << "\n";
  save << endData;
  save.close();
}

void Menu::readSave(){
  Board::populate();

  fstream save;
  save.open("board.save", fstream::in | fstream::out | std::ios_base::app);

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
  int playerNumPieces = 0;
  int AINumPieces = 0;
  bool keepReading = false;

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
      Mechanics::JumpSqrs.at(j).setPieceStatus(hasPiece);
      save >> color;
      Mechanics::JumpSqrs.at(j).setColor(color);
      save >> pieceColor;
      Mechanics::JumpSqrs.at(j).setPieceColor(pieceColor);
      save >> option;
      Mechanics::JumpSqrs.at(j).setPieceOption(option);
      save >> selected;
      Mechanics::JumpSqrs.at(j).setPieceSelected(selected);
      save >> des;
      Mechanics::JumpSqrs.at(j).setPieceDes(des);
      save >> row;
      Mechanics::JumpSqrs.at(j).setRow(row);
      save >> col;
      Mechanics::JumpSqrs.at(j).setCol(col);
      save >> jump;
      Mechanics::JumpSqrs.at(j).setJumpStatus(jump);
      save >> king;
      Mechanics::JumpSqrs.at(j).setPieceKing(king);
    }

    save >> Canvas::playing;
    save >> playerNumPieces;
    Player::setNumPieces(playerNumPieces);
    save >> AINumPieces;
    AI::setNumPieces(AINumPieces);

    AI::getRemainingSqrs().resize(0);
    save >> keepReading;
    int i = 0;
    Square tempSqr;
    while(keepReading){
      save >> hasPiece;
      tempSqr.setPieceStatus(hasPiece);
      save >> color;
      tempSqr.setColor(color);
      save >> pieceColor;
      tempSqr.setPieceColor(pieceColor);
      save >> option;
      tempSqr.setPieceOption(option);
      save >> selected;
      tempSqr.setPieceSelected(selected);
      save >> des;
      tempSqr.setPieceDes(des);
      save >> row;
      tempSqr.setRow(row);
      save >> col;
      tempSqr.setCol(col);
      save >> jump;
      tempSqr.setJumpStatus(jump);
      save >> king;
      tempSqr.setPieceKing(king);
      AI::addRemainingSqr(tempSqr);
      save >> keepReading;
      i++;
    }

    Player::getRemainingSqrs().resize(0);
    save >> keepReading;
    i = 0;
    tempSqr = Square();
    while(keepReading){
      save >> hasPiece;
      tempSqr.setPieceStatus(hasPiece);
      save >> color;
      tempSqr.setColor(color);
      save >> pieceColor;
      tempSqr.setPieceColor(pieceColor);
      save >> option;
      tempSqr.setPieceOption(option);
      save >> selected;
      tempSqr.setPieceSelected(selected);
      save >> des;
      tempSqr.setPieceDes(des);
      save >> row;
      tempSqr.setRow(row);
      save >> col;
      tempSqr.setCol(col);
      save >> jump;
      tempSqr.setJumpStatus(jump);
      save >> king;
      tempSqr.setPieceKing(king);
      Player::addRemainingSqr(tempSqr);
      save >> keepReading;
      i++;
    }
  }
  save.close();
}

void Menu::clearSave(){
  ofstream deleteFile;
  deleteFile.open("board.save", std::ofstream::out | std::ofstream::trunc);
  deleteFile.close();
}


Menu::Menu(){}
Menu::~Menu(){}

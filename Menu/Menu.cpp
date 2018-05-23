#include "Menu.h"

bool Menu::startGame(){
  double version = 0.30;
  int numPlayers = 0;
  bool choosing = true;
  Canvas::clearScreen();
  cout << "\n Welcome to Simple Checkers! You're playing version "
    << fixed << setprecision(2) << version << ".";
  cout << "\n\n How many players? (1 or 2) ";

  while(choosing){
    choosing = false;

    cin >> numPlayers;

    if(numPlayers > 2 || numPlayers < 1 || cin.fail()){
      cout << "Please choose 1 or two players." << endl;
      cin.clear();
      cin.ignore();
      choosing = true;
    }

    if(numPlayers == 1){
      AI::singlePlayer = true;
      srand(time(NULL));
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
  cout << "Run again? ";
  bool runagain = Player::yesOrNo();
  if(runagain){
    Board::populate();
    Canvas::drawBoard();
  }
  return runagain;
}

void Menu::writeSave(){

  bool startData = true;
  bool endData = true;

  fstream save;
  save.open("board.save", fstream::in | fstream::out | std::ios_base::app);

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

  save << Player::getNumPieces();
  save << " ";
  save << AI::getNumPieces();

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

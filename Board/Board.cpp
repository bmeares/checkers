#include "Board.h"

matrix Board::grid = {
{Square(false, "white"), Square(false, "black")},
{Square(false, "black")},
{Square(false, "white")}
};

void Board::populate(){

  /*Create empty board*/

  int place = 0;

  grid.resize(8);
  AI::getRemainingSqrs().resize(12);
  Player::getRemainingSqrs().resize(12);

  AI::setNumPieces(12);
  Player::setNumPieces(12);

  for(int i = 0; i < 8; i++){
    grid.at(i).resize(16);

    if( i % 2 == 0){
      place = 0;
      for(int j = 0; j < 8; j++){
        grid.at(i).at(place) = Square(false, "white");
        grid.at(i).at(place).setRow(i);
        grid.at(i).at(place).setCol(place);
        grid.at(i).at(place + 1) = Square(false, "black");
        grid.at(i).at(place + 1).setRow(i);
        grid.at(i).at(place + 1).setCol(place + 1);
        place += 2;
      }
    }

    else{
      place = 0;
      for(int k = 0; k < 8; k++){
        grid.at(i).at(place) = Square(false, "black");
        grid.at(i).at(place).setRow(i);
        grid.at(i).at(place).setCol(place);
        grid.at(i).at(place + 1) = Square(false, "white");
        grid.at(i).at(place + 1).setRow(i);
        grid.at(i).at(place + 1).setCol(place + 1);
        place += 2;
      }
    }
  }

  int k = 0;
  /*Fill board with pieces*/
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 8; j++){
      if(grid.at(i).at(j).getColor() == "white"){
        grid.at(i).at(j).setPiece(Piece("black"));
        grid.at(i).at(j).setPieceStatus(true);
        grid.at(i).at(j).setPieceKing(false);
        grid.at(i).at(j).setJumpStatus(false);
        AI::getRemainingSqrs().at(k) = grid.at(i).at(j);
        k++;
      }
    }
  }
  k = 0;
  for(int i = 5; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(grid.at(i).at(j).getColor() == "white"){
        grid.at(i).at(j).setPiece(Piece("white"));
        grid.at(i).at(j).setPieceStatus(true);
        grid.at(i).at(j).setPieceKing(false);
        grid.at(i).at(j).setJumpStatus(false);
        Player::getRemainingSqrs().at(k) = grid.at(i).at(j);
        k++;
      }
    }
  }

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(!grid.at(i).at(j).hasPiece())
        grid.at(i).at(j).setPieceColor("none");
        grid.at(i).at(j).setPieceKing(false);
        grid.at(i).at(j).setJumpStatus(false);
    }
  }

  Mechanics::resetJumpSqrs();

}

int Board::selectRow(){
  int row;
  bool running = true;

  while(running){

    running = false;
    cout << "Choose a row (number): ";
    cin >> row;

    if(row < 1 || row > 8 || cin.fail()){
      cout << "\nPlease choose a valid row." << endl;
      cout << "Enter any key to choose again." << endl;
      running = true;
      cin.clear();
      cin.ignore();
      cin.ignore();
      Canvas::drawBoard();
    }
  }

  row = (8 - row);

  return row;
}

int Board::selectCol(){
  int col;
  char letter;
  bool running = true;

  while(running){

    running = false;
    cout << "Choose a column (letter): ";
    cin >> letter;

    if(letter == 'q' || letter == 'Q'){
      running = !Menu::quit();
    }

    else if(letter == 'r' || letter == 'R'){
      Board::populate();
      Menu::clearSave();
      Canvas::clearScreen();
      cout << "\n Board has been reset." << endl;
      cout << "\n Press any key to start a new game." << endl;
      cout << " Note that you now have the first move." << endl;
      cin.clear();
      cin.ignore();
      cin.ignore();
      running = true;
    }

    else if(letter == 'l' || letter == 'L'){
      Menu::readSave();
      Canvas::clearScreen();
      cout << "\n Board has been loaded." << endl;
      cout << "\n Press any key to resume the saved game." << endl;
      //cout << " Note that you now have the first move." << endl;
      cin.ignore();
      cin.ignore();
      running = true;
    }

    else if(toupper(letter) < 'A' || toupper(letter) > 'H'){
      cout << "\nPlease choose a valid column." << endl;
      cout << "Enter any key to choose again." << endl;
      running = true;
      cin.clear();
      cin.ignore();
      cin.ignore();
    }

    letter = toupper(letter);
    letter -= 65;
    col = letter;
    Canvas::reset = false;

    if(running)
      Canvas::drawBoard();
  }

  return col;
}

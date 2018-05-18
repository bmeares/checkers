#include "Board.h"

matrix Board::grid = {
{Square(false, "white"), Square(false, "black")},
{Square(false, "black")},
{Square(false, "white")}
};

void Board::populate(){

  /*Create empty board*/

  int place = 0;

  grid.resize(16);

  for(int i = 0; i < 8; i++){
    grid.at(i).resize(16);

    if( i % 2 == 0){
      place = 0;
      for(int j = 0; j < 8; j++){
        grid.at(i).at(place) = Square(false, "white");
        grid.at(i).at(place + 1) = Square(false, "black");
        place += 2;
      }
    }

    else{
      place = 0;
      for(int k = 0; k < 8; k++){
        grid.at(i).at(place) = Square(false, "black");
        grid.at(i).at(place + 1) = Square(false, "white");
        place += 2;
      }
    }
  }

  /*Fill board with pieces*/
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 8; j++){
      if(grid.at(i).at(j).getColor() == "white"){
        grid.at(i).at(j).setPiece(Piece("black"));
        grid.at(i).at(j).setPieceStatus(true);
      }
    }
  }

  for(int i = 5; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(grid.at(i).at(j).getColor() == "white"){
        grid.at(i).at(j).setPiece(Piece("white"));
        grid.at(i).at(j).setPieceStatus(true);
      }
    }
  }

}

Square& Board::selectSquare(bool from){

  char letter;
  int row;
  int col;
  bool selecting = true;

  while(selecting){

    cout << "Choose a column (letter): ";
    cin >> letter;
    cout << "Choose a row (number): ";
    cin >> row;

    row = (8 - row);
    letter = toupper(letter);
    letter -= 65;
    col = letter;

    if(grid.at(row).at(col).getPieceColor() == "white" && from){
      grid.at(row).at(col).setPieceColor("selected");
      selecting = false;
    }

    else{
      Canvas::drawBoard();
      cout << "\n Please choose a square with one of your pieces." << endl;
      cout << " Press Enter to select again." << endl;
      cin.clear();
      cin.ignore();
      cin.ignore();
      Canvas::drawBoard();
    }
  }

  return grid.at(row).at(col);

}

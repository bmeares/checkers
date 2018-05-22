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

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(!grid.at(i).at(j).hasPiece())
        grid.at(i).at(j).setPieceColor("none");
    }
  }

}

// Square& Board::selectFromSquare(){
//
//   bool selecting = true;
//
//   while(selecting){
//
//     col = selectCol();
//     row = selectRow();
//
//     if(grid.at(row).at(col).getPieceColor() == "white" || grid.at(row).at(col).getPieceColor() == "black"){
//       grid.at(row).at(col).setPieceSelected(true);
//       selecting = false;
//     }
//
//     else{
//       Canvas::drawBoard();
//       cout << "\n Please choose a square with one of your pieces." << endl;
//       cout << " Press Enter to select again." << endl;
//       cin.clear();
//       cin.ignore();
//       cin.ignore();
//       Canvas::drawBoard();
//     }
//   }
//
//   return grid.at(row).at(col);
//
// }

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

    if(letter == 'r' || letter == 'R'){
      Board::populate();
      Mechanics::clearSave();
      Canvas::clearScreen();
      cout << "\n Game has been reset." << endl;
      cout << "\n Press any key to start a new game." << endl;
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

    if(running)
      Canvas::drawBoard();
  }

  return col;
}

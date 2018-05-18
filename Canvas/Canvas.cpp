#include "Canvas.h"
using namespace Canvas;

void Canvas::clearScreen(){
  cout << "\033c";
}

void Canvas::drawBoard(){
  clearScreen();
  Board::populate();

  int numLabel = 8;
  char letterLabel = 'A';


  cout << "\n   ";
  for (int i = 0; i < 8; i++){
    cout << letterLabel << " ";
    letterLabel++;
  }
  cout << endl;

  for(int i = 0; i < 8; i++){
    cout << " " << numLabel << " ";
    for(int j = 0; j < 8; j++){
      cout << Board::Grid().at(i).at(j);
    }
    numLabel--;
    cout << endl;
  }
  cout << endl;
}

bool Canvas::gameState(){
  clearScreen();
  drawBoard();
  Mechanics::playerTurn();
//TODO   Board::selectSquare();



  cout << "Run again? ";

  return Player::yesOrNo();

}

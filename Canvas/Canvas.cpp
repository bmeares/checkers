#include "Canvas.h"
using namespace Canvas;

void Canvas::clearScreen(){
  cout << "\033c";
}

void Canvas::drawBoard(){
  clearScreen();
  char label = 'A';
  for(int i = 0; i < 8; i++){
    cout << setw(5) << label;
    label++;
  }
  cout << endl;
}

bool Canvas::gameState(){
  clearScreen();

  cout << "Inside gameState!" << endl;
  cout << "Run again? ";

  return Player::yesOrNo();

}

#include "Canvas.h"
#include <stdlib.h>
using namespace Canvas;

void Canvas::clearScreen(){
//  cout << "\033c";
  system("CLS");
}

void Canvas::drawBoard(){
//  clearScreen();
//  clearScreen();
//  clearScreen();
  clearScreen();
  nowPlaying();

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

void Canvas::chooseAvailableMessage(){
  Canvas::drawBoard();
  cout << "\n Please choose a piece with available moves." << endl;
  cout << "\n Press Enter to choose another piece.";
  cin.clear();
  cin.ignore();
  cin.ignore();
  Canvas::drawBoard();
}

string Canvas::playing = "@@";
bool Canvas::reset = false;

void Canvas::nowPlaying(){
  cout << " ";
  for(int i = 0; i < 19; i++){
    cout << "-";
  }
  cout << "\n | NOW PLAYING: " << playing << " |"<< endl;
  cout << " ";
  for(int i = 0; i < 19; i++){
    cout << "-";
  }
}

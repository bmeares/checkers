#include "Menu.h"

void Menu::printMenu(){
  cout << "Hello World!" << endl;
}

bool Menu::startGame(){
  double version = 0.05;
  Canvas::clearScreen();
  cout << "\n Welcome to Simple Checkers! You're playing version "
    << fixed << setprecision(2) << version << ".";
  cout << "\n\n Enter any key to begin." << endl;
  cin.ignore();
  Board::populate();
  return true;
}




Menu::Menu(){}
Menu::~Menu(){}

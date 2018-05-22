#include "Menu.h"

void Menu::printMenu(){
  cout << "Hello World!" << endl;
}

bool Menu::startGame(){
  double version = 0.20;
  Canvas::clearScreen();
  cout << "\n Welcome to Simple Checkers! You're playing version "
    << fixed << setprecision(2) << version << ".";
  cout << "\n\n Enter any key to begin." << endl;
  cin.ignore();
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


Menu::Menu(){}
Menu::~Menu(){}

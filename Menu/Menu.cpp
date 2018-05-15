#include "Menu.h"

void Menu::printMenu(){
  cout << "Hello World!" << endl;
}

bool Menu::startGame(){
  double version = 0.01;
  Canvas::clearScreen();
  cout << "\n Welcome to Simple Chess! You're playing version "
    << fixed << setprecision(2) << version << ".";
  cout << "\n\n Enter any key to begin." << endl;
  cin.ignore();
  return true;
}




Menu::Menu(){}
Menu::~Menu(){}

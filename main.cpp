#include <iostream>
#include <string>
#include "includes.h"
#include <fstream>


using namespace std;

int main() {

  fstream save;
  save.open("board.save", fstream::in | fstream::out | std::ios_base::app);

  bool running = Menu::startGame();
  //Mechanics::clearSave();
  Mechanics::readSave(save);
  save.close();
  do{

    running = Mechanics::gameState();

  } while (running);


  return 0;
}

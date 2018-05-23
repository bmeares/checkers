#include <iostream>
#include <string>
#include "includes.h"
#include <fstream>


using namespace std;

int main() {

  bool running = Menu::startGame();
  Menu::readSave();
  do{

    running = Mechanics::gameState();

  } while (running);


  return 0;
}

// TODO difficulty
// TODO king jump down left not working, check availMoves and JumpSqrs sync

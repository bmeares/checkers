#include <iostream>
#include <string>
#include "includes.h"
#include <fstream>
//#include <io.h>
//#include <fcntl.h>
//#include <windows.h>


using namespace std;

int main() {
//  _setmode(_fileno(stdout), _O_U16TEXT);
//  SetConsoleOutputCP(65001);
//_setmode(_fileno(stdout), _O_U16TEXT);

  bool running = Menu::startGame();
  Menu::readSave();
  do{

    running = Mechanics::gameState();

  } while (running);


  return 0;
}

// TODO difficulty
// TODO king jump down left not working, check availMoves and JumpSqrs sync

#include <iostream>
#include <string>
#include "includes.h"


using namespace std;

int main() {

  bool running = Menu::startGame();
  do{

    running = Canvas::gameState();

  } while (running);


  return 0;
}

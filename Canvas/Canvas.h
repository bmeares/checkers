#ifndef CANVAS_H
#define CANVAS_H 1

#include <iostream>
#include <string>
#include <iomanip>
#include "../Player/Player.h"
#include "../Board/Board.h"
#include "../Mechanics/Mechanics.h"

using namespace std;

namespace Canvas{

    void clearScreen();
    void drawBoard();
    void chooseAvailableMessage();
    void nowPlaying();

    extern string playing;

}
#endif


#ifndef AI_H
#define AI_H 1

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

class AI{
  private:
    static string choice;
    static vector<Square> remainingSqrs;
    static int numPieces;

  public:

    static void turn();
    static void chooseMove(Square&, vector<Square>);
    static void randChooseMove(Square&, vector<Square>);
    static Square& select();
    static Square& randSelect();
    static void addSqr(Square&);
    static vector<Square>& getRemainingSqrs(){return remainingSqrs;}
    static void setNumPieces(int n){numPieces = n;}
    static int getNumPieces(){return numPieces;}
    static void decreaseNumPieces(){numPieces--;}
    static int randomInt(int, int);

    static bool singlePlayer;
//    static string difficulty; // TODO

    AI();
    ~AI();
};
#endif

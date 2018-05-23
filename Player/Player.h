
#ifndef PLAYER_H
#define PLAYER_H 1

#include <iostream>
#include <string>
#include <vector>
#include "../Board/Board.h"
#include "../Canvas/Canvas.h"

using namespace std;

class Player{
  private:
    static string choice;
    static vector<Square> remainingSqrs;
    static int numPieces;

  public:

    static bool yesOrNo();
    static void clearSave();
    static void turn();
    static void chooseMove(Square&, vector<Square>);
    static Square& select();
    static void addSqr(Square&);
    static vector<Square>& getRemainingSqrs(){return remainingSqrs;}
    static void setNumPieces(int n){numPieces = n;}
    static int getNumPieces(){return numPieces;}
    static void decreaseNumPieces(){numPieces--;}

    Player();
    ~Player();
};
#endif

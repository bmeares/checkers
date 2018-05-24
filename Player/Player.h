
#ifndef PLAYER_H
#define PLAYER_H 1

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
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
//    static void clearSave();
    static void turn();
    static void chooseMove(Square&, vector<Square>);
    static Square& select();
    static void addSqr(Square&);
    static vector<Square>& getRemainingSqrs(){return remainingSqrs;}
    static void setNumPieces(int n){numPieces = n;}
    static int getNumPieces(){return numPieces;}
    static void decreaseNumPieces(){numPieces--;}

    static Square& randSelect();
    static int randomInt(int, int);
    static void randChooseMove(Square&, vector<Square>);
    static void delRemainingSqr(int, int);
    static void updateRemainingSqr(int, int, int, int);
    static void addRemainingSqr(Square& sqr){remainingSqrs.push_back(sqr);}

    static Square& quietSelect(int);

    static bool noPlayers;

    Player();
    ~Player();
};
#endif

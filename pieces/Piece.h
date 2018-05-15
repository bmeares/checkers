#ifndef PIECE_H
#define PIECE_H 1

#include <iostream>
#include <string>
//#include <iomanip>

using namespace std;

class Piece{
  private:
    char label;
    int x;
    int y;

  public:

    void setLabel(char label){this->label = label;}
    char getLabel(){return label;}
    void setx(int x){this->x = x;}
    int X(){return x;}
    void sety(int y){this->y = y;}
    int Y();

    Piece();
    Piece(int, int, char);
    ~Piece();
};
#endif

#ifndef PIECE_H
#define PIECE_H 1

#include <iostream>
#include <string>
//#include <iomanip>

using namespace std;

class Piece{
  private:
    string color;
    int x;
    int y;
    int option;

  public:

    void setColor(string clr){this->color = clr;}
    string getColor(){return color;}
    void setx(int x){this->x = x;}
    int X(){return x;}
    void sety(int y){this->y = y;}
    int Y();
    void setOption(int o){this->option = o;}
    int getOption(){return this->option;}

    friend ostream& operator<<(ostream&, Piece&);

    Piece();
    Piece(string);
    ~Piece();
};
#endif

#ifndef SQUARE_H
#define SQUARE_H 1

#include <iostream>
#include <string>
#include <vector>
#include "../pieces/Piece.h"
//#include <iomanip>

using namespace std;

class Square{
  private:
    bool pieceStatus;
    string color;
    Piece piece;

  public:

    bool hasPiece(){return pieceStatus;}
    void setPieceStatus(bool status){this->pieceStatus = status;}
    string getColor(){return color;}
    void setPiece(Piece pc){this->piece = pc;}
    void setPieceColor(string clr){this->piece.setColor(clr);}
    string getPieceColor(){return this->piece.getColor();}

    friend ostream& operator<<(ostream&, Square&);
    Square();
    Square(bool, string);

    Square(bool, string, Piece);
    ~Square();
};
#endif

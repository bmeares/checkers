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
    int row;
    int col;
    bool isJump;

  public:

    bool hasPiece(){return pieceStatus;}
    void setPieceStatus(bool status){this->pieceStatus = status;}
    string getColor(){return color;}
    void setColor(string clr){this->color = clr;}
    void setPiece(Piece pc){this->piece = pc;}
    void setPieceColor(string clr){this->piece.setColor(clr);}
    string getPieceColor(){return this->piece.getColor();}
    void setRow(int r){
      this->row = r;
      this->piece.setx(r);}
    int getRow(){return this->row;}
    void setCol(int c){
      this->col = c;
      this->piece.sety(c);}
    int getCol(){return this->col;}
    void setPieceOption(int o){this->piece.setOption(o);}
    int getPieceOption(){return this->piece.getOption();}
    void setPieceSelected(bool s){this->piece.setSelected(s);}
    bool getPieceSelected(){return this->piece.getSelected();}
    void setPieceDes(bool d){this->piece.setDes(d);}
    bool getPieceDes(){return this->piece.getDes();}
    void setJumpStatus(bool j){this->isJump = j;}
    bool getJumpStatus(){return this->isJump;}
    void setPieceKing(bool k){this->piece.setKingStatus(k);}
    bool getPieceKing(){return this->piece.getKingStatus();}

    friend ostream& operator<<(ostream&, Square&);
    Square();
    Square(bool, string);

    Square(bool, string, Piece);
    ~Square();
};
#endif

#include "Piece.h"

Piece::Piece() :  option(1), selected(false), des(false){}
Piece::Piece(string clr) : color(clr), option(1), selected(false), des(false){}
Piece::~Piece(){}

ostream& operator << (ostream& out, Piece& piece) {

  if(piece.des)
    out << "*" << piece.option;

  else if(piece.selected)
    out << "[]";

  else if(piece.color == "white")
    out << "@@";

  else if(piece.color == "black")
    out << "##";


  return out;
}

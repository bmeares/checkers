#include "Piece.h"

Piece::Piece() : selected(false), des(false){}
Piece::Piece(string clr) : color(clr), selected(false), des(false){}
Piece::~Piece(){}

ostream& operator << (ostream& out, Piece& piece) {

  if(piece.des)
    out << "*" << piece.option;

  if(piece.selected)
    out << "[]";

  else if(piece.color == "white")
    out << "@@";

  else if(piece.color == "black")
    out << "##";


  return out;
}

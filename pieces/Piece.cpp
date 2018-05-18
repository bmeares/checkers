#include "Piece.h"

Piece::Piece(){}
Piece::Piece(string clr) : color(clr){}
Piece::~Piece(){}

ostream& operator << (ostream& out, Piece& piece) {

  if(piece.color == "white")
    out << "@@";

  else if(piece.color == "black")
    out << "##";

  else if(piece.color == "selected")
    out << "[]";

  return out;
}

#include "Piece.h"

Piece::Piece(){}
Piece::Piece(string clr) : color(clr){}
Piece::~Piece(){}

ostream& operator << (ostream& out, Piece& piece) {

  if(piece.color == "white")
    out << "@@";

  if(piece.color == "black")
    out << "##";

  if(piece.color == "des"){
    out << " " << piece.option;
  }

  if(piece.color == "selected")
    out << "[]";



  return out;
}

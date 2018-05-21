#include "Square.h"

ostream& operator << (ostream& out, Square& square) {

  if(square.hasPiece() || square.getPieceDes()){
    out << square.piece;
  }
  else{
    if(square.getColor() == "black"){
      out << "\u2588\u2588";
    }
    else if(square.getColor() == "white"){
      out << "  ";
    }


  }

  return out;
}

Square::Square(bool hasPiece, string clr, Piece pc) : pieceStatus(hasPiece),
  color(clr), piece(pc){}

Square::Square(bool hasPiece, string clr) : pieceStatus(hasPiece),
    color(clr){}

Square::Square(){}

Square::~Square(){}

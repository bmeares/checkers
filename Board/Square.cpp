#include "Square.h"
#include <codecvt>
#include <locale>
#include <fcntl.h>
#include <io.h>


ostream& operator << (ostream& out, Square& square) {
  char block = 219;

  if(square.hasPiece() || square.getPieceDes()){
    out << square.piece;
  }
  else{
    if(square.getColor() == "black"){
  //    out << "\u2588\u2588";
        out << block << block;
    }
    else if(square.getColor() == "white"){
      out << "  ";
    }


  }

  return out;
}

Square::Square(bool hasPiece, string clr, Piece pc) : pieceStatus(hasPiece),
  color(clr), piece(pc), isJump(false){}

Square::Square(bool hasPiece, string clr) : pieceStatus(hasPiece),
  color(clr), isJump(false){}

Square::Square() : pieceStatus(false), color("white"), piece(Piece("none")),
  row(0), col(0), isJump(false){}

Square::~Square(){}

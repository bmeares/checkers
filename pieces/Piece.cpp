#include "Piece.h"

Piece::Piece(){}
Piece::Piece(int x, int y, char label){
  this->x = x;
  this->y = y;
  this->label = label;
}
Piece::~Piece(){}

#include "AI.h"

string AI::choice = "";

void AI::turn(){
  Canvas::playing = "##";
  Canvas::drawBoard();
  bool runagain = true;
  Square fromSqr;
  vector<Square> availMoves;

  while(runagain){
    fromSqr = select();
    availMoves = Mechanics::findPossibleMoves(fromSqr, "ai");
    runagain = !(Mechanics::hasMoves(availMoves));

    if(runagain){
      Board::Grid().at(fromSqr.getRow()).at(fromSqr.getCol()).setPieceSelected(false);
      Canvas::chooseAvailableMessage();
      Canvas::drawBoard();
    }
  }

  chooseMove(fromSqr, availMoves);
  Canvas::playing = "@@";

  Canvas::drawBoard();
}

void AI::chooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  cout << "Choose which move you would like to make (number): ";
  cin >> option;
  Mechanics::move(fromSqr, availMoves, "black", option);
}

Square& AI::select(){
  cout << "Select which piece to move," << endl;
  cout << "   or enter q to quit.\n" << endl;
  int col = 0;
  int row = 0;

  bool selecting = true;
  while(selecting){

    col = Board::selectCol();
    row = Board::selectRow();

    if(Board::Grid().at(row).at(col).getPieceColor() == "black"){
      Board::Grid().at(row).at(col).setPieceSelected(true);
      selecting = false;
    }

    else{
      Canvas::drawBoard();
      cout << "\n Please choose a square with one of your pieces." << endl;
      cout << " Press Enter to select again." << endl;
      cin.clear();
      cin.ignore();
      cin.ignore();
      Canvas::drawBoard();
    }
  }

  return Board::Grid().at(row).at(col);
}

AI::AI(){}
AI::~AI(){}

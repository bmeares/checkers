#include "AI.h"

string AI::choice = "";

void AI::turn(){
  Canvas::playing = "Player 2";
  Canvas::drawBoard();
  bool runagain = true;
  Square fromSqr;
  vector<Square> availMoves;

  while(runagain){
    fromSqr = select();
    availMoves = Mechanics::findPossibleMoves(fromSqr, "ai");
    runagain = !(Mechanics::hasMoves(availMoves));

    if(runagain){
      Canvas::chooseAvailableMessage();
      fromSqr.setPieceColor("black");
      Canvas::drawBoard();
    }
  }

  chooseMove(fromSqr, availMoves);
  Canvas::drawBoard();
}

void AI::chooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  cout << "Choose which move you would like to make (number): ";
  cin >> option;
  Mechanics::move(fromSqr, availMoves, "black", option);
}

Square& AI::select(){
  cout << "Select which piece to move.\n" << endl;
  int col = 0;
  int row = 0;

  bool selecting = true;
  while(selecting){

    col = Board::selectCol();
    row = Board::selectRow();

    if(Board::Grid().at(row).at(col).getPieceColor() == "white" || Board::Grid().at(row).at(col).getPieceColor() == "black"){
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
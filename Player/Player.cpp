#include "Player.h"

string Player::choice = "";
vector<Square> Player::remainingSqrs;
int Player::numPieces = 0;

bool Player::yesOrNo(){

  cin >> choice;

  bool intent = false;
  if(choice == "y" || choice == "Yes" || choice == "yes" || choice == "Y"
  || choice == "YES" || choice == "1" || choice == "YASS"){
    intent = true;
  }
  else{
    choice = "";
    intent = false;
  }
  return intent;
}

void Player::turn(){
  Canvas::playing = "@@";
//  Canvas::drawBoard();
  bool runagain = true;
  Square fromSqr;
  vector<Square> availMoves;

  while(runagain){
    fromSqr = select();
    availMoves = Mechanics::findPossibleMoves(fromSqr, "player");

    runagain = !(Mechanics::hasMoves(availMoves));

    if(runagain){
      Board::Grid().at(fromSqr.getRow()).at(fromSqr.getCol()).setPieceSelected(false);
      Canvas::chooseAvailableMessage();
      Canvas::drawBoard();
    }
  }

  chooseMove(fromSqr, availMoves);

  Canvas::playing = "##";

  Canvas::drawBoard();
}

void Player::chooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  bool running = true;

  while(running){
    running = false;
    cout << "Choose which move you would like to make (number): ";
    cin >> option;

    if(option < 1 || static_cast<uint>(option) > availMoves.size()){
      cout << "\nPlease pick a valid move." << endl;
      cout << "Press Enter to pick another move" << endl;
      cin.clear();
      cin.ignore();
      cin.ignore();
      running = true;
      Canvas::drawBoard();
    }
  }

  Mechanics::move(fromSqr, availMoves, "white", option);
}

Square& Player::select(){
  cout << "Select which piece to move," << endl;
  cout << "   or enter q to quit.\n" << endl;

  int col = 0;
  int row = 0;

  bool selecting = true;
  while(selecting){

    col = Board::selectCol();
    row = Board::selectRow();

    if(Board::Grid().at(row).at(col).getPieceColor() == "white" ){
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

void Player::addSqr(Square& sqr){
  remainingSqrs.push_back(sqr);
}

Player::Player(){}
Player::~Player(){}

#include "AI.h"

using namespace std::this_thread;
using namespace std::chrono;


string AI::choice = "";
bool AI::singlePlayer = false;
vector<Square> AI::remainingSqrs;
int AI::numPieces = 0;

void AI::turn(){
  Canvas::playing = "##";
  bool runagain = true;
  Square fromSqr;
  vector<Square> availMoves;

  if(!singlePlayer){
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
  }
  else{
    if(Player::noPlayers)
      sleep_for(nanoseconds(50000000));
    else{
      srand( time(NULL) );
      sleep_for(nanoseconds(400000000));
    }
    while(runagain){
      fromSqr = randSelect();
      availMoves = Mechanics::findPossibleMoves(fromSqr, "ai");
      runagain = !(Mechanics::hasMoves(availMoves));

      if(runagain){
        Board::Grid().at(fromSqr.getRow()).at(fromSqr.getCol()).setPieceSelected(false);
      }
    }
    if(Player::noPlayers){

    }
    else
      sleep_for(nanoseconds(700000000));

    randChooseMove(fromSqr, availMoves);
  }

  Canvas::playing = "@@";

  Canvas::drawBoard();
}

void AI::chooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  bool running = true;

  while(running){
    running = false;
    cout << "Choose which move you would like to make (number): ";
    cin >> option;

    if(option < 1 || static_cast<unsigned int>(option) > availMoves.size()){
      cout << "\nPlease pick a valid move." << endl;
      cout << "Press Enter to pick another move" << endl;
      cin.clear();
      cin.ignore();
      cin.ignore();
      running = true;
      Canvas::drawBoard();
    }
  }

  Mechanics::move(fromSqr, availMoves, "black", option);
}

void AI::randChooseMove(Square& fromSqr, vector<Square> availMoves){
  int option;
  bool running = true;
//  unsigned int randMax = availMoves.size();

  while(running){
    running = false;
    option = randomInt(1, static_cast<int>(availMoves.size()));

    if(option < 1 || static_cast<unsigned int>(option) > availMoves.size()){
      running = true;
//      Canvas::drawBoard();
    }
  }

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

    if(Board::Grid().at(row).at(col).getPieceColor() == "black"
    && Board::Grid().at(row).at(col).hasPiece()){
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

Square& AI::randSelect(){
  int col = 0;
  int row = 0;
  int randMax = remainingSqrs.size();
  int randChoice = 0;

  bool selecting = true;
  while(selecting){

    if(randMax == 0)
      randChoice = 0;
    else
      randChoice = rand() % randMax;

    col = remainingSqrs.at(randChoice).getCol();
    row = remainingSqrs.at(randChoice).getRow();

    if(Board::Grid().at(row).at(col).getPieceColor() == "black"
    && Board::Grid().at(row).at(col).hasPiece()){
      Board::Grid().at(row).at(col).setPieceSelected(true);
      selecting = false;
    }
  }

  return Board::Grid().at(row).at(col);
}

Square& AI::quietSelect(int choice){
  int col = 0;
  int row = 0;

  bool selecting = true;
  while(selecting){

    col = remainingSqrs.at(choice).getCol();
    row = remainingSqrs.at(choice).getRow();

    if(Board::Grid().at(row).at(col).getPieceColor() == "black"
    && Board::Grid().at(row).at(col).hasPiece()){
      Board::Grid().at(row).at(col).setPieceSelected(true);
      selecting = false;
    }
  }

  return Board::Grid().at(row).at(col);
}

void AI::addSqr(Square& sqr){
  remainingSqrs.push_back(sqr);
}

int AI::randomInt(int min, int max){
  return min + rand() % (( max + 1 ) - min);
}

void AI::delRemainingSqr(int jumpedRow, int jumpedCol){
  for(unsigned int i = 0; i < remainingSqrs.size(); i++){
    if(remainingSqrs.at(i).getRow() == jumpedRow
    && remainingSqrs.at(i).getCol() == jumpedCol){
      remainingSqrs.erase(remainingSqrs.begin() + i);
    }
  }
}

void AI::updateRemainingSqr(int fromRow, int fromCol, int choiceRow, int choiceCol){
  for(unsigned int i = 0; i < remainingSqrs.size(); i++){
    if(remainingSqrs.at(i).getRow() == fromRow
    && remainingSqrs.at(i).getCol() == fromCol){
      remainingSqrs.at(i).setRow(choiceRow);
      remainingSqrs.at(i).setCol(choiceCol);
    }
  }
}

AI::AI(){}
AI::~AI(){}

#include "Player.h"

string Player::choice = "";

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

Player::Player(){}
Player::~Player(){}

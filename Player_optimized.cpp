/**********************************

Patrick Saperstein
Battleship
for COBB Tuning
July 8, 2016
Player.cpp

**********************************/

#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <time.h>
using namespace std;
Player::Player(){
     isAI=false;
     aircraftCarrier=5;
     battleship=4;
     submarine=3;
     destroyer=3;
     patrolBoat=2;
     numLiveBoats = 5;
     for(int i=0; i<10; ++i){
          for(int j=0; j<10; j++){
               board[i][j]=' ';
          }
     }
}
Player::Player(const bool &_isAI){
     isAI=_isAI;
     aircraftCarrier=5;
     battleship=4;
     submarine=3;
     destroyer=3;
     patrolBoat=2;
     numLiveBoats = 5;
     for(int i=0; i<10; ++i){
          for(int j=0; j<10; j++){
               board[i][j]=' ';
          }
     }
}

void Player::setAI(bool _isAI){
     isAI=_isAI;
}

bool Player::getAI(){
     return isAI;
}

char Player::boardSquare(int x, int y){
     return board[x][y];
}

void Player::setBoats(){
     if(isAI){
          AISetBoats();
     }
     else{
          PlayerSetBoats();
     }
}

struct Boat {
  const char *name;
  char id;
  int size;
};

Boat boats[] = {
  { "Aircraft Carrier", 'A', 5 },
  { "Battleship", 'B', 4 },
  { "Submarine", 'S', 3 },
  { "Destroyer", 'D', 3 },
  { "Patrol Boat", 'P', 2 },
  { NULL, 0, 0 }
};

//AI Places each Boat
void Player::AISetBoats(){
  int idx=0;
  Boat *boat;
  while (boats[idx].name != NULL) {
    boat = &boats[idx++];
    AISetBoat(boat->id, boat->size);
  }
}

//Player places each boat. I realize I could have optimized this a bit more.
//I could have made a get coords function that would work with this and getTarget
void Player::PlayerSetBoats(){
     char tempx;
     int x, y, d;
     bool valid = false;
     printFriendBoard();
     cout<<"It's time to place your boats."<<endl;

  int idx=0;
  Boat *boat;
  while (boats[idx].name != NULL) {
    boat = &boats[idx];
    cout << "Placing the " << boat->name;
    cout << ", which has a length of " << boat->size << "." << endl;

    x = placeX();
    y = placeY();
    d = placeD();
    valid = checkAndSet(x, y, d, boat->id, boat->size);
    if (valid) {
      ++idx;
    }
  }
}
//The actual setting of the boats. I know this looks kind of ugly and complex too.
void Player::AISetBoat(char type, int size){
     srand(time(NULL));
     bool valid = false;
     int startLoc = rand()%100;
     int direction = rand()%4;
     int x = startLoc/10;
     int y = startLoc%10;
     while(!valid){
          startLoc = rand()%100;
          direction = rand()%4;
          x = startLoc/10;
          y = startLoc%10;
          // 0=Up  1=Right  2=Down  3=Left
          switch (direction){
                 case 0:
                      if(y-size >= 0){     //if piece fits
                           valid=true;
                                                    //if all squares are clear
                           for(int i=0; i<size; i++){
                                                     //each square of the placement
                                if(boardSquare(y-i, x) != ' '){
                                     valid=false;
                                     break;
                                }
                           }
                      }
                      break;
                      
                 case 1:
                      if(x+size <= 10){     //if piece fits
                           valid=true;
                                                    //if all squares are clear
                           for(int i=0; i<size; i++){
                                                     //each square of the placement
                                if(boardSquare(y,x+i) != ' '){
                                     valid=false;
                                     break;
                                }
                           }
                      }
                      break;
                      
                 case 2:
                      if(y+size <= 10 ){     //if piece fits
                           valid=true;
                                                    //if all squares are clear
                           for(int i=0; i<size; i++){
                                                     //each square of the placement
                                if(boardSquare(y+i, x) != ' '){
                                     valid=false;
                                     break;
                                }
                           }
                      }
                      break;
                      
                 case 3:
                      if(x-size >=0){     //if piece fits
                           valid=true;
                                                    //if all squares are clear
                           for(int i=0; i<size; i++){
                                                     //each square of the placement
                                if(boardSquare(y-i, x)!=' '){
                                     valid=false;
                                     break;
                                }
                           }
                      }
                      break;
          }    
     }
     //We know we are clear, we need to fill the spaces
     switch(direction){
          case 0:
               for(int i=0; i<size; ++i){
                    board[y-i][x]=type;
               }
               break;
               
          case 1:
               for(int i=0; i<size; ++i){
                    board[y][x+i]=type;
               }
               break;
               
          case 2:
               for(int i=0; i<size; ++i){
                    board[y+i][x]=type;
               }
               break;
               
          case 3:
               for(int i=0; i<size; ++i){
                    board[y][x-i]=type;
               }
               break;
     }
}
// so you can see your ships.....
void Player::printFriendBoard(){
     cout<<"                    YOUR SHIPS"<<endl;
     cout<<"---------------------------------------------"<<endl;
     cout<<"|   | A | B | C | D | E | F | G | H | I | J |"<<endl;
     cout<<"---------------------------------------------"<<endl;
     for(unsigned i=0; i<10; ++i){
          if(i==9){
               cout<<"| "<<i+1<<"|";
          }else{
               cout<<"| "<<i+1<<" |";
          }
          for(unsigned j=0; j<10; j++) {
               cout<<" ";
               cout<<boardSquare(i,j);
               cout<<" |";
          }
          cout<<endl;
          cout<<"---------------------------------------------"<<endl;
     }
}
// But not the opponent's
void Player::printEnemyBoard(){
     cout<<"                    THE ENEMY"<<endl;
     cout<<"---------------------------------------------"<<endl;
     cout<<"|   | A | B | C | D | E | F | G | H | I | J |"<<endl;
     cout<<"---------------------------------------------"<<endl;
     for(unsigned i=0; i<10; ++i){
          if(i==9){
               cout<<"| "<<i+1<<"|";
          }else{
               cout<<"| "<<i+1<<" |";
          }
          for(unsigned j=0; j<10; j++) {
               char current = boardSquare(i,j);
               cout<<" ";
               if(current=='X' || current=='O'){
                    cout<<current;
               }else{
                    cout<<" ";
               }
               cout<<" |";
          }
          cout<<endl;
          cout<<"---------------------------------------------"<<endl;
     }
}
//conversion function
int Player::letterToNumber(char input){
    char temp=toupper(input);
    switch(temp) {
         case 'A':
              return 0;
         case 'B':
              return 1;
         case 'C':
              return 2;
         case 'D':
              return 3;
         case 'E':
              return 4;
         case 'F':
              return 5;
         case 'G':
              return 6;
         case 'H':
              return 7;
         case 'I':
              return 8;
         case 'J':
              return 9;
         default:
              return -1;
    }
}
//could have used the getCoords function for this too.
int Player::placeX(){
     int x;
     char tempx;
     bool valid=false;
     while (!valid){
          valid=true;
          cout<<"Which column would you like to put one end of it in (A-J)?"<<endl;
          cin>>tempx;
          x = letterToNumber(tempx);
          if(x==-1){
               valid=false;
               cout<<"Please enter a letter between A and J"<<endl;
          }
     }
    return x;
}
//see above
int Player::placeY(){
     char temp;
     int y;
     bool valid = false;
     while (!valid){
          valid=true;
          cout<<"Which row would you like to put one end of it in (1-10)?"<<endl;
          cin>>temp;
          y = temp-'0';
          y=y-1;                     //index shift;
          if(y<0 || y>9){
               valid=false;
               cout<<"Please enter a number between 1 and 10"<<endl;
          }
     }
     return y;
}
//direction of ship during placement
int Player::placeD(){
    char d;
    bool valid= false;
    while (!valid) {
         cout<<"Which direction would you like the ship to go? (U,D,L,R)"<<endl;
         cin>>d;
         d = toupper(d);
         switch(d){
              case 'U':
                   return 0;
              case 'R':
                   return 1;
              case 'D':
                   return 2;
              case 'L':
                   return 3;
         }
         cout<<"Please enter either U, D, L, or R for a direction"<<endl;
    }
}
//checks the ship to see if it's clear to be placed.
//probably could have made a function used by AI and normal players
//since it's the same code
bool Player::checkAndSet(int x, int y, int d, char ship, int size){
     bool valid = false;
     switch (d){
          case 0:
                 if(y-size >= 0){     //if piece fits
                      valid=true;
                                               //if all squares are clear
                      for(int i=0; i<size; i++){
                                                //each square of the placement
                           if(boardSquare(y-i, x) != ' '){
                                valid=false;
                                break;
                           }
                      }
                 }
                 break;
                 
            case 1:
                 if(x+size <= 10){     //if piece fits
                      valid=true;
                                               //if all squares are clear
                      for(int i=0; i<size; i++){
                                                //each square of the placement
                           if(boardSquare(y, x+i) != ' '){
                                valid=false;
                                break;
                           }
                      }
                 }
                 break;
                 
            case 2:
                 if(y+size <= 10 ){     //if piece fits
                      valid=true;
                                               //if all squares are clear
                      for(int i=0; i<size; i++){
                                                //each square of the placement
                           if(boardSquare(y+i, x) != ' '){
                                valid=false;
                                break;
                           }
                      }
                 }
                 break;
                 
            case 3:
                 if(x-size >=0){     //if piece fits
                      valid=true;
                                               //if all squares are clear
                      for(int i=0; i<size; i++){
                                                //each square of the placement
                           if(boardSquare(y, x-i)!=' '){
                                valid=false;
                                break;
                           }
                      }
                 }
                 break;
     }
     //we know we're clear, fill the squares
     if(valid){
        switch(d){
          case 0:
               for(int i=0; i<size; ++i){
                    board[y-i][x]=ship;
               }
               break;
               
          case 1:
               for(int i=0; i<size; ++i){
                    board[y][x+i]=ship;
               }
               break;
               
          case 2:
               for(int i=0; i<size; ++i){
                    board[y+i][x]=ship;
               }
               break;
               
          case 3:
               for(int i=0; i<size; ++i){
                    board[y][x-i]=ship;
               }
               break;
        }
        //if not clear, do it again
     }else{
          cout<<"This ship can't go there. Gonna have to try again.\n"<<endl;
     }
     return valid;
}
//Setting specific squares
void Player::setSquare(int x, int y, char place){
     board[y][x]=place;
}
//acquire next target.
//The other place for the getCoords Function
int Player::getTarget(){
     //srand(time(NULL));
     if(isAI){
         return rand()%100;
     }
     char temp;
     int x, y, result;
     bool valid=false;
     while (!valid){
          valid=true;
          cout<<"Which column would you like to attack (A-J)?"<<endl;
          cin>>temp;
          x = letterToNumber(temp);
          if(x==-1){
               valid=false;
               cout<<"Please enter a letter between A and J"<<endl;
          }
     }
     result=10*x;
     valid=false;
     while (!valid){
          valid=true;
          cout<<"Which row would you like to attack (1-10)?"<<endl;
          cin>>temp;
          y = temp - '0';
          y=y-1;                     //index shift;
          if(y<0 || y>9){
               valid=false;
               cout<<"Please enter a number between 1 and 10"<<endl;
          }
     }
     result+=y;
     return result;
}
//attacking each particular boat, and checking if it sinks
void Player::attackA(){
     aircraftCarrier--;
     if(aircraftCarrier==0){
          cout<<"You sunk the Aircraft Carrier!"<<endl;
          numLiveBoats--;
          cout<<numLiveBoats<<" Boats Left."<<endl;
     }
}
void Player::attackB(){
     battleship--;
     if(battleship==0){
          cout<<"You sunk the Battleship!"<<endl;
          numLiveBoats--;
          cout<<numLiveBoats<<" Boats Left."<<endl;
     }
}
void Player::attackD(){
     destroyer--;
     if(destroyer==0){
          cout<<"You sunk the Destroyer!"<<endl;
          numLiveBoats--;
          cout<<numLiveBoats<<" Boats Left."<<endl;
     }
}
void Player::attackP(){
     patrolBoat--;
     if(patrolBoat==0){
          cout<<"You sunk the Patrol Boat!"<<endl;
          numLiveBoats--;
          cout<<numLiveBoats<<" Boats Left."<<endl;
     }
}
void Player::attackS(){
     submarine--;
     if(submarine==0){
          cout<<"You sunk the Submarine!"<<endl;
          numLiveBoats--;
          cout<<numLiveBoats<<" Boats Left."<<endl;
     }
}
//for checking victory conditions.
int Player::getLives(){
    return numLiveBoats;
}

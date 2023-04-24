/**********************************

Patrick Saperstein
Battleship
for COBB Tuning
July 8, 2016
main.cpp

**********************************/

#include <cstdlib>
#include <iostream>
#include "Player.h"

using namespace std;
void turn(Player &, Player &);
void p1SwitchScreen();
void p2SwitchScreen();


int main(int argc, char *argv[])
{    
    cout<<"Welcome to Battleship!"<<endl;
    cout<<"The game of adventure on the high seas!"<<endl;
    cout<<"Please enter the number of human players (0-2)"<<endl;
    Player player1 = new Player();
    player1.setAI(false);             //Not sure why I have to do it this way
    Player player2 = new Player();
    player2.setAI(false);             //But it's the only way it works properly
    char temp;
    bool valid = false;
    while(!valid){
         cin>>temp;
         if(temp<'0' || temp > '2'){
              cout<<"Invalid input."<<endl;
              cout<<"The number should be between 0 and 2."<<endl;
         }else{
              valid=true;
         }
    }
    int numPlayers = temp - '0';    //this way prevents loops if a letter is entered instead of a number
    if(numPlayers==0){
         player1.setAI(true);
         player2.setAI(true);
    }
    if(numPlayers==1){
         player2.setAI(true);         //0 or 1 players
    }
    //Player 1 places boats
    player1.setBoats();
    if(numPlayers==2){
         p1SwitchScreen();
    }
    //Player 2 places boats
    player2.setBoats();
    if(numPlayers==2){
         p2SwitchScreen();
    }
    //Boats are set. Time to play the game!
    //victory conditions examined at end of each turn. 
    while(true){
         cout<<"Player 1 Turn"<<endl;
         turn(player1, player2);
         if(numPlayers==2){
              p1SwitchScreen();
         }
         cout<<"Player 2 Turn"<<endl;
         turn(player2, player1);
         if(numPlayers==2){
              p2SwitchScreen();
         }
    }
    //You'll never actually reach this
    system("PAUSE");
    return EXIT_SUCCESS;
}

//Each person's turn. It's viewed as player 1's turn.
//made to be usable by all players, AI and Human, 1 & 2
void turn(Player & player1, Player & player2){
     system("cls");
     char result;
     int target, x, y;
     bool valid = false;
     //Print out the current Board
     player2.printEnemyBoard(); 
     player1.printFriendBoard();
     //find next non-redundant target
     while(!valid){
          valid=true;
          target = player1.getTarget();
          x=target/10;
          y=target%10;
          result = player2.boardSquare(y,x);
          if(result=='X' || result=='O'){
               cout<<"You've gone there already. Try again."<<endl;
               valid=false;
          }
     }
     //Evaluate hitting that target
     switch(result){
          case 'A':
               cout<<"You Hit The Aircraft Carrier."<<endl;
               player2.setSquare(x,y,'X');
               player2.attackA();
               break;
          case 'B':
               cout<<"You Hit The Battleship."<<endl;
               player2.setSquare(x,y,'X');
               player2.attackB();
               break;
          case 'D':
               cout<<"You Hit The Destroyer."<<endl;
               player2.setSquare(x,y,'X');
               player2.attackD();
               break;
          case 'P':
               cout<<"You Hit The Patrol Boat."<<endl;
               player2.setSquare(x,y,'X');
               player2.attackP();
               break;
          case 'S':
               cout<<"You Hit The Submarine."<<endl;
               player2.setSquare(x,y,'X');
               player2.attackS();
               break;
          default:
               cout<<"You missed."<<endl;
               player2.setSquare(x,y,'O');
               break;
     }
     ////Check Victory Condition!
     if(player2.getLives()==0){
          if(player1.getAI() && player2.getAI()){
               cout<<"THE COMPUTER WINS!!!"<<endl;
          }else if(player1.getAI()){
               cout<<"Too Bad. You Lose."<<endl;
          }else{
               cout<<"Congratulations!! You Win!"<<endl;
          }
          system("PAUSE");
          exit(0);
     }
     if(!player1.getAI()){
          system("PAUSE");
     }
}
//NO CHEATING :)
void p1SwitchScreen(){
     system("cls");
     cout<<"It is time for Player 2 to take his/her turn."<<endl;
     cout<<"Please get Player 2. No Cheating."<<endl;
     system("PAUSE");
}

void p2SwitchScreen(){
     system("cls");
     cout<<"It is time for Player 1 to take his/her turn."<<endl;
     cout<<"Please get Player 1. No Cheating."<<endl;
     system("PAUSE");
}

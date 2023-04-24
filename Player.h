/**********************************

Patrick Saperstein
Battleship
for COBB Tuning
July 8, 2016
Player.h

**********************************/

#ifndef Player_h_included
#define Player_h_included

class Player
{
      public:
             Player();
             Player(const bool &);
             void setAI(bool);
             char boardSquare(int, int);
             void setSquare(int, int, char);
             void setBoats();
             bool getAI();
             void printFriendBoard();
             void printEnemyBoard();
             int getTarget();
             void attackA();
             void attackB();
             void attackS();
             void attackP();
             void attackD();
             int getLives();
      private:
              char board[10][10];
              int numLiveBoats;
              bool isAI;
              int aircraftCarrier;
              int battleship;
              int submarine;
              int destroyer;
              int patrolBoat;
              void AISetBoats();
              void PlayerSetBoats();
              void AISetBoat(char, int);
              int letterToNumber(char);
              int placeX();
              int placeY();
              int placeD();
              bool checkAndSet(int, int, int, char, int);
};

#endif //Player_h_included

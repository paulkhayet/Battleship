//Hw4.cpp
//Paul Khayet, CISP 400
//12/15/2019
// A basic version of the hit classic "Battleship"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include<ctime> 
using namespace std; 
fstream nameFile;
  ofstream myfile;


//Global Variables
char pboard[10][10] = 
{{'-','-','-','-','-','-','-','-','S','-'},
{'-','S','-','-','-','-','-','-','S','-'},
{'-','S','-','-','-','-','-','-','S','-'},
{'-','S','-','S','S','S','S','-','-','-'},
{'-','S','-','-','-','-','-','-','-','-'},
{'-','S','-','-','S','S','S','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','S','S','-','-'},
}; 
char bboard[10][10] = 
{{'-','-','-','-','S','S','S','S','S','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','S','-'},
{'-','-','-','-','-','-','-','-','S','-'},
{'-','-','-','-','-','-','S','-','S','-'},
{'-','-','-','-','-','-','S','-','-','-'},
{'-','-','-','-','-','-','S','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','S','S','S','S','-','-','-','-','S'},
{'-','-','-','-','-','-','-','-','-','S'},
}; ; 
char pfboard[10][10] =
{{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
}; 


//Function Prototpe
void printBoard(char b[10][10]); 
void playerFire(); 
int checkWin(); 
void countShipB(); 
void botFire(); 
void saveBotData(int x, int y); 
void saveHumanData(int x, int y); 
void countShipP(); 
string printDate(); 

//Global Variables
bool stop = false; 
bool multifire; 
int playerShip = 5; 
int botShip = 5; 

// Specification C1 - OOP
class ship {
  public:
  int size; 
  bool alive; 

  bool checkAlive(){
    return alive; 
  }

  void kill(){
    alive = false; 
  }
}; 

class carrier:public ship{
  public:
  carrier(){
    int size = 5; 
    bool alive = true; 
  }

};

class cruiser: public ship{
  public:
  cruiser(){
    int size = 3; 
    bool alive = true; 
  }
};

class submarine: public ship{
  public:
  submarine(){
    int size = 3;
    bool alive = true; 
  }
};

class battleship: public ship{
  public: 
  battleship(){
    int size = 4; 
    bool alive = true; 
  }
}; 

class destroyer: public ship{
  public:
  destroyer(){
    int size = 2; 
    bool alive = true; 
  }
};

carrier c; 
cruiser cr; 
submarine s; 
battleship b; 
destroyer d; 

//MAIN
int main() {
  myfile.open ("Log.txt");
  cout << "The current date is: " << printDate() << endl; 
  cout << "Hello and welcome to Battleship!" << endl; 
  cout << "You will have the first move, " << endl; 
  cout << "and you cannot move your ships." << endl; 
  cout << "HAVE FUN" << endl << endl; 


  while (stop == false){
  cout << "ENEMY BOARD" << endl; 
  cout << "------------------" << endl; 
  printBoard(pfboard); 
  cout << "\nYOUR BOARD" << endl; 
  cout << "------------------" << endl; 
  printBoard(pboard); 

  cout << "What would you like to do?" << endl;
  cout << "1. Fire" << endl; 
  cout << "2. Quit" << endl; 
  int input; 
  cin >> input; 

  if (input == 1){
    playerFire(); 
    // Specification A2 - MultiFire Game
    if (multifire == true){
      for (int i = 0; i < playerShip - 1; i++){
        playerFire(); 
      }
    }
    botFire(); 
    if (multifire == true){
      for (int i = 0; i < botShip - 1; i++){
        botFire(); 
      }
    }
  }
  if (input == 2){
    stop = true; 
  }

  // Specification C3 - Secret Option
  if (input == 5){
    cout << "BOT BOARD" << endl; 
    cout << "------------------" << endl; 
    printBoard(bboard); 
  }

  
  }
  myfile.close();
}


void printBoard(char b[10][10]){
  cout << "  1 2 3 4 5 6 7 8 9 10" << endl; 
  for (int j = 0; j < 10; j++){
  if (j == 0){
    cout << "A "; 
  }
  if (j == 1){
    cout << "B "; 
  }
  if (j == 2){
    cout << "C "; 
  }
  if (j == 3){
    cout << "D "; 
  }
  if (j == 4){
    cout << "E "; 
  }
  if (j == 5){
    cout << "F "; 
  }
  if (j == 6){
    cout << "G "; 
  }
  if (j == 7){
    cout << "H "; 
  }
  if (j == 8){
    cout << "I "; 
  }
  if (j == 9){
    cout << "J "; 
  }

  
  for (int i = 0; i < 10; i++){
    cout << b[j][i]<< " "; 
  }
  cout << endl; 
  }
}



void countShipP() {
  if (pboard[1][1] == 'X' && pboard[2][1] == 'X' && pboard[3][1] == 'X' && pboard[4][1] == 'X' && pboard[5][1] == 'X'){
    c.kill(); 
  }

  if (pboard[0][8] == 'X' && pboard[1][8] == 'X' && pboard[2][8] == 'X' ){
    cr.kill(); 
  }

  if (pboard[5][4] == 'X' && pboard[5][5] == 'X' && pboard[5][6] == 'X' ){
    s.kill(); 
  }

  if (pboard[3][3] == 'X' && pboard[3][4] == 'X' && pboard[3][5] == 'X' && pboard[3][6] == 'X'){
    b.kill(); 
  }

  if(pboard[9][6] == 'X' && pboard[9][7] == 'X' ){
    d.kill(); 
  }

  int temp = 0; 

  if (c.checkAlive() == true){
    temp++; 
  }
  if (cr.checkAlive() == true){
    temp++; 
  }
  if (s.checkAlive() == true){
    temp++; 
  }
  if (b.checkAlive() == true){
    temp++; 
  }
  if (d.checkAlive() == true){
    temp++; 
  }
  
  playerShip = temp; 
}

// Specification A1 - Adv Input Validation
void playerFire(){
    char row; 
    int rowNum; 
    int column; 
    cout << "What row would you like to fire at?(Letter): "; 
    cin >> row; 
    cout << "\nWhat column would you like to fire at?(Number): "; 
    cin >> column; 
    column--; 
    if (row == 'A' || row == 'a' ){
      rowNum = 0; 
    }
    else if (row == 'B' || row == 'b' ){
      rowNum = 1; 
    }
    else if (row == 'C' || row == 'c' ){
      rowNum = 2; 
    }
    else if (row == 'D' || row == 'd' ){
      rowNum = 3; 
    }
    else if (row == 'E' || row == 'e' ){
      rowNum = 4; 
    }
    else if (row == 'F' || row == 'f' ){
      rowNum = 5; 
    }
    else if (row == 'G' || row == 'g' ){
      rowNum = 6; 
    }
    else if (row == 'H' || row == 'h' ){
      rowNum = 7; 
    }
    else if (row == 'I' || row == 'i' ){
      rowNum = 8; 
    }
    else if (row == 'J' || row == 'j' ){
      rowNum = 9; 
    }
    // Specification B1 - Validate Input
    else{
      cout << "You did not enter a valid row number! Try again!" << endl; 
      playerFire(); 
    }

  if (bboard[rowNum][column] == 'X'){
    cout << "You already fired there! Try again!" << endl; 
  }
  if (bboard[rowNum][column] == 'S'){
    cout << "HIT!!!" << endl; 
    saveHumanData(rowNum,column); 
    bboard[rowNum][column] = 'X'; 
    pfboard[rowNum][column] = 'X'; 
  }
  if(bboard[rowNum][column] == '-'){
    cout << "Miss." << endl; 
    saveHumanData(rowNum,column);
    bboard[rowNum][column] = 'O'; 
    pfboard[rowNum][column] = 'O'; 
  }
}

int checkWin(){
  countShipP(); 
  countShipB(); 
  if (playerShip == 0){
    cout << 1 << endl; 
    return 1; 
  }
  else if (botShip == 0){
    cout << 2 << endl; 
    return 2; 
  }
  else {
    cout << 0 << endl; 
    return 0; 
  }
}


void botFire(){
  int x = rand() % 10;  
  int y = rand() % 10; 
  // Specification C2 - Prohibit AI wasted shots
  if (pboard[x][y] == 'X'){
    botFire(); 
  } 
  else if (pboard[x][y] == 'S'){
    cout << "You have been hit by the bot!" << endl; 
    saveBotData(x,y); 
    pboard[x][y] = 'X'; 
  }
  else if (pboard[x][y] == '-'){
    cout << "The bot missed!" << endl; 
    saveBotData(x,y); 
    pboard[x][y] = 'O'; 
  }
}

void countShipB() {
  if (pboard[1][1] == 'X' && pboard[2][1] == 'X' && pboard[3][1] == 'X' && pboard[4][1] == 'X' && pboard[5][1] == 'X'){
    c.kill(); 
  }

  if (pboard[0][8] == 'X' && pboard[1][8] == 'X' && pboard[2][8] == 'X' ){
    cr.kill(); 
  }

  if (pboard[5][4] == 'X' && pboard[5][5] == 'X' && pboard[5][6] == 'X' ){
    s.kill(); 
  }

  if (pboard[3][3] == 'X' && pboard[3][4] == 'X' && pboard[3][5] == 'X' && pboard[3][6] == 'X'){
    b.kill(); 
  }

  if(pboard[9][6] == 'X' && pboard[9][7] == 'X' ){
    d.kill(); 
  }

  int temp = 0; 

  if (c.checkAlive() == true){
    temp++; 
  }
  if (cr.checkAlive() == true){
    temp++; 
  }
  if (s.checkAlive() == true){
    temp++; 
  }
  if (b.checkAlive() == true){
    temp++; 
  }
  if (d.checkAlive() == true){
    temp++; 
  }
  cout << "Temp: " << temp; 
  botShip = temp; 
}


void saveBotData(int x, int y){
  myfile << printDate(); 
  myfile << "The bot fired at: "; 
  y++; 
  if (x == 0){
    myfile << "A";
    myfile << y << endl;  
  }
  if (x == 1){
    myfile << "B"; 
    myfile << y << endl;  
  }
  if (x == 2){
    myfile << "C"; 
    myfile << y << endl;  
  }
  if (x == 3){
    myfile << "D"; 
    myfile << y << endl;  
  }
  if (x == 4){
    myfile << "E"; 
    myfile << y << endl;  
  }
  if (x == 5){
    myfile << "F"; 
    myfile << y << endl;  
  }
  if (x == 6){
    myfile << "G"; 
    myfile << y << endl;  
  }
  if (x == 7){
    myfile << "H"; 
    myfile << y << endl;  
  }
  if (x == 8){
    myfile << "I"; 
    myfile << y << endl;  
  }
  if (x == 9){
    myfile << "J"; 
    myfile << y << endl;  
  }

myfile << endl; 
}

//Specification B2 - Log file to Disk
void saveHumanData(int x, int y){
  myfile << printDate(); 
  myfile << "The player fired at: "; 
  if (x == 0){
    myfile << "A";
    myfile << y << endl;  
  }
  if (x == 1){
    myfile << "B"; 
    myfile << y << endl;  
  }
  if (x == 2){
    myfile << "C"; 
    myfile << y << endl;  
  }
  if (x == 3){
    myfile << "D"; 
    myfile << y << endl;  
  }
  if (x == 4){
    myfile << "E"; 
    myfile << y << endl;  
  }
  if (x == 5){
    myfile << "F"; 
    myfile << y << endl;  
  }
  if (x == 6){
    myfile << "G"; 
    myfile << y << endl;  
  }
  if (x == 7){
    myfile << "H"; 
    myfile << y << endl;  
  }
  if (x == 8){
    myfile << "I"; 
    myfile << y << endl;  
  }
  if (x == 9){
    myfile << "J"; 
    myfile << y << endl;  
  }
myfile << endl; 
}

// Specification A3 - Date Class in Program Greeting
string printDate(){
    string temp; 
    time_t tt; 
    struct tm * ti; 
    time (&tt); 
    ti = localtime(&tt); 
    temp = asctime(ti); 
    return temp; 
}

// Specification B3 - Random Start
void randomBotBoard(){
  int x = rand() % 3;

  if(x == 0){
   char bboard1 [10][10]=
{{'-','-','-','-','S','S','S','S','S','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','S','-'},
{'-','-','-','-','-','-','-','-','S','-'},
{'-','-','-','-','-','-','S','-','S','-'},
{'-','-','-','-','-','-','S','-','-','-'},
{'-','-','-','-','-','-','S','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','S','S','S','S','-','-','-','-','S'},
{'-','-','-','-','-','-','-','-','-','S'},
}; 
  }
  if (x == 1){
    char bboard1 [10][10]=
{{'-','S','-','-','-','-','-','-','-','S'},
{'-','S','-','-','-','-','-','-','-','S'},
{'-','S','-','S','-','-','-','-','-','-'},
{'-','S','-','S','-','-','-','-','-','-'},
{'-','S','-','S','-','-','S','S','S','-'},
{'-','-','-','-','S','-','-','-','-','-'},
{'-','-','-','-','S','-','-','-','-','-'},
{'-','-','-','-','S','-','-','-','-','-'},
{'-','-','-','-','S','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
}; 
  }
  if ( x == 2){
    char bboard1 [10][10] = 
{{'-','S','-','-','-','-','-','-','-','-'},
{'-','S','-','-','-','-','-','-','-','-'},
{'-','S','-','S','S','S','-','-','-','-'},
{'-','S','-','-','-','-','-','-','-','-'},
{'-','S','-','-','-','-','S','S','S','-'},
{'-','S','S','S','S','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','-','-','-','-','-','-','-','-'},
{'-','-','S','S','-','-','-','-','-','-'},
}; 
  }
}
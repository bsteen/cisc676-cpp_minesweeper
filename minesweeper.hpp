#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

struct Square{
  bool hasMine = false;
  bool isRevealed = false;
  bool isFlagged = false;
  int adjacent_mines = 0; //Value shown when space is cleared
};

class Minesweeper{
  public:
    int x_size = 0;
    int y_size = 0;
    int number_of_mines = 0;
    bool first_guess = true;
    
    bool dead = false;
    bool win = false;
    
    //Game board is a vector of pointers to Squares
    vector<Square*> game_board;
    
    Minesweeper(int x, int y, int mines);
    ~Minesweeper();
    void createBoard();
    void initializeBoard(int y, int x);
    void printBoard(bool showAnswers);
    int convertYXtoRM(int y, int x);
    bool checkSquare(int y, int x, bool placeFlag, bool useArgs);
    bool checkSquare();
    void getUserCoords(int &y, int &x, bool &placeFlag);
    void revealSquare(int y, int x);
    void recursiveReveal(int y, int x);
    bool checkIfWon();
    void inputError(int &y, int &x, bool placeFlag);
};
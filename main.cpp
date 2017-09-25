#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.hpp"

using namespace std;

//This cheat code does nothing, but someone looking around the executable might find it...
string secret_code = "Super secret world: Wololo";

int main(int argc, char *argv[]){
    
    int x_size = 0;
    int y_size = 0;
    int number_of_mines = 0;

    string deaths[] = {"exploded!", "vaporized!", "dismembered!",
    "terminated with extreme prejudice.", "welcome to die.", "WASTED!", "BLAM'D!"};
    
    if(argc != 4){
        cout << "Usage is: ./minesweeper [x width(>1)] [y height(>1)] [# mines(>0)]" << endl;
        return 0;
    }
    else{
        x_size = abs(atoi(argv[1]));
        y_size = abs(atoi(argv[2]));
        number_of_mines = abs(atoi(argv[3]));
    }
    
    if(x_size < 2 || y_size < 2){
        cout << "The board must be at least 2 in both dimensions." << endl;
        return 0;
    }
    
    if(number_of_mines < 1){
        number_of_mines = 1;
    }
    else if(number_of_mines >= x_size * y_size){
        number_of_mines = x_size * y_size - 1;
    }
    
    // Create the board with the input values and ask user for first guess.
    Minesweeper game(x_size, y_size, number_of_mines);

    // game.printBoard(true); //Print the solutions, debug only

    game.win = game.checkIfWon(); //Need to check this incase they win in the first turn.
    
    //Main game loop
    while(!game.dead && !game.win){
        game.printBoard(false);
        game.dead = game.checkSquare();
        game.win = game.checkIfWon();
    }

    //Show end game message
    if(game.dead){
        game.printBoard(true);
        srand(time(NULL));
        cout << "You hit a mine and were " << deaths[rand() % 7] << endl << "Game over." << endl;
    }
    else if(game.win){
        game.printBoard(true);
        cout << "~~~~~You won~~~~~" << endl << "Game over." << endl;
    }

    return 0;
}

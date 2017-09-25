#include "minesweeper.hpp"

//Initializes the game by creating the board and asking the player for their first guess
//This first guess will always reveal a blank spot
Minesweeper::Minesweeper(int x, int y, int mines){
    x_size = x;
    y_size = y;
    number_of_mines = mines;
    bool placeFlag = false;
    int first_x, first_y;
    cout << "X dimension: " << x_size << ", Y dimension: " << y_size << ", Number of mines: " << number_of_mines << endl;

    createBoard();//Initialize the vector
    printBoard(false);//Print the totally covered board.

    getUserCoords(first_y, first_x, placeFlag); //Get the user's first input
    initializeBoard(first_y, first_x);//Initialize board with first input in mind (don't put a mine where they guessed)

    checkSquare(first_y, first_x, placeFlag, true);//Now that the board is initalized, reveal the first guess.
}

//Clear allocated items in game board and empty game board.
Minesweeper::~Minesweeper(){
    for (vector<Square*>::iterator it = game_board.begin() ; it != game_board.end(); ++it){
        delete *it;
    }
    game_board.clear();
}

//Allocates the space for the board in the (1D) vector.
void Minesweeper::createBoard(){
    for (int i = 0; i < x_size * y_size; i++){
        game_board.push_back(new Square);
    }
}

int Minesweeper::convertYXtoRM(int y, int x){
    return (y * x_size) + x;
}

//Places bombs on the board and set adjacent bomb number
//y and x are the user's first guess; don't put a bomb there
void Minesweeper::initializeBoard(int y, int x){
    int mine_positions[number_of_mines];
    srand(time(NULL));
    bool all_unique = false;
    int possible_postion;
    
    //Generate the position for the mines, and guarantee they are unique
    for(int i = 0; i < number_of_mines; i++){
        
        //Generate a new number that has not been used yet
        while(!all_unique){
            possible_postion = rand() % (x_size * y_size);

            if(possible_postion == convertYXtoRM(y,x)){
                continue; //Can't place bomb on the first guessed space.
            }

            all_unique = true; //Assume the new value is unique
            
            //Now test if it is actually unique
            for(int j = i - 1; j >= 0; j--){
                if(possible_postion == mine_positions[j]){
                    all_unique = false;
                    break;
                }
            }
        }
        
        //Position has been found to be unique, add to list of used spaces
        mine_positions[i] = possible_postion;
        
        //Register the mine on the actual game board. 
        game_board.at(mine_positions[i])->hasMine = true;
        
        //Reset value for next loop
        all_unique = false; 
    }
    
    //Calculate number of adjacent mines
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            int mine_count = 0;
            
            //Check above
            if(i > 0){
                if(j > 0 && game_board.at(convertYXtoRM(i - 1, j - 1))->hasMine){
                    mine_count++;
                }
                if(game_board.at(convertYXtoRM(i - 1, j))->hasMine){
                    mine_count++;
                }
                if(j < x_size - 1 && game_board.at(convertYXtoRM(i - 1, j + 1))->hasMine){
                        mine_count++;
                }
            }
            
            //Check left and right
            if(j > 0 && game_board.at(convertYXtoRM(i, j - 1))->hasMine){
                mine_count++;
            }
            if(j < x_size - 1 && game_board.at(convertYXtoRM(i, j + 1))->hasMine){
                mine_count++;
            }
            
            //Check below
            if(i < y_size - 1){
                if(j > 0 && game_board.at(convertYXtoRM(i + 1, j - 1))->hasMine){
                    mine_count++;
                }
                if(game_board.at(convertYXtoRM(i + 1, j))->hasMine){
                    mine_count++;
                }
                if(j < x_size - 1 && game_board.at(convertYXtoRM(i + 1, j + 1))->hasMine){
                    mine_count++;
                }
            }
            
            //Set its adjacent_mines value after calculations are done
            game_board.at(convertYXtoRM(i, j))->adjacent_mines = mine_count;
        }
    }
}

void Minesweeper::inputError(int &y, int &x, bool placeFlag){
    if(placeFlag){
        cout << "Invalid input format, defaulting coordinates to \"f 0 0\"" << endl;
        x = 0;
        y = 0;
    }
    else{
        cout << "Invalid input format, defaulting coordinates to \"0 0\"" << endl;
        x = 0;
        y = 0;
    }

    return;
}

void Minesweeper::getUserCoords(int &y, int &x, bool &placeFlag){
    string input_string, first, second, third;
    x = 0;
    y = 0;

    cout << endl << "Enter \"X Y\" or \"f X Y\": ";
    getline(cin, input_string); //Get the input

    first = input_string.substr(0, 1);

    //See if the first input value is an f
    if(first.compare("f") == 0){ 
        //Get the X and Y values

        try{
            placeFlag = true;

            input_string = input_string.substr(2);
            second = input_string.substr(0, input_string.find(" "));
            
            input_string = input_string.substr(second.length() + 1);
            third = input_string;
                    
            x = abs(stoi(second));
            y = abs(stoi(third));
        }
        catch(const std::invalid_argument& ia){
            inputError(y, x, placeFlag);
            return;
        }
        catch(const out_of_range& oor){
            inputError(y, x, placeFlag);
            return;
        }
    }
    else{ //Get the x and y value
        try{
            first = input_string.substr(0, input_string.find(" "));
            input_string = input_string.substr(first.length() + 1);
            second = input_string;

            x = abs(stoi(first));
            y = abs(stoi(second));
        }
        catch(const invalid_argument& ia){
            inputError(y, x, placeFlag);
            return;
        }
        catch (const out_of_range& oor){
            inputError(y, x, placeFlag);
            return;
        }
    }   

    if(x >= x_size){
        cout << "X value to large, defaulting to " << x_size - 1 << endl;
        x = x_size - 1;
    }
    if(y >= y_size){
        cout << "Y value to large, defaulting to " << y_size - 1 << endl;
        y = y_size - 1;
    }

    // cout << x << " " << y << endl; //Debug, used to see what is going to be used as coords
}

void Minesweeper::revealSquare(int y, int x){
     game_board.at(convertYXtoRM(y, x))->isRevealed = true;
}

void Minesweeper::recursiveReveal(int y, int x){
    //Reveal the current space, return if it is already revealed or is flagged
    if(game_board.at(convertYXtoRM(y, x))->isRevealed){
        return;
    }
    else if(game_board.at(convertYXtoRM(y, x))->isFlagged){
        return;
    }
    else{
        revealSquare(y, x);//Reveal the current square
    }
    
    bool above = y - 1 >= 0;
    bool left = x - 1 >= 0;
    bool right = x + 1 <= x_size - 1;
    bool below = y + 1 <= y_size - 1;
    
    if(game_board.at(convertYXtoRM(y, x))->adjacent_mines == 0){
        if(above && left)
            recursiveReveal(y - 1, x - 1);
        if(above)
            recursiveReveal(y - 1, x);
        if(above && right)
            recursiveReveal(y - 1, x + 1);
        if(left)
            recursiveReveal(y, x - 1);
        if(right)
            recursiveReveal(y, x + 1);
        if(below && left)
            recursiveReveal(y + 1, x - 1);
        if(below)
            recursiveReveal(y + 1, x);
        if(below && right)
            recursiveReveal(y + 1, x + 1);
    }
    else{//If the currently revealed space is not a 0, don't reveal any more
        return;
    }
}

//Overload function for checking the square after the first move.
bool Minesweeper::checkSquare(){
    return checkSquare(0,0, false, false);
}

//Returns true if square is revealed and has a mine
bool Minesweeper::checkSquare(int y, int x, bool placeFlag, bool useArgs){

    //useArgs is true when revealing the very first Square of the game.
    if(!useArgs){
        getUserCoords(y, x, placeFlag); //Get user input
    }
    
    if(placeFlag){
        if(game_board.at(convertYXtoRM(y, x))->isRevealed){
            cout << "Square already revealed. Can't place flag." << endl;
            return false;
        }
        else{
            game_board.at(convertYXtoRM(y, x))->isFlagged = !game_board.at(convertYXtoRM(y, x))->isFlagged;
            return false;
        }
    }
    else{
        if(game_board.at(convertYXtoRM(y, x))->isRevealed){
            return false;//Do nothing if the Square is already revealed
        }
        else if(game_board.at(convertYXtoRM(y, x))->isFlagged){
            return false;//Do nothing if the Square is flagged
        }
        else if(game_board.at(convertYXtoRM(y, x))->hasMine){
            revealSquare(y, x);//Reveal the space with the mine
            return true;
        }
        else{
            recursiveReveal(y, x); //Attempt to reveal a large chunk
            return false;
        }
    }
}

bool Minesweeper::checkIfWon(){
    for(int y = 0; y < y_size; y++){
        for(int x = 0; x < x_size; x++){
            //If any Square that does not have mine is not revelaed, the game is not over yet.
            if(!game_board.at(convertYXtoRM(y, x))->hasMine && !game_board.at(convertYXtoRM(y, x))->isRevealed){
                return false;
            }
        }
    }
    return true;
}

void Minesweeper::printBoard(bool showAnswers){
    //Make the printout aline if there are more than 10 in either dimension
    string header_gap = "    ";

    //Print border coordinates and underlines
    cout << header_gap;
    for(int i = 0; i < x_size; i++){
        if(i > 9){
            cout << i << " ";
        }
        else{
            cout << i << "  ";
        }
    }
    cout << endl << header_gap;
    for(int i = 0; i < x_size; i++){
        cout << "_  ";
    }
    cout << endl;
    
    for(int i = 0; i < y_size; i++){
        if(i > 9){
            cout << i << "| ";//Print border coordinates
        }
        else{
            cout << i << " | ";//Print border coordinates
        }
        
        //Print the solutions
        if(showAnswers){
            for(int j = 0; j < x_size; j++){
                if(game_board.at(convertYXtoRM(i, j))->hasMine){
                    cout << "*  ";
                }
                else{
                    if(game_board.at(convertYXtoRM(i, j))->adjacent_mines == 0){
                        cout << "   ";
                    }
                    else{
                        cout << game_board.at(convertYXtoRM(i, j))->adjacent_mines << "  ";
                    } 
                }
            }
            cout << "|" << endl;
        }
        else{ //Print the player board 
            for(int j = 0; j < x_size; j++){
                if(game_board.at(convertYXtoRM(i, j))->isRevealed){
                    if(game_board.at(convertYXtoRM(i, j))->hasMine){
                        cout << "*  ";
                    }
                    else{
                        if(game_board.at(convertYXtoRM(i, j))->adjacent_mines == 0){
                            cout << "   ";
                        }
                        else{
                            cout << game_board.at(convertYXtoRM(i, j))->adjacent_mines << "  ";
                        }  
                    }
                }
                else if(game_board.at(convertYXtoRM(i, j))->isFlagged){
                    cout << "!  ";
                }
                else{
                    cout << "#  ";
                }
            }
            cout << "|" << endl;
        }
    }

    cout << header_gap;
    for(int i = 0; i < x_size; i++){
        cout << "_  ";
    }
    cout << endl;
}

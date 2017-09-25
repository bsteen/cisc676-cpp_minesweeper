#Casey Campbell, Miguel Hernandez, Benjamin Steenkamer
#CISC 676-010
#Project 1 - Command Line Minesweeper
#9/25/17

#Description (http://sec.prof.ninja/projects/)
Project 1 (ALL TEAMS BLUE): Command-Line Minesweeper. Write a function which
consumes three arguments width height number_of_mines and generates a
Minesweeper board internally. The board is a rectangle with a cover over each
square. It will display this board to the user and prompt for a coordinate where
they predict that no mine exists (format: x-coord y-coord 0-indexed). If they
struck a mine then they lose (let them know). Otherwise uncover the selected
square. If there are no adjacent mines then it should be blank and you uncover
all adjacent squares too (chain-react this for every blank square). Otherwise
show the number of mines in the surrounding 8 squares. If at somepoint only
mines are covered then the user wins and the game ends. POINTS: For every rule
or rec from ARR and EXP that you include and document (external to the code) you
get 20 points. Extra levels for (first click always blank) and the ability to
flag mines.

#Extra Credit Features
-A player can enter "f X Y" and flag a square. This square can't be revealed until the player un-flags it.
To un-flag, the player enters f X Y for the already flagged square.

-The first guess will always be safe/a blank square. Because of this, the game only allows the max number of mines to be one less than the total number of space.
e.g.: the player starts a 10x10 game with 1000 mines. The game will automatically change the number of mines to 99 since 10*10-1 = 99. In this situation, no matter
where the player guesses for their first move, they will instantly win.


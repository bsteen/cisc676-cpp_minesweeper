
build_minesweeper_game: minesweeper.o main.o
	g++ -std=c++11 -o minesweeper_game objects/main.o objects/minesweeper.o

minesweeper.o: minesweeper.cpp minesweeper.hpp
	g++ -std=c++11 -c -o objects/minesweeper.o minesweeper.cpp

main.o: main.cpp
	g++ -std=c++11 -c -o objects/main.o main.cpp

valgrind:
	g++ -std=c++11 -g -c -o objects/main.o main.cpp
	g++ -std=c++11 -g -c -o objects/minesweeper.o minesweeper.cpp
	g++ -std=c++11 -g -o minesweeper_game objects/main.o objects/minesweeper.o
	valgrind --leak-check=full ./minesweeper_game 5 2 1
 
clean:
	rm -f objects/*.o minesweeper_game
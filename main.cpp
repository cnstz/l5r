/*
 * main.cpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "GameBoard.hpp"
#include "TypeConverter.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(NULL));
	GameBoard game;								// construct GameBoard
	game.initializeGameBoard();					// initialize GameBoard
	game.printGameStatistics();					// ektipwsh statistikwn
	game.gameplay();							// gameplay

}


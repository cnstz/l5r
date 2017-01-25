/*
 * GameBoard.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#include <iomanip>
#include <iostream>
#include "GameBoard.hpp"

using namespace std;

GameBoard::GameBoard() {
}

GameBoard::~GameBoard() {
	delete player1;
	delete player2;
}

void GameBoard::initializeGameBoard() {
	cout << "Initializing gameboard...\n" << endl;
	player1 = new Player("Player 1");
	cout << endl;
	player2 = new Player("Player 2");
	cout << "\n" << endl;
}

void GameBoard::printGameStatistics() {
	cout << setw(25) << player1->getpname() << setw(10) << player2->getpname()
			<< endl;
	cout << "Honour" << setw(16) << player1->gethonour() << setw(10)
			<< player2->gethonour() << endl;
	cout << "Provinces" << setw(13) << player1->getprovinces() << setw(10)
			<< player2->getprovinces() << endl;
	cout << "Initial Defence" << setw(7) << player1->getinitialDefense()
			<< setw(10) << player2->getinitialDefense() << "\n" << endl;
}

void GameBoard::finalPhase() {
	printGameStatistics();
	player1->printHand();
	cout << "\n";
	player1->printProvinces();
	cout << "\n";
	player1->printArena();
	cout << "\n";
	player1->printHoldings();
	cout << "\n";
	player2->printHand();
	cout << "\n";
	player2->printProvinces();
	cout << "\n";
	player2->printArena();
	cout << "\n";
	player2->printHoldings();
	cout << "\n";
}

int GameBoard::checkWinningCondition() {
	if (player1->getprovinces() == 0)
		return 2;
	else if (player2->getprovinces() == 0)
		return 1;
	return 0;
}

void GameBoard::gameplay() {
	Player *first, *second;
	int i = 1;
	do {
		cout << "\n\nROUND " << i << " begins:" << endl;
		i++;
		if (player1->gethonour() >= player2->gethonour()) {
			first = player1;
			second = player2;
		} else {
			first = player2;
			second = player1;
		}
		first->startingPhase();
		first->equipPhase();
		first->battlePhase(*second);
		first->economyPhase();
		first->finalPhase();
		if (checkWinningCondition() == 0) {
			second->startingPhase();
			second->equipPhase();
			second->battlePhase(*first);
			second->economyPhase();
			second->finalPhase();
		}
		finalPhase();
	} while (checkWinningCondition() == 0);
	if (checkWinningCondition() == 1)
		cout << player1->getpname() << "wins" << endl;
	else
		cout << player2->getpname() << "wins" << endl;
}

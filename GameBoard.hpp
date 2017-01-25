/*
 * GameBoard.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _GAMEBOARD_HPP_
#define _GAMEBOARD_HPP_

#include "Player.hpp"

class GameBoard {
private:
	Player *player1, *player2;
public:
	GameBoard();
	~GameBoard();

	void initializeGameBoard();
	void printGameStatistics();
	void finalPhase();
	int checkWinningCondition();
	void gameplay();
};

#endif /* _GAMEBOARD_HPP_ */

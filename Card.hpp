/*
 * Card.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <string>

enum {
	PERSONALITY = 1, HOLDING, FOLLOWER, ITEM
};

class Card {
protected:
	std::string name;
	int cost;
	int type;
	bool isTapped;
public:

	Card(std::string, int);
	virtual ~Card();

	/* SETTERS */
	void unTap();
	void Tap();

	/* GETTERS */
	int getType();
	int getCost();
	bool getTap();
	std::string getName();

	virtual void examineCard()=0;// emfanish statistikwn kartas analoga me to type
};

#endif /* _CARD_HPP_ */

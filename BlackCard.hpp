/*
 * BlackCard.hpp
 *
 *  Created on: 5 Ìבס 2013
 *      Author: Constantine
 */

#include "Card.hpp"

#ifndef _BLACKCARD_HPP_
#define _BLACKCARD_HPP_

class BlackCard: public Card {
protected:
	bool isRevealed;
public:

	BlackCard(std::string, int);
	~BlackCard();

	/* SETTERS */
	void reveal();

	/* GETTERS */
	bool getisRevealed();
};

#endif /* _BLACKCARD_HPP_ */

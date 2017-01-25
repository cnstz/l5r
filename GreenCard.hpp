/*
 * GreenCard.hpp
 *
 *  Created on: 5 Ìבס 2013
 *      Author: Constantine
 */

#ifndef _GREENCARD_HPP_
#define _GREENCARD_HPP_

#include "Card.hpp"

class GreenCard: public Card {
protected:
	int attackBonus, defenseBonus, minimumHonour, effectBonus, effectCost;
	std::string cardText;
public:
	GreenCard(std::string, int);
	~GreenCard();

	/* SETTERS */
	void activateeffect();

	/* GETTERS */
	int getminimumHonour();
	int geteffectCost();
	int getAttack();
	int getDefense();
};

#endif /* _GREENCARD_HPP_ */

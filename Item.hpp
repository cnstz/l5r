/*
 * Item.hpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include "GreenCard.hpp"

enum {
	KATANA, SPEAR, BOW, NINJATO, WAKIZASHI
};

class Item: public GreenCard {
private:
	int durability;
public:

	Item(std::string, int);
	~Item();
	void detach();
	int getdurability();
	void damagedurability();
	void examineCard();
};

#endif /* _ITEM_HPP_ */

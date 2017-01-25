/*
 * Holding.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _HOLDING_HPP_
#define _HOLDING_HPP_

#include "BlackCard.hpp"

enum {
	PLAIN = 1, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD
};

class Holding: public BlackCard {
private:
	int harvestValue;
	Holding *upperHolding, *subHolding;
	int HoldingType;
public:

	Holding(std::string, int);
	~Holding();
	bool appendLowerHolding(Holding *);
	bool appendUpperHolding(Holding *);
	int getharvestValue();
	int getHoldingType();
	Holding* getsubHolding();
	void examineCard();
};

class Stronghold: public Holding {
private:
	int honour, money, initialDefence;
public:
	Stronghold(std::string, int);
	~Stronghold();
	int gethonour();
	int getmoney();
	int getinitialDefence();
};

#endif /* _HOLDING_HPP_ */

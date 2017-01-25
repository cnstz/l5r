/*
 * Holding.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#include <iostream>
#include "Holding.hpp"

using namespace std;

Holding::Holding(string n, int t) :
		BlackCard(n, t) {
	upperHolding = NULL;
	subHolding = NULL;
	type = HOLDING;
	HoldingType = t;
	switch (t) {
	case PLAIN:
		cost = 2;
		harvestValue = 2;
		break;
	case MINE:
		cost = 5;
		harvestValue = 3;
		break;
	case GOLD_MINE:
		cost = 7;
		harvestValue = 5;
		break;
	case CRYSTAL_MINE:
		cost = 12;
		harvestValue = 6;
		break;
	case FARMS:
		cost = 3;
		harvestValue = 4;
		break;
	case SOLO:
		cost = 2;
		harvestValue = 2;
		break;
	case STRONGHOLD:
		cost = 0;
		harvestValue = 5;
		break;
	}
}

Holding::~Holding() {
}

bool Holding::appendLowerHolding(Holding *hold) {
	if (subHolding == NULL) {
		subHolding = hold;
		hold->appendUpperHolding(this);
		return true;
	}
	return false;
}

bool Holding::appendUpperHolding(Holding *hold) {
	if (upperHolding == NULL) {
		upperHolding = hold;
		hold->appendLowerHolding(this);
		cout << hold->getName() << " successfully connected to " << name
				<< endl;
		return true;
	}
	return false;
}

int Holding::getharvestValue() {
	if (HoldingType == MINE) {
		if (upperHolding != NULL) {
			return (harvestValue + 2);
		}
	} else if (HoldingType == GOLD_MINE) {
		if (subHolding != NULL) {
			if (upperHolding != NULL) {
				return (harvestValue * 2);
			} else {
				return (harvestValue + 4);
			}
		} else if (upperHolding != NULL) {
			return (harvestValue + 5);
		}
	} else if (HoldingType == CRYSTAL_MINE) {
		if (subHolding != NULL) {
			if (subHolding->getsubHolding() == NULL) {
				return (harvestValue * 2);
			} else {
				return (harvestValue * 3);
			}
		}
	}
	return harvestValue;

}

int Holding::getHoldingType() {
	return HoldingType;
}

Holding* Holding::getsubHolding() {
	return subHolding;
}

void Holding::examineCard() {
	cout << "_______________________" << endl;
	cout << "name: " << name << endl;
	cout << "cost: " << cost << endl;
	cout << "harvestValue: " << harvestValue << endl;
	if (subHolding == NULL)
		cout << "sub Holding: -" << endl;
	else
		cout << "sub Holding: " << subHolding->getName() << endl;
	if (upperHolding == NULL)
		cout << "upper Holding: -" << endl;
	else
		cout << "upper Holding: " << upperHolding->getName() << endl;
	cout << "_______________________" << endl;
}

Stronghold::Stronghold(string n, int t) :
		Holding(n, t) {
	honour = rand() % 20 + 5;
	money = rand() % 5;
	initialDefence = rand() % 5;
}

Stronghold::~Stronghold() {
}

int Stronghold::gethonour() {
	return honour;
}

int Stronghold::getmoney() {
	return money;
}

int Stronghold::getinitialDefence() {
	return initialDefence;
}

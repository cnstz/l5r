/*
 * GreenCard.cpp
 *
 *  Created on: 5 Ìבס 2013
 *      Author: Constantine
 */

#include "GreenCard.hpp"

GreenCard::GreenCard(std::string n, int t) :
		Card(n, t) {
}

GreenCard::~GreenCard() {
}

/* SETTERS */
void GreenCard::activateeffect() {
	attackBonus = attackBonus + effectBonus;
	defenseBonus = defenseBonus + effectBonus;
}

/* GETTERS */
int GreenCard::getminimumHonour() {
	return minimumHonour;
}

int GreenCard::geteffectCost() {
	return effectCost;
}

int GreenCard::getAttack() {
	return attackBonus;
}

int GreenCard::getDefense() {
	return defenseBonus;
}


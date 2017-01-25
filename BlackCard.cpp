/*
 * BlackCard.cpp
 *
 *  Created on: 5 Ìבס 2013
 *      Author: Constantine
 */

#include "BlackCard.hpp"

BlackCard::BlackCard(std::string n, int t) :
		Card(n, t) {
	isRevealed = false;
}

BlackCard::~BlackCard() {
}

/* SETTERS */
void BlackCard::reveal() {
	isRevealed = true;
}

/* GETTERS */
bool BlackCard::getisRevealed() {
	return isRevealed;
}


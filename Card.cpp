/*
 * Card.cpp
 *
 *  Created on: 24 Öåâ 2013
 *      Author: Constantine
 */

#include "Card.hpp"

using namespace std;

Card::Card(string n, int t) {
	name = n;
	isTapped = false;
}

Card::~Card() {
}

string Card::getName() {
	return name;
}

/* SETTERS */
void Card::unTap() {
	isTapped = false;
}

void Card::Tap() {
	isTapped = true;
}

/* GETTERS */
int Card::getType() {
	return type;
}

int Card::getCost() {
	return cost;
}

bool Card::getTap() {
	return isTapped;
}


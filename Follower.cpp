/*
 * Follower.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#include "Follower.hpp"
#include <iostream>

using namespace std;

Follower::Follower(string n, int t) :
		GreenCard(n, t) {
	type = FOLLOWER;
	switch (t) {
	case FOOTSOLDIER:
		cost = 0;
		attackBonus = 2;
		defenseBonus = 0;
		minimumHonour = 1;
		effectBonus = 1;
		effectCost = 2;
		cardText =
				"Nothing like a quick drink to put you in the mood for a good scrap, eh boys?";
		break;
	case ARCHER:
		cost = 0;
		attackBonus = 0;
		defenseBonus = 2;
		minimumHonour = 1;
		effectBonus = 1;
		effectCost = 2;
		cardText = "What we do is art.What peasants do is merely adequate.";
		break;
	case SIEGER:
		cost = 5;
		attackBonus = 3;
		defenseBonus = 3;
		minimumHonour = 2;
		effectBonus = 2;
		effectCost = 3;
		cardText = "Zunguri, the Hiruma daimyo, laughed. "
				"\"Now we show them what we have learned.\"";
		break;
	case CAVALRY:
		cost = 3;
		attackBonus = 4;
		defenseBonus = 2;
		minimumHonour = 3;
		effectBonus = 3;
		effectCost = 4;
		cardText = "Show me the coin and a target.";
		break;
	case NAVAL:
		cost = 3;
		attackBonus = 2;
		defenseBonus = 4;
		minimumHonour = 3;
		effectBonus = 3;
		effectCost = 4;
		cardText =
				"Along the rocky coast the Mantis fleet raged, unable to gain a hold on the Isawa shore. "
						"At last, a port opened for them. In the end, "
						"it was not the kobune captains that new the way, "
						"but a young boyin silken robes and a pale, golden mask.";
		break;
	case BUSHIDO:
		cost = 8;
		attackBonus = 8;
		defenseBonus = 8;
		minimumHonour = 6;
		effectBonus = 3;
		effectCost = 8;
		cardText = "Each will make a name or die with glory.";
		break;
	}
}

void Follower::detach() {
	delete this;
	cout << "BLAARGGGH!" << endl;
}

Follower::~Follower() {
}

void Follower::examineCard() {
	cout << "_______________________" << endl;
	cout << "name: " << name <<" (follower)"<< endl;
	cout << "cost: " << cost << endl;
	cout << "attackBonus: " << attackBonus << endl;
	cout << "defenceBonus: " << defenseBonus << endl;
	cout << "minimumHonour: " << minimumHonour << endl;
	cout << "effectBonus: " << effectBonus << endl;
	cout << "effectCost: " << effectCost << endl;
	cout << "cardText: " << cardText << endl;
	cout << "_______________________" << endl;
}

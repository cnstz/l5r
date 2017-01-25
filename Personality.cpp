/*
 * Personality.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#include <iostream>
#include "Personality.hpp"
#include "TypeConverter.hpp"

using namespace std;

int Personality::uniqueIDseed = 100;

Personality::Personality(string n, int t) :
		BlackCard(n, t) {
	no_followers = 0;
	no_items = 0;
	uniqueIDseed += rand() % 20 + 1;
	ID = uniqueIDseed;
	for (int i = 0; i < NO_MAXFOLLOWERS; i++) {
		attachedFollowers[i] = NULL;
	}
	for (int i = 0; i < NO_MAXITEMS; i++) {
		attachedItems[i] = NULL;
	}
	isDead = false;
	type = PERSONALITY;
	switch (t) {
	case ATTACKER:
		attack = 3;
		defense = 2;
		honour = 2;
		cost = 5;
		break;
	case DEFENDER:
		attack = 2;
		defense = 3;
		honour = 2;
		cost = 5;
		break;
	case SHOGUN:
		attack = 10;
		defense = 5;
		honour = 8;
		cost = 15;
		break;
	case CHANCELLOR:
		attack = 5;
		defense = 10;
		honour = 8;
		cost = 15;
		break;
	case CHAMPION:
		attack = 20;
		defense = 20;
		honour = 12;
		cost = 30;
		break;
	}
}

Personality::~Personality() {
	for (int i = 0; i < no_followers; i++) {
		attachedFollowers[i]->detach();
	}
	for (int i = 0; i < no_items; i++) {
		attachedItems[i]->detach();
	}
}

void Personality::examineCard() {
	cout << "_______________________" << endl;
	cout << "name: " << name << "(#" << ID << ")" << endl;
	cout << "cost: " << cost << endl;
	cout << "attack: " << attack << "(" << getAttack() << ")" << endl;
	cout << "defence: " << defense << "(" << getDefense() << ")" << endl;
	cout << "honour: " << honour << endl;
	cout << "Followers slots " << NO_MAXFOLLOWERS - no_followers << endl;
	cout << "Items slots " << NO_MAXITEMS - no_items << endl;
	cout << "_______________________" << endl;
}

int Personality::getAttack() {
	int sumAttack = attack;
	for (int i = 0; i < no_followers; i++) {
		sumAttack += attachedFollowers[i]->getAttack();
	}
	for (int i = 0; i < no_items; i++) {
		sumAttack += attachedItems[i]->getAttack();
	}
	return sumAttack;
}

int Personality::getID() {
	return ID;
}

int Personality::getDefense() {
	int sumDefense = defense;
	for (int i = 0; i < no_followers; i++) {
		sumDefense += attachedFollowers[i]->getDefense();
	}
	for (int i = 0; i < no_items; i++) {
		sumDefense += attachedItems[i]->getDefense();
	}
	return sumDefense;
}

void Personality::performSeppuku() {
	cout << getName() << " : I' d rather die than being dishonored..." << endl;
	delete this;
}

void Personality::BattleResults(int dif, char type) {
	/*
	 * Se periptwsh xamenhs maxhs kaleite auth h synarthsh
	 * kai elegxei poioi apo tous epitithemenous followers
	 * kai items prepei na ginoun detach */
	int size_fol = no_followers, size_it = no_items;
	for (int i = 0; i < size_fol; i++) {
		if (attachedFollowers[i]->getAttack() >= dif) {
			attachedFollowers[i]->detach();
			attachedFollowers[i] = NULL;
			no_followers--;
		}
	}
	for (int i = 0; i < size_fol; i++) {
		if (attachedFollowers[i] == NULL) {
			for (int j = i + 1; j < size_fol; j++) {
				attachedFollowers[j - 1] = attachedFollowers[j];
			}
		}
	}
	for (int i = 0; i < size_it; i++) {
		if (attachedItems[i]->getdurability() == 0) {
			attachedItems[i]->detach();
			attachedItems[i] = NULL;
			no_items--;
		} else {
			attachedItems[i]->damagedurability();
		}
	}
	for (int i = 0; i < size_it; i++) {
		if (attachedItems[i] == NULL) {
			for (int j = i + 1; j < size_fol; j++) {
				attachedItems[j - 1] = attachedItems[j];
			}
		}
	}
	if (type == 'A')
		honour--;
	if (honour == 0) {
		performSeppuku();
	}
}

void Personality::attach(GreenCard *attachment) {
	Follower *follower;
	Item *item;
	TypeConverter converter;
	converter.getCorrectType(attachment, &follower, &item);
	if (attachment->getType() == FOLLOWER) {
		attachedFollowers[no_followers] = follower;
		no_followers++;
	} else {
		attachedItems[no_items] = item;
		no_items++;
	}
}

bool Personality::canAttach(int type, int requiredhonour) {
	if (requiredhonour <= honour) {
		if (type == FOLLOWER) {
			if (no_followers < NO_MAXFOLLOWERS) {
				return true;
			}
		} else {
			if (no_items < NO_MAXITEMS)
				return true;
		}
	}
	if (requiredhonour > honour)
		cout << name << " doesn't have enough honour." << endl;
	else {
		if (type == FOLLOWER)
			cout << name << " has maximum number of followers." << endl;
		else
			cout << name << " has maximum number of items." << endl;
	}
	return false;
}

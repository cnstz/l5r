/*
 * Item.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */

#include <iostream>
#include "Item.hpp"

using namespace std;

Item::Item(string n, int t) :
		GreenCard(n, t) {
	type = ITEM;
	switch (t) {
	case KATANA:
		attackBonus = 3;
		defenseBonus = 3;
		minimumHonour = 1;
		effectBonus = 5;
		effectCost = 6;
		durability = 4;
		cost = 5;
		cardText =
				"\"A blade is the soul of its maker, soft or hard, cold or hot. "
						"Any darkness is reflected in the sheen of steel; \n"
						"any imperfection turns the blade brittle and shatters in the depths of the soul. "
						"How stands your soul, Toshiken, my son? How bitter is your blade, if it draws your father's blood?\"";
		break;
	case SPEAR:
		attackBonus = 2;
		defenseBonus = 2;
		minimumHonour = 1;
		effectBonus = 4;
		effectCost = 6;
		durability = 4;
		cost = 5;
		cardText =
				"Sometimes you die a glorious death with your sword held high. "
						"Sometimes you're just target practice";
		break;
	case BOW:
		attackBonus = 4;
		defenseBonus = 4;
		minimumHonour = 2;
		effectBonus = 4;
		effectCost = 10;
		durability = 6;
		cost = 10;
		cardText = "\"They are deadly, of that there is no doubt. "
				"They are not so deadly as those who wield them, however.\"";
		break;
	case NINJATO:
		attackBonus = 6;
		defenseBonus = 6;
		minimumHonour = 3;
		effectBonus = 6;
		effectCost = 10;
		durability = 8;
		cost = 15;
		cardText =
				"\"To the Scorpion, the Empress grants the shadow of Heaven, "
						"that they might be ever hidden.\" - The Voice of the Empress";
		break;
	case WAKIZASHI:
		attackBonus = 8;
		defenseBonus = 8;
		minimumHonour = 6;
		effectBonus = 8;
		effectCost = 15;
		durability = 10;
		cost = 20;
		cardText =
				"The Dragon held his wakizashi at an angle, catching the light of the sun. "
						"The Lion flinched only for a moment - the rest of his life.";
		break;
	}
}

Item::~Item() {
}

void Item::detach() {
	delete this;
}

int Item::getdurability() {
	return durability;
}

void Item::damagedurability() {
	durability--;
}

void Item::examineCard() {
	cout << "_______________________" << endl;
	cout << "name: " << name << " (item)" << endl;
	cout << "cost: " << cost << endl;
	cout << "attackBonus: " << attackBonus << endl;
	cout << "defenceBonus: " << defenseBonus << endl;
	cout << "minimumHonour: " << minimumHonour << endl;
	cout << "effectBonus: " << effectBonus << endl;
	cout << "effectCost: " << effectCost << endl;
	cout << "cardText: " << cardText << endl;
	cout << "durability: " << durability << endl;
	cout << "_______________________" << endl;
}

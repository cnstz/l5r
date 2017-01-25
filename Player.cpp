/*
 * Player.cpp
 *
 *  Created on: 25 ÷Â‚ 2013
 *      Author: Constantine
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include "Player.hpp"

using namespace std;

Player::Player(string n) :
		pname(n), numberOfProvinces(4) {

	string sname;
	cout << "Wild " << n << " comes to fight!" << endl;
	switch (rand() % 4) {
	case 0:
		sname = "Fields of the Dead";
		break;
	case 1:
		sname = "The Naga Stronghold";
		break;
	case 2:
		sname = "The Shadow Stronghold of the Bayushi";
		break;
	case 3:
		sname = "Ninja Stronghold";
		break;
	}
	FateDeck = Deck.createFateDeck();
	DynastyDeck = Deck.createDynastyDeck();
	Deck.deckShuffler(FateDeck);
	Deck.deckShuffler(DynastyDeck);
	for (int i = 0; i < STARTING_HAND; i++) {
		drawFateCard();
	}
	for (int i = 0; i < 4; i++) {
		drawDynastyCard();
	}
	stronghold = new Stronghold(sname, 7);
	stronghold->reveal();
	holding.BlackpushBack(stronghold);
	honour = stronghold->gethonour();
	money = stronghold->getmoney();
	initialDefense = stronghold->getinitialDefence();
}

Player::~Player() {
}

int Player::gethonour() {
	return honour;
}

int Player::getprovinces() {
	return numberOfProvinces;
}

int Player::getinitialDefense() {
	return initialDefense;
}

int Player::calculateAttack(BlackList *attackers) {
	/* Ektypwnei to strato tou player, kai tou zhtaei
	 * na epileksei tous attackers. Tous topothetei se
	 * mia lista, kai ipologizei to sinoliko tous Attack.
	 */
	int totalAttack = 0;
	string chosenPerson;
	Personality *person;
	cout << "Available Personalities for battle:" << endl;
	army.printUntapped();
	do {
		cout << "Choose attacking Personalities. Type STOP to stop" << endl;
		do {
			chosenPerson = windowsreadcorrection();
			if (chosenPerson == "STOP")
				break;
		} while ((person = army.getPersonality(chosenPerson)) == NULL);
		if (chosenPerson != "STOP") {
			person = army.getArmyBlackNode(person->getName());
			totalAttack += person->getAttack();
			person->Tap();
			attackers->BlackpushBack(person);
		}
	} while (army.get_size() != 0
			&& (chosenPerson != "STOP" || attackers->get_size() == 0));
	return totalAttack;
}

int Player::calculateDefense(BlackList *defenders) {
	/* Ektypwnei to strato tou player, kai tou zhtaei
	 * na epileksei tous defenders. Tous topothetei se
	 * mia lista, kai ipologizei to sinoliko tous Defense.
	 */
	int totalDefense = 0;
	string chosenPerson = "a";
	Personality *person;
	if (army.get_size() != 0) {
		cout << "Available Personalities for defense:" << endl;
		army.printUntapped();
	} else {
		cout
				<< "Available Personalities for defense: none (Good luck with that...)"
				<< endl;
	}
	while (army.get_size() != 0 && chosenPerson != "STOP") {
		cout << "Choose defending Personalities: (type STOP to stop)" << endl;
		do {
			chosenPerson = windowsreadcorrection();
			if (chosenPerson == "STOP")
				break;
		} while ((person = army.getPersonality(chosenPerson)) == NULL);
		if (chosenPerson != "STOP") {
			person = army.getArmyBlackNode(person->getName());
			totalDefense += person->getDefense();
			person->Tap();
			defenders->BlackpushBack(person);
		}
	}
	totalDefense += initialDefense;
	return totalDefense;
}

string Player::getpname() {
	return pname;
}

void Player::untapEverything() {
	cout << "Untappinng " << pname << "' s cards!" << endl;
	stronghold->unTap();
	holding.BlackunTap("holdings");
	army.BlackunTap("army");
}

void Player::drawFateCard() {
	cout << pname << " draws from the Fate Deck!" << endl;
	GreenCard *i = FateDeck->front();
	hand.GreenpushBack((i));
	FateDeck->pop_front();
}

void Player::drawDynastyCard() {
	cout << pname << " draws from the Dynasty Deck!" << endl;
	BlackCard *i = DynastyDeck->front();
	provinces.BlackpushBack((i));
	DynastyDeck->pop_front();
}

void Player::drawDynastyCard(int pos) {
	/* Adikathista mia agorasmenh province */
	cout << pname << " draws from the Dynasty Deck!" << endl;
	BlackCard *i = DynastyDeck->front();
	provinces.Blackpush(i, pos);
	DynastyDeck->pop_front();
}

void Player::destroyProvince(int prov) {
	/* Katastrefei th province pou vriskete sth thesh prov */
	int i = 1;
	BlackNode *node;
	node = provinces.get_head();
	do {
		if (i == prov) {
			provinces.deleteBlackNode(node->data->getName());
			numberOfProvinces--;
			return;
		}
		node = node->next;
		i++;
	} while (1);
}

void Player::revealProvinces() {
	cout << pname << " revealing provinces..." << endl;
	if (provinces.get_size() != 0)
		provinces.reveal();
}

void Player::printHand() {
	cout << "Hand of " << pname << ":" << endl;
	hand.Greenprint();
}

void Player::printProvinces() {
	cout << "Provinces of " << pname << ":" << endl;
	provinces.Blackprint();
}

void Player::printArena() {
	cout << "Arena of " << pname << ":" << endl;
	army.Blackprint();
}

void Player::printHoldings() {
	cout << "Holdings of " << pname << ":" << endl;
	holding.Blackprint();
}

void Player::startingPhase() {
	cout << "\n" << pname << ": Starting Phase." << endl;
	untapEverything();
	cout << "\n";
	if (FateDeck->size() != 0)
		drawFateCard();
	else
		cout << this->getpname() << ": The Fate Deck is empty." << endl;
	cout << "\n";
	revealProvinces();
	cout << "\n";
	printHand();
	cout << "\n";
	printProvinces();
	cout << "\n";
	cout << pname << ": End of Starting Phase." << endl;
}

void Player::equipPhase() {
	string buycard;
	string person;
	string chosenhold;
	char status;
	char bs;
	Personality *selectedperson;
	Holding* selectedhold;
	GreenCard *boughtcard;
	cout << "\n" << pname << ": Equip Phase." << endl;
	if (army.get_size() != 0) {
		do {
			do {
				cout << "Type Y to buy a Card or N to skip." << endl;
				cin >> bs;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			} while (bs != 'Y' && bs != 'N');
			if (bs == 'Y') {
				cout << pname << " cards in Hand:" << endl;
				hand.Greenprint();
				do {
					cout
							<< "Choose a card from Hand to buy or type STOP to stop"
							<< endl;
					buycard = windowsreadcorrection();
				} while (buycard != "STOP"
						&& (boughtcard = hand.getGreenNode(buycard)) == NULL);
				if (buycard != "STOP") {
					boughtcard->examineCard();
					cout << "\nArmy:" << endl;
					army.printArmyStats();
					cout << "Type B to buy the card or S to skip." << endl;
					do {
						cin >> status;
						cin.clear();
						cin.ignore(INT_MAX, '\n');
					} while (status != 'S' && status != 'B');
					if (status == 'S')
						hand.GreenpushBack(boughtcard);
					if (buycard != "STOP" && status != 'S') {
						cout << "The cost for " << boughtcard->getName()
								<< " is " << boughtcard->getCost()
								<< " and the bonus cost is "
								<< boughtcard->geteffectCost() << "." << endl;
						do {
							cout << pname << "'s Holdings available to tap:"
									<< endl;
							holding.printUntapped();
							cout << "Available Gold: " << money << endl;
							cout
									<< "Choose Holding to tap or type STOP to exit!"
									<< endl;
							chosenhold = windowsreadcorrection();
							if (chosenhold == "STOP"
									&& money < boughtcard->getCost()) {
								cout
										<< "Are you sure you want to stop? "
												"The cost of the item is not yet covered. "
												"You will lose all the tapped money. Type Y to stop or N to continue"
										<< endl;
								do {
									cin >> status;
									cin.clear();
									cin.ignore(INT_MAX, '\n');
									if (status == 'N') {
										chosenhold = "asd";
									}
								} while (status != 'Y' && status != 'N');
							}
							if (chosenhold != "STOP") {
								selectedhold = holding.getHolding(chosenhold);
								if (selectedhold != NULL) {
									if (selectedhold->getTap() == false) {
										selectedhold->Tap();
										money +=
												(selectedhold->getharvestValue());
									} else
										cout << selectedhold->getName()
												<< " is alreay Tapped!" << endl;
								}
							}
						} while (chosenhold != "STOP"
								&& (money
										< boughtcard->getCost()
												+ boughtcard->geteffectCost()));
						if (boughtcard->getCost() <= money) {
							do {
								cout << pname << "'s Army:" << endl;
								army.Blackprint();
								cout
										<< "Choose a personality from your army to attach "
										<< boughtcard->getName()
										<< ", or type STOP to exit." << endl;
								person = windowsreadcorrection();
								if (person != "STOP")
									selectedperson = army.getPersonality(
											person);
							} while (selectedperson == NULL
									&& (person != "STOP"));
							if (selectedperson != NULL
									&& selectedperson->canAttach(
											boughtcard->getType(),
											boughtcard->getminimumHonour())
											== false) {
								person = "STOP";
							}
							if (person != "STOP") {
								cout << boughtcard->getName() << " attached to "
										<< selectedperson->getName() << endl;
								selectedperson->attach(boughtcard);
								money = money - boughtcard->getCost();
								if (money >= boughtcard->geteffectCost()) {
									cout
											<< "Do you want to activate effect Bonus ? "
													"Type Y to activate or N to waste your money!"
											<< endl;
									do {
										cin >> status;
										cin.clear();
										cin.ignore(INT_MAX, '\n');
									} while (status != 'Y' && status != 'N');
									if (status == 'Y') {
										money = 0;
										boughtcard->activateeffect();
									}
								}
							} else {
								if (money)
									cout << "GRATZ! You just lost " << money
											<< " Gold!" << endl;
								money = 0;
								hand.GreenpushBack(boughtcard);
							}
						} else {
							if (money)
								cout << "GRATZ! You just lost " << money
										<< " Gold!" << endl;
							hand.GreenpushBack(boughtcard);
						}
					}
				}
			}
		} while (bs != 'N' && buycard != "STOP");
	} else {
		cout << pname << " has no personalities to equip!" << endl;
	}
	cout << pname << ": End of Equip Phase." << endl;
}

void Player::battlePhase(Player &p) {
	TypeConverter converter;
	BlackList attackers;
	BlackList defenders;
	Personality *person;
	Holding *hold;
	char status;
	int selectprov, p1attackpoints, p2defensepoints, dif;
	cout << "\n" << pname << ": Battle Phase." << endl;
	if (army.get_size() != 0) {
		do {
			cout << "Do you want to attack " << p.getpname()
					<< " ? (type Y to attack or N to not attack)" << endl;
			cin >> status;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		} while (status != 'N' && status != 'Y');
		if (status == 'Y') {
			p.provinces.Blackprint();
			do {
				cout
						<< "Choose a province to attack (type 1 for first, 2 for second, etc...)"
						<< endl;
				cin >> selectprov;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			} while (selectprov < 1 || selectprov > 4);
			p1attackpoints = this->calculateAttack(&attackers);
			p2defensepoints = p.calculateDefense(&defenders);
			dif = p1attackpoints - p2defensepoints;
			if (dif > p.getinitialDefense()) {
				cout << this->getpname() << " destroys " << p.getpname()
						<< "' s Province" << endl;
				p.destroyProvince(selectprov);
				while (attackers.get_size() != 0) {
					army.BlackpushBack(attackers.getBlackNode());
				}
				defenders.~BlackList();
			} else {
				if (dif > 0) {
					cout << this->getpname() << " can't destroy "
							<< p.getpname()
							<< "' s Province but kills all of his defenders"
							<< endl;
					while (attackers.get_size() != 0) {
						converter.getCorrectType(attackers.getBlackNode(),
								&person, &hold);
						if (person->getAttack() < dif) {
							person->BattleResults(dif, 'A');
							army.BlackpushBack(person);
						} else {
							delete person;
						}
					}
					defenders.~BlackList();
				} else if (dif == 0) {
					cout << "Everyone DIES!" << endl;
					attackers.~BlackList();
					defenders.~BlackList();
				} else if (dif < 0) {
					cout << this->getpname() << " can't destroy "
							<< p.getpname()
							<< "' s Province and all his attackers DIE!"
							<< endl;
					while (defenders.get_size() != 0) {
						converter.getCorrectType(defenders.getBlackNode(),
								&person, &hold);
						if (person->getAttack() < dif) {
							person->BattleResults(dif, 'D');
							p.army.BlackpushBack(person);
						} else {
							delete person;
						}
					}
					attackers.~BlackList();
				}
			}
		}
	} else {
		cout << this->getpname() << " has no army to attack with." << endl;
	}
	cout << pname << ": End of Battle Phase." << endl;
}

void Player::economyPhase() {
	int pos = -1;
	char type, status;
	TypeConverter converter;
	string buycard, chosenhold;
	BlackCard *boughtcard;
	Holding *selectedhold, *finalhold;
	Personality *finalperson;
	cout << "\n" << pname << ": Economy Phase." << endl;
	revealProvinces();
	cout << "\n";
	do {
		cout << "You have " << money << " Gold.\n" << endl;
		do {
			cout << "Type B to buy or S to skip" << endl;
			cin >> type;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		} while (type != 'B' && type != 'S');
		cout << "\n";
		if (type == 'B') {
			printProvinces();
			cout << "\n";
			do {
				cout
						<< "Choose a card from Provinces to buy or type STOP to exit"
						<< endl;
				buycard = windowsreadcorrection();
			} while (buycard != "STOP"
					&& ((boughtcard = provinces.getBlackNode(buycard, &pos))
							== NULL));
			if (buycard == "STOP")
				break;
			cout << "\n";
			cout << "The cost for " << boughtcard->getName() << " is "
					<< boughtcard->getCost() << endl;
			cout << "\n";
			if (money >= boughtcard->getCost()) {
				cout << "Cost covered... You have " << money << " Gold" << endl;
			} else {
				if (holding.getNoAvailable() != 0) {
					do {
						cout << pname << "'s Holdings available to tap:"
								<< endl;
						holding.printUntapped();
						cout << "\n";
						cout << "Available Gold: " << money << endl;
						cout << "Choose Holding to tap or type STOP to exit!\n"
								<< endl;
						chosenhold = windowsreadcorrection();
						if (chosenhold == "STOP"
								&& money < boughtcard->getCost()) {
							cout << "\n";
							cout
									<< "Are you sure you want to stop? "
											"The cost of the item is not yet covered. "
											"You will lose all the tapped money. Type Y to stop or N to continue"
									<< endl;
							do {
								cin >> status;
								cin.clear();
								cin.ignore(INT_MAX, '\n');
								if (status == 'N') {
									chosenhold = "asd";
								}
							} while (status != 'Y' && status != 'N');
						}
						if (chosenhold != "STOP") {
							selectedhold = holding.getHolding(chosenhold);
							if (selectedhold != NULL) {
								if (selectedhold->getTap() == false) {
									selectedhold->Tap();
									money = money
											+ (selectedhold->getharvestValue());
								} else {
									cout << "\n";
									cout << "CHEATER!! This card is Tapped."
											<< endl;
								}
							}
						}
					} while (chosenhold != "STOP"
							&& money < boughtcard->getCost());
				}
			}
			if (boughtcard->getCost() <= money) {
				converter.getCorrectType(boughtcard, &finalperson, &finalhold);
				if (finalperson == NULL) {
					finalhold->Tap();
					finalhold->reveal();
					cout << "\n" << endl;
					if (finalhold->getHoldingType() == MINE
							|| finalhold->getHoldingType() == CRYSTAL_MINE
							|| finalhold->getHoldingType() == GOLD_MINE)
						holding.checkforChain(finalhold);
					holding.BlackpushBack(finalhold);
				} else {
					finalperson->reveal();
					army.BlackpushBack(finalperson);
				}
				if (DynastyDeck->size() != 0)
					drawDynastyCard(pos);
				else
					cout << this->getpname() << ": The Dynasty Deck is empty."
							<< endl;
				cout << "\n";
				cout << "You just bought " << boughtcard->getName() << "!\n"
						<< endl;
				cout << "\nYou wasted " << money - boughtcard->getCost()
						<< " Gold." << endl;
				money = 0;
			} else {
				cout << "\n";
				if (money)
					cout << "GRATZ! You just lost " << money << " Gold!"
							<< endl;
				money = 0;
				provinces.Blackpush(boughtcard, pos);
			}
		}
	} while (type != 'S' && holding.getNoAvailable() != 0);
	if (!holding.getNoAvailable())
		cout << "\n" << pname << ": No Holdings Available." << endl;
	cout << pname << ": End of Economy Phase." << endl;
}

void Player::finalPhase() {
	string c;
	cout << "\n" << pname << ": Final Phase." << endl;
	while (hand.get_size() > MAX_HAND_SIZE) {
		cout << "\n" << getpname() << ": ";
		cout << "You must discard " << (hand.get_size() - MAX_HAND_SIZE)
				<< " cards from your hand!" << endl;
		hand.Greenprint();
		do {
			cout << "Choose a card to discard" << endl;
			c = windowsreadcorrection();
		} while (hand.deleteGreenNode(c) == false);
	}
	if (provinces.AllRevealed() == true) {
		cout << "\n" << getpname() << ": ";
		cout
				<< "You can discard a card from your provinces and draw a new one from the Dynasty Deck."
				<< endl;
		provinces.Blackprint();
		do {
			cout << "Choose a card to discard or type STOP to skip." << endl;
			c = windowsreadcorrection();
		} while (c != "STOP" && provinces.deleteBlackNode(c) == false);
		if (c != "STOP")
			drawDynastyCard();
	}
	cout << pname << ": End of Final Phase" << endl;
}

string windowsreadcorrection() {
	string line;
	getline(cin, line);
	if (*line.rbegin() == '\r') {
		line.erase(line.length() - 1);
	}
	return line;
}

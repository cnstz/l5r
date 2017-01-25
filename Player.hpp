/*
 * Player.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#define MAX_HAND_SIZE 7
#define STARTING_HAND 6

#include <list>
#include <string>
#include "GreenList.hpp"
#include "BlackList.hpp"
#include "DeckBuilder.hpp"

class Player {
private:
	DeckBuilder Deck;
	std::list<GreenCard*>* FateDeck;
	std::list<BlackCard*>* DynastyDeck;
	GreenList hand;
	BlackList holding;
	BlackList army;
	BlackList provinces;
	std::string pname;
	int numberOfProvinces, honour, money, initialDefense;
	Stronghold *stronghold;
public:
	Player(std::string);

	~Player();

	int gethonour();
	int getprovinces();
	int getinitialDefense();
	int calculateAttack(BlackList*);
	int calculateDefense(BlackList*);
	std::string getpname();
	void untapEverything();
	void drawFateCard();
	void drawDynastyCard();
	void drawDynastyCard(int);
	void destroyProvince(int);
	void revealProvinces();
	void printHand();
	void printProvinces();
	void printArena();
	void printHoldings();
	void startingPhase();
	void equipPhase();
	void battlePhase(Player&);
	void economyPhase();
	void finalPhase();
};

std::string windowsreadcorrection();

#endif /* _PLAYER_HPP_ */

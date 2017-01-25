/*
 * Personality.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _PERSONALITY_HPP_
#define _PERSONALITY_HPP_

#define NO_MAXFOLLOWERS 5
#define NO_MAXITEMS 3

#include "BlackCard.hpp"
#include "Follower.hpp"
#include "Item.hpp"

enum {
	ATTACKER = 1, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION,
};

class Personality: public BlackCard {
private:
	int attack, defense, honour, no_followers, no_items;
	bool isDead;
	static int uniqueIDseed;
	int ID;
	Follower *attachedFollowers[NO_MAXFOLLOWERS];
	Item *attachedItems[NO_MAXITEMS];
public:

	Personality(std::string, int);
	~Personality();
	void examineCard();
	int getAttack();
	int getID();
	int getDefense();
	void performSeppuku();
	void BattleResults(int, char);
	void attach(GreenCard*);
	bool canAttach(int, int);
};

#endif /* _PERSONALITY_HPP_ */

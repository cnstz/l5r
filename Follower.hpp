/*
 * Follower.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _FOLLOWER_HPP_
#define _FOLLOWER_HPP_

#include "GreenCard.hpp"

enum {
	FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO
};

class Follower: public GreenCard {
private:
public:

	Follower(std::string n, int t);
	~Follower();
	void detach();
	void examineCard();
};

#endif /* _FOLLOWER_HPP_ */

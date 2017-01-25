/*
 * BlackList.hpp
 *
 *  Created on: 3 Ìבס 2013
 *      Author: Constantine
 */

#ifndef _BLACKLIST_HPP_
#define _BLACKLIST_HPP_
#include "TypeConverter.hpp"

struct BlackNode {
	// komvos dipla sindedemenhs listas
	BlackCard *data;
	BlackNode *next;								// deikths sto epomeno node
	BlackNode *previous;						// deikths sto prohgoumeno node
	BlackNode(BlackCard*, BlackNode*, BlackNode*);
	~BlackNode();
};

class BlackList {
private:
	BlackNode* _head;
	BlackNode* _tail;
	int _size;
public:
	BlackList();
	~BlackList();

	/* SETTERS */
	void BlackunTap(std::string);
	void reveal();

	/* GETTERS */
	int get_size();
	int getNoAvailable();				// epistrofh arithmou UnTapped Kartwn
	BlackNode * get_head();
	BlackCard* getBlackNode(std::string, int*);	// epistrofh kartas me delete tou node
	Personality* getArmyBlackNode(std::string);	// epistrofh kartas me delete tou node
	BlackCard* getBlackNode();	// epistrofh prwths kartas me delete tou node
	Holding * getHolding(std::string);					// access node data
	Personality * getPersonality(std::string);			// access node data
	bool AllRevealed();

	/* */
	bool deleteBlackNode(std::string);			// diagrafh enos node kai data
	void BlackpushBack(BlackCard*);
	void Blackpush(BlackCard*, int);				// topothethsh se thesh
	void Blackprint();							// ektypwsh ths listas
	void printArmyStats();
	void printUntapped();		// ektypwsh twn Untapped ths listas
	void checkforChain(Holding *);

};

#endif /* _BLACKLIST_HPP_ */

/*
 * GreenList.hpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#ifndef _GREENLIST_HPP_
#define _GREENLIST_HPP_

#include <string>
#include "GreenCard.hpp"

struct GreenNode {
	GreenCard *data;
	GreenNode *next;
	GreenNode *previous;
	GreenNode(GreenCard*, GreenNode*, GreenNode*);
	~GreenNode();
};

class GreenList {
private:
	GreenNode* _head;
	GreenNode* _tail;
	int _size;
public:

	GreenList();
	~GreenList();

	/* SETTERS */
	void GreenunTap(std::string);

	/* GETTERS */
	int get_size();
	GreenCard* getGreenNode(std::string);

	void GreenpushBack(GreenCard*);
	bool deleteGreenNode(std::string);
	void Greenprint();
};

#endif /* _GREENLIST_HPP_ */

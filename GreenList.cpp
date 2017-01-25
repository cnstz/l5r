/*
 * GreenList.cpp
 *
 *  Created on: 24 ÷Â‚ 2013
 *      Author: Constantine
 */

#include <iostream>
#include "GreenList.hpp"

using namespace std;

GreenNode::GreenNode(GreenCard* s, GreenNode* p = NULL, GreenNode* n = NULL) :
		data(s), next(n), previous(p) {
}

GreenNode::~GreenNode() {
}

GreenList::GreenList() :
		_head(NULL), _tail(NULL), _size(0) {
}

GreenList::~GreenList() {
	GreenNode* current = _head;
	while (current != NULL) {
		GreenNode* next = current->next;
		delete current->data;
		delete current;
		current = next;

	}
	_head = NULL;
	_tail = NULL;
}

/* SETTERS */
void GreenList::GreenunTap(string h) {
	if (_size == 0)
		cout << "-Nothing to untap in " << h << "." << endl;
	else {
		GreenNode *temp = _head;
		do {
			temp->data->unTap();

			temp = temp->next;
		} while (temp != NULL);
		cout << "-Everything untapped in " << h << "." << endl;
	}
}

/* GETTERS */
int GreenList::get_size() {
	return _size;
}

GreenCard* GreenList::getGreenNode(string name) {
	GreenNode *temp = _head;
	GreenCard *tempcard;
	if (_head != NULL) {
		if (_head->data->getName() == name) {
			tempcard = _head->data;
			_head = _head->next;
			if (_head != NULL)
				_head->previous = NULL;
			_size--;
			delete temp;
			return tempcard;
		} else {
			while (temp->next != NULL) {
				temp = temp->next;
				if (temp->data->getName() == name) {
					tempcard = temp->data;
					temp->previous->next = temp->next;
					if (temp->next != NULL)
						temp->next->previous = temp->previous;
					else {
						_tail = temp->previous;
					}
					_size--;
					delete temp;
					return tempcard;
				}
			}
		}
		cout << "Didn't find card with name: " << name << endl;
	}
	return NULL;
}

/* */
void GreenList::GreenpushBack(GreenCard *card) {
	if (_head == NULL) {
		_head = new GreenNode(card);
		_tail = _head;
	} else {
		_tail->next = new GreenNode(card, _tail);
		_tail = _tail->next;
	}
	_size++;
}

bool GreenList::deleteGreenNode(string name) {
	if (_size != 0) {
		GreenNode *temp = _head;
		GreenNode *temp2;
		if (_head->data->getName() == name) {
			_head = _head->next;
			if (_head != NULL)
				_head->previous = NULL;
			delete temp->data;
			delete temp;
			_size--;
			return true;
		} else {
			while (temp->next != NULL) {
				temp = temp->next;
				temp2 = temp;
				if (temp->data->getName() == name) {
					temp->previous->next = temp->next;
					if (temp->next != NULL)
						temp->next->previous = temp->previous;
					else {
						_tail = temp->previous;
					}
					delete temp2->data;
					delete temp2;
					_size--;
					return true;
				}
			}
		}
		cout << "Didn't find card with name: " << name << endl;
		return false;
	}
	cout << "No cards left!" << endl;
	return false;
}

void GreenList::Greenprint() {
	GreenNode *temp = _head;
	do {
		cout << "-" << temp->data->getName() << " costs "
				<< temp->data->getCost() << " gold." << endl;
		temp = temp->next;
	} while (temp != NULL);
}

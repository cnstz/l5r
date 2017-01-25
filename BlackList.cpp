/*
 * BlacList.cpp
 *
 *  Created on: 3 Ìבס 2013
 *      Author: Constantine
 */

#include "BlackList.hpp"
#include <list>
#include <iostream>

using namespace std;

BlackNode::BlackNode(BlackCard* s, BlackNode* p = NULL, BlackNode* n = NULL) :
		data(s), next(n), previous(p) {
}

BlackNode::~BlackNode() {
}

BlackList::BlackList() :
		_head(NULL), _tail(NULL), _size(0) {
}

BlackList::~BlackList() {
	BlackNode* current = _head;
	while (current != NULL) {
		BlackNode* next = current->next;
		delete current->data;
		delete current;
		current = next;
	}
	_head = NULL;
	_tail = NULL;
}

/* SETTERS */
void BlackList::BlackunTap(string h) {
	/* Kanei unTap olh thn Black List
	 * to string h einai to onoma ths listas
	 * sthn opoia kanei untouch */
	if (_size == 0)
		cout << "-Nothing to untap in " << h << "." << endl;
	else {
		BlackNode *temp = _head;
		do {
			temp->data->unTap();

			temp = temp->next;
		} while (temp != NULL);
		cout << "-Everything untapped in " << h << "." << endl;
	}
}

void BlackList::reveal() {
	/* Kanei reveal oles tis Provinces */
	BlackNode *temp = _head;
	do {
		temp->data->reveal();
		temp = temp->next;
	} while (temp != NULL);
	cout << "All provinces revealed!" << endl;
}

/* GETTERS */
int BlackList::get_size() {
	return _size;
}

int BlackList::getNoAvailable() {
	BlackNode *temp = _head;
	int i = 0;
	while (temp != NULL) {
		if (temp->data->getTap() == false) {
			i++;
		}
		temp = temp->next;
	}
	return i;
}

BlackNode * BlackList::get_head() {
	return _head;
}

BlackCard* BlackList::getBlackNode(string name, int *position) {
	/* Epistrefei th Card me to onoma name kai th thesh ths
	 * kai kanei delete to node sto opoio vriskotan.
	 * H thesh xrisimopoieitai otan theloyme na antikatasthsoume
	 * kati pou agorasame apo ta provinces
	 */
	BlackNode *temp = _head;
	BlackCard *tempcard;
	*position = 0;
	if (_head != NULL) {
		if (_head->data->getName() == name
				&& _head->data->getisRevealed() == true) {
			tempcard = _head->data;
			_head = _head->next;
			if (_head != NULL)
				_head->previous = NULL;
			delete temp;
			_size--;
			return tempcard;
		} else {
			while (temp->next != NULL) {
				(*position)++;
				temp = temp->next;
				if (temp->data->getName() == name) {
					if (temp->data->getisRevealed() == true) {
						tempcard = temp->data;
						temp->previous->next = temp->next;
						if (temp->next != NULL)
							temp->next->previous = temp->previous;
						else {
							_tail = temp->previous;
						}
						delete temp;
						_size--;
						return tempcard;
					}
				}
			}

		}
		cout << "Didn't find card with name: " << name << endl;
	}
	return NULL;
}

Personality* BlackList::getArmyBlackNode(string name) {
	/* Elegxei gia iparxontes komvous simfwna me to name,
	 * kai kataxwrei ta id tous se mia lista.
	 * An vrei parapanw apo 1 komvous me to idio name
	 * rwtaei ton paixth pio thelei na xrhsimopoihsei simfwna me to unique ID
	 * Epistrefei Personality kai kanei delete to antistoixo node*/
	BlackNode *temp = _head;
	string asd;
	int selectedID;
	int pf = -1;
	bool flag = false;
	Personality *tempcard;
	Holding *temphold;
	TypeConverter converter;
	list<int> tempList;
	while (temp != NULL) {
		if (temp->data->getName() == name) {
			if (temp->data->getTap() == false) {
				//temp->data->examineCard();
				converter.getCorrectType(temp->data, &tempcard, &temphold);
				tempList.push_back(tempcard->getID());
			}
		}
		temp = temp->next;
	}
	if (tempList.size() == 1) {
		converter.getCorrectType(getBlackNode(name, &pf), &tempcard, &temphold);
		return tempcard;
	} else {
		do {
			cout
					<< "There are multiple personalities with that name, please choose a Personality ID."
					<< endl;
			cin >> selectedID;
			for (list<int>::const_iterator it = tempList.begin();
					it != tempList.end(); ++it) {
				if ((*it) == selectedID) {
					flag = true;
				}
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		} while (flag == false);
		temp = _head;
		while (temp != NULL) {
			converter.getCorrectType(temp->data, &tempcard, &temphold);
			if (tempcard->getID() == selectedID) {
				if (temp == _head) {
					_head = _head->next;
					if (_head != NULL)
						_head->previous = NULL;
					delete temp;
					_size--;
				} else {
					temp->previous->next = temp->next;
					if (temp->next != NULL)
						temp->next->previous = temp->previous;
					else {
						_tail = temp->previous;
					}
					delete temp;
					_size--;
				}
				return tempcard;
			}
			temp = temp->next;
		}
		return NULL;
	}
}

BlackCard * BlackList::getBlackNode() {
	BlackNode *temp = _head;
	BlackCard *tempcard;
	if (_head != NULL) {
		tempcard = temp->data;
		_head = _head->next;
		if (_head != NULL)
			_head->previous = NULL;
		delete temp;
		_size--;
		return tempcard;
	} else
		return NULL;
}

Holding* BlackList::getHolding(string hold) {
	BlackNode *temp = _head;
	Personality *temppersoncard;
	Holding *tempholdcard;
	TypeConverter converter;
	while (temp != NULL) {
		if (temp->data->getName() == hold) {
			if (temp->data->getTap() == false) {
				converter.getCorrectType(temp->data, &temppersoncard,
						&tempholdcard);

				return tempholdcard;
			}
		}
		temp = temp->next;
	}
	cout << "Didn't find card with name: " << hold << endl;
	return NULL;
}

Personality* BlackList::getPersonality(string person) {
	/* Elegxei gia iparxontes komvous simfwna me to name,
	 * kai kataxwrei ta id tous se mia lista.
	 * An vrei parapanw apo 1 komvous me to idio name
	 * rwtaei ton paixth pio thelei na xrhsimopoihsei simfwna me to unique ID.
	 * Epistrefei Personality*/
	BlackNode *temp = _head;
	int selectedID;
	bool flag = false;
	Personality *temppersoncard;
	Holding *tempholdcard;
	TypeConverter converter;
	list<int> tempList;
	while (temp != NULL) {
		if (temp->data->getName() == person) {
			converter.getCorrectType(temp->data, &temppersoncard,
					&tempholdcard);
			temppersoncard->examineCard();
			tempList.push_back(temppersoncard->getID());
		}
		temp = temp->next;
	}
	if (tempList.size() == 0) {
		cout << "Didn't find card with name: " << person << endl;
		return NULL;
	} else if (tempList.size() == 1) {
		return temppersoncard;
	} else {
		do {
			cout
					<< "\nThere are multiple personalities with that name, please choose a Personality ID"
					<< endl;
			cin >> selectedID;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (list<int>::const_iterator it = tempList.begin();
					it != tempList.end(); ++it) {
				if ((*it) == selectedID) {
					flag = true;
				}
			}
		} while (flag == false);
		temp = _head;
		while (temp != NULL) {
			converter.getCorrectType(temp->data, &temppersoncard,
					&tempholdcard);
			if (temppersoncard->getID() == selectedID) {
				return temppersoncard;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

bool BlackList::AllRevealed() {
	/* Epistrefei an einai oloi Revealed, dhladh
	 * an egine h oxi agora se ayto to gyro.
	 * An den egine dinoume ston paixth thn epilogh
	 * na petaksei mia karta kai na traviksei kainuria*/
	BlackNode *temp = _head;
	while (temp != NULL) {
		if (temp->data->getisRevealed() == false) {
			return false;
		}
		temp = temp->next;
	}
	return true;
}

/* */
bool BlackList::deleteBlackNode(string name) {
	/* Diagrafei ena Black Node symfwna me to onoma */
	if (_size != 0) {
		BlackNode *temp = _head;
		BlackNode *temp2;
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

void BlackList::BlackpushBack(BlackCard *card) {
	/* Topotheth th card sto telos ths listas */
	if (_head == NULL) {
		_head = new BlackNode(card);
		_tail = _head;
	} else {
		_tail->next = new BlackNode(card, _tail);
		_tail = _tail->next;
	}
	_size++;
}

void BlackList::Blackpush(BlackCard *card, int position) {
	/* Topothetei th card se sygekrimenh thesh ths listas */
	BlackNode *temp = new BlackNode(card);
	BlackNode *temp2 = _head;
	int i;
	if (_size == 0)
		BlackpushBack(card);
	else {
		if (position == 0) {
			_head->previous = temp;
			temp->next = _head;
			temp->previous = NULL;
			_head = temp;
		} else if (position == _size) {
			_tail->next = temp;
			temp->previous = _tail;
			temp->next = NULL;
			_tail = temp;
		} else {
			for (i = 0; i < position; i++) {
				temp2 = temp2->next;
			}
			(temp2->previous)->next = temp;
			temp->previous = temp2->previous;
			temp->next = temp2;
			temp2->previous = temp;
		}
		_size++;
	}
}

void BlackList::Blackprint() {
	/* Ektypwnei olh th lista.
	 * An kati den einai Revealed emfanizei HIDDEN
	 * sth thesh tou.*/
	BlackNode *temp = _head;
	while (temp != NULL) {
		if (temp->data->getisRevealed() == true)
			cout << "-" << temp->data->getName() << endl;
		else
			cout << "HIDDEN" << endl;
		temp = temp->next;
	}
}

void BlackList::printArmyStats() {
	BlackNode *temp = _head;
	while (temp != NULL) {
		temp->data->examineCard();
		temp = temp->next;
	}
}

void BlackList::printUntapped() {
	/* Ektypwnei oses kartes einai Untapped */
	BlackNode *temp = _head;
	while (temp != NULL) {
		if (temp->data->getTap() == false) {
			temp->data->examineCard();
		}
		temp = temp->next;
	}
}

void BlackList::checkforChain(Holding *hold) {
	/* Elegxei an to hold borei na dimiourghsei allisida
	 * me kapoio allo typo oryxeiou (an vrethei kapoios sth lista)
	 */
	BlackNode *temp = _head;
	TypeConverter converter;
	Holding * temphold;
	Personality *tempperson;
	bool flag = false, goldflag = false;
	switch (hold->getHoldingType()) {
	case MINE:
		while (temp != NULL && flag == false) {
			converter.getCorrectType(temp->data, &tempperson, &temphold);
			if (temphold->getHoldingType() == GOLD_MINE) {
				flag = temphold->appendLowerHolding(hold);
			}
			temp = temp->next;
		}
		break;
	case GOLD_MINE:
		while (temp != NULL && (flag == false || goldflag == false)) {
			converter.getCorrectType(temp->data, &tempperson, &temphold);
			if (flag == false && temphold->getHoldingType() == MINE) {
				flag = temphold->appendUpperHolding(hold);
			} else if (goldflag == false
					&& temphold->getHoldingType() == CRYSTAL_MINE) {
				goldflag = temphold->appendLowerHolding(hold);
			}
			temp = temp->next;
		}
		break;
	case CRYSTAL_MINE:
		while (temp != NULL) {
			converter.getCorrectType(temp->data, &tempperson, &temphold);
			if (temphold->getHoldingType() == GOLD_MINE) {
				flag = temphold->appendUpperHolding(hold);
			}
			temp = temp->next;
		}
		break;
	}
}

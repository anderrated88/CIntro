/*
 * NonTerminal.cpp
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#include <sstream>

#include "NonTerminal.h"
#include "Terminal.h"

NonTerminal::NonTerminal() :
		Symbol() {

}

NonTerminal::NonTerminal(std::string function, bool isHead, int start, int end) :
		Symbol(function, isHead, start, end) {

}

NonTerminal::NonTerminal(std::string function, int start, int end) :
		Symbol(function, start, end) {

}
NonTerminal::NonTerminal(std::string function, bool isHead) :
		Symbol(function, isHead) {

}

NonTerminal::NonTerminal(std::string function) :
		Symbol(function) {

}

NonTerminal::NonTerminal(const NonTerminal& nonTerminal) :
		Symbol(nonTerminal) {

	this->children.resize(nonTerminal.children.size());
	this->ordered.resize(nonTerminal.ordered.size());

	std::size_t numOfOrdered = this->ordered.size();
	for (std::size_t ci = 0; ci < numOfOrdered; ci++) {
		this->ordered[ci] = nonTerminal.ordered[ci];
	}

	std::size_t numOfChild = this->children.size();
	for (std::size_t ci = 0; ci < numOfChild; ci++) {
		this->children[ci] = nonTerminal.children[ci];
	}

}

NonTerminal::~NonTerminal() {
}

bool NonTerminal::isNonTerminal() const {
	return true;
}

bool NonTerminal::isTerminal() const {
	return false;
}

std::string NonTerminal::toString() const {
	std::stringstream ss;

	ss << "(";
	if (!this->symbol.empty()) {
		ss << this->symbol << " ";
	}

	std::size_t numOfChildren = children.size();
	if (numOfChildren == 0) {
		ss << "*";
	} else {
		for (std::size_t ci = 0; ci < numOfChildren; ci++) {
			if (children[ci] == NULL) {
				ss << "NULL";
			} else {
				ss << children[ci]->toString();
			}

			if (ci != numOfChildren - 1) {
				ss << " ";
			}
		}
	}
	ss << ")";

	return ss.str();
}

void NonTerminal::push_back(Symbol *child) {

	children.push_back(child);

}

NonTerminal* NonTerminal::nonTerminal() {
	return this;
}

Terminal* NonTerminal::terminal() {
	return NULL;
}

/**
 * \param ordered set vector ordered
 */
void NonTerminal::setOrdered(std::vector<int> ordered) {
	this->ordered.resize(ordered.size());
	std::size_t sizeOfIndex = ordered.size();

	for (std::size_t ci = 0; ci < sizeOfIndex; ci++) {
		this->ordered[ci] = ordered[ci];
	}
}

int NonTerminal::getOrderedAt(std::size_t orderedIndex) {
	int retVal = -1;

	if (orderedIndex < 0 || orderedIndex >= this->ordered.size()) {
		std::cerr << "getOrderedAt: error with index: " << orderedIndex << "'"
				<< std::endl;
	} else {
		retVal = this->ordered[orderedIndex];
	}

	return retVal;
}

/**
 * check non-terminal is match or not
 * <br /> two non-terminal is match if
 *  both symbol is non-terminal
 *  same function and same status is head
 *  and children is same size, finally each element in children is same
 *
 * @param symbol - symbol need to check
 * @return two non-terminal is same or not
 */
bool NonTerminal::isMatch(Symbol * symbol) {
	bool retVal = false;

	//both symbol is non-terminal
	if (symbol->isNonTerminal()) {
		NonTerminal * tmp = symbol->nonTerminal();

		//same function and same head
		retVal = (this->symbol.compare(tmp->symbol) == 0)
				&& this->isHead == tmp->isHead;

		if (retVal) {

			if (this->children.size() == 0 && tmp->children.size() != 0) {
				retVal = true;
			} else if (this->children.size() != 0
					&& tmp->children.size() == 0) {
				retVal = true;
			} else {

				//child is same size
				retVal = this->children.size() == tmp->children.size();

				if (retVal) {
					std::size_t numOfChild = this->children.size();

					//check each child in list
					for (size_t ci = 0; ci < numOfChild; ci++) {
						retVal = this->children[ci]->isMatch(tmp->children[ci]);

						if (!retVal) {
							break;
						}
					}

				} //end check each element
			} //end special case for size
		} //end if same function and head

	} //end check both non terminal

	return retVal;
}

Symbol * NonTerminal::getChildrenAt(int idx) {
	if (idx < 0 || idx >= (int) children.size()) {
		return NULL;
	}

	return children[idx];
}

void NonTerminal::setElementAt(Symbol * symbol, int idx) {
	if (idx >= 0 && idx < (int) children.size()) {
		children[idx] = symbol;
	}
}

int NonTerminal::sizeOfChildren() const {
	return (int) children.size();
}

std::vector<int> NonTerminal::getOrdered() const {
	return ordered;
}

std::string NonTerminal::getSentence() {
	std::stringstream ss;
	bool isUsedOrder = false;

	if (ordered.size() != 0) {
		isUsedOrder = true;
	}

	std::size_t numOfElement = children.size();
	if (isUsedOrder) {
		numOfElement = ordered.size();
	}

	for (size_t ci = 0; ci < numOfElement; ci++) {
		size_t cj = ci;
		if (isUsedOrder) {
			cj = ordered[ci];
		}
		ss << children[cj]->getSentence();
		if (ci != numOfElement - 1) {
			ss << " ";
		}
	}

	return ss.str();
}

/**
 * check non-terminal is match with a symbol
 * condition:
 * 		same function
 * 		same length
 * 		same children
 * @param symbol
 * @return
 */
bool NonTerminal::isRuleMatch(Symbol * symbol) {
	bool b = false;
	if (symbol->isNonTerminal()) {
		b = this->getSymbol() == symbol->getSymbol();
		if (b) {
			b = this->sizeOfChildren()
					== symbol->nonTerminal()->sizeOfChildren();

			if (b) {

				int size = this->children.size();
				for (int i = 0; i < size; i++) {
					b =
							children[i]->getSymbol()
									== symbol->nonTerminal()->getChildrenAt(i)->getSymbol();
					if (!b) {
						break;
					}
				}
			}
		}
	}

	return b;
}

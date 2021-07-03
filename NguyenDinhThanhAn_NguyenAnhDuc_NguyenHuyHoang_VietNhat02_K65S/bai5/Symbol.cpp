/*
 * Symbol.cpp
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#include "Symbol.h"

Symbol::Symbol() {
	this->symbol = "";
	this->isHead = false;
	this->start = 0;
	this->end = 1;
}

Symbol::~Symbol() {
	// TODO Auto-generated destructor stub
}

Symbol::Symbol(std::string symbol, bool isHead, int start, int end) {
	this->symbol = symbol;
	this->isHead = isHead;
	this->start = start;
	this->end = end;
}

Symbol::Symbol(std::string symbol, bool isHead) {
	this->symbol = symbol;
	this->isHead = isHead;
}

Symbol::Symbol(std::string symbol, int start, int end) {
	this->symbol = symbol;
	this->isHead = false;
	this->start = start;
	this->end = end;
}

Symbol::Symbol(std::string symbol) {
	this->symbol = symbol;
	this->isHead = false;
	this->start = 0;
	this->end = 1;
}

///
/// getter function
std::string Symbol::getSymbol() const {
	return this->symbol;
}

bool Symbol::getIsHead() const {
	return isHead;
}

int Symbol::getStart() const {
	return start;
}

int Symbol::getEnd() const {
	return end;
}

int Symbol::getHeight () const {
	return height;
}

void Symbol::setHeight (int height){
	this->height = height;
}

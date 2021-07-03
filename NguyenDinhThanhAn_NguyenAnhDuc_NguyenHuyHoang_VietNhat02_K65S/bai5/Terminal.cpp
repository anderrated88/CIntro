/*
 * Terminal.cpp
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#include <sstream>

#include "NonTerminal.h"
#include "Terminal.h"

Terminal::Terminal() {
	// TODO Auto-generated constructor stub

}

Terminal::Terminal(std::string pos, std::string word) :
		Symbol(pos) {
	this->word = word;
}

Terminal::Terminal(std::string pos, int start, int end, std::string word) :
		Symbol(pos, start, end) {
	this->word = word;
}

Terminal::Terminal(const Terminal& terminal) :
		Symbol(terminal) {
	this->word = terminal.word;
}

Terminal::~Terminal() {
	// TODO Auto-generated destructor stub
}

bool Terminal::isNonTerminal() const {
	return false;
}

bool Terminal::isTerminal() const {
	return true;
}

std::string Terminal::toString() const {
	std::stringstream ss;

	ss << "(" << this->symbol << " " << this->word << ")";

	return ss.str ();

}

NonTerminal* Terminal::nonTerminal() {
	return NULL;
}

Terminal* Terminal::terminal() {
	return this;
}

bool Terminal::isMatch(Symbol *symbol) {
	bool retVal = false;

	if (symbol->isTerminal()) {
		Terminal * tmp = symbol->terminal();

		retVal = (this->symbol.compare(tmp->symbol) == 0
				&& this->word.compare(tmp->word) == 0);
	}

	return retVal;
}

std::string Terminal::getSentence () {
	if (word == "-LRB-"){
 	    word = "(";
	} else if (word == "-RRB-"){
	    word = ")";
	} else if (word == "-LCB-"){
	    word = "{";
	} else if (word == "-RCB"){
	    word = "}";
	} else if (word == "COMMA"){
	    word = ",";
	}
	
	return word;
}

std::string Terminal::getWord() const {
	return word;
}

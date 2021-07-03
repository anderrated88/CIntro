/*
 * Terminal.h
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "Symbol.h"

/*
 *
 */
class Terminal: public Symbol {
protected:
	std::string word;
public:

	Terminal();
	Terminal(std::string pos, std::string word);
	Terminal(std::string pos, int start, int end, std::string word);
	Terminal(const Terminal& terminal);

	virtual ~Terminal();

	std::string getWord () const;

	bool isNonTerminal() const;
	bool isTerminal() const;

	std::string toString() const;

	NonTerminal* nonTerminal();
	Terminal* terminal();

	bool isMatch (Symbol *symbol);

	std::string getSentence ();
};

//class EmptyTerminal : public Terminal {
//
//};

#endif /* TERMINAL_H_ */

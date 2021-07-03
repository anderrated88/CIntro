/*
 * NonTerminal.h
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#ifndef NONTERMINAL_H_
#define NONTERMINAL_H_

#include <vector>

#include "Symbol.h"

/*
 *
 */
class NonTerminal: public Symbol {
protected:
	std::vector<Symbol *> children;
	std::vector<int> ordered; //order of children default is 0 1 2 ... <size_of_children>
public:
	NonTerminal();
	NonTerminal(std::string function, bool isHead, int start, int end);
	NonTerminal(std::string function, int start, int end);
	NonTerminal(std::string function, bool isHead);
	NonTerminal(std::string function);
	NonTerminal(const NonTerminal& nonTerminal);

	virtual ~NonTerminal();

	bool isNonTerminal() const;
	bool isTerminal() const;

	std::string toString() const;

	NonTerminal* nonTerminal();
	Terminal* terminal();

	void setOrdered (std::vector<int> ordered);
	void push_back(Symbol *child);

	int getOrderedAt (std::size_t orderedIndex);

	Symbol * getChildrenAt (int idx);
	void setElementAt (Symbol * symbol, int idx);
	int sizeOfChildren () const;

	bool isMatch (Symbol * symbol);
	bool isRuleMatch (Symbol * symbol);

	std::vector<int> getOrdered () const;

	std::string getSentence () ;
};

#endif /* NONTERMINAL_H_ */

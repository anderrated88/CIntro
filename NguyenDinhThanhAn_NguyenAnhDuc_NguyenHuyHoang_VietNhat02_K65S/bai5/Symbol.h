/*
 * Symbol.h
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */

#include <iostream>

#ifndef SYMBOL_H_
#define SYMBOL_H_

class NonTerminal;
class Terminal;
/*
 *
 */
class Symbol {
protected:
	std::string symbol;

	bool isHead;

	int start;
	int end;

	int height;
public:
	Symbol();

	Symbol (std::string symbol, bool isHead, int start, int end);
	Symbol (std::string symbol, int start, int end);
	Symbol (std::string symbol, bool isHead);
	Symbol (std::string symbol);

	std::string getSymbol () const;
	bool getIsHead () const;
	int getStart () const;
	int getEnd () const;
	int getHeight () const;

	void setHeight (int height);
	virtual ~Symbol();

	virtual bool isNonTerminal () const =0;
	virtual bool isTerminal () const =0;

	virtual std::string toString () const =0;

	virtual NonTerminal* nonTerminal () =0;
	virtual Terminal* terminal () =0;

	virtual bool isMatch (Symbol *symbol) =0;

	virtual std::string getSentence () =0;
};

#endif /* SYMBOL_H_ */

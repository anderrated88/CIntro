/*
 * Utils.h
 *
 *  Created on: Apr 19, 2012
 *      Author: thuvh
 */
#include <iostream>
#include <vector>

#include "Symbol.h"

#ifndef UTILS_H_
#define UTILS_H_

//const enum TYPE_OF_SYMBOL = { NON_TERMINAL = 1, NON_TERMINAL_IS_HEAD = 2, TERMINAL }
enum NUM_OF_ELE {
	ERROR = 0, NON_TERMINAL = 1, TERMINAL_OR_HEAD_NON_TERMINAL = 2
};
const std::size_t NUM_OF_ELE_IN_LINE = 3; //word tag chunk

std::vector<std::string> tokenize(std::string inpStr, std::string delim = " ");
/**
 * input $AB
 * input $AB[H]
 * input $AB["the"]
 */
Symbol * getSymbol(std::string inpStr, int start = 0, int end = 1);

std::vector<int> getIntVect(std::string inpStr);
std::vector<int> getIntVect(std::string inpStr, size_t expSize);
int s2i(std::string inpStr);

/**
 * load rule from file with structure like below text
 * $<sym> := $<sym>		symbol
 * x x x 				index of rhs in new order
 * @param filename
 * @return
 */
Symbol * loadRuleFromFile(std::string filename);

/**
 * automatic rule
 * load rule from file with format
 * one rule will contain in two line
 * first line is rule and second line is vector of index
 * @param filename
 * @return
 */
Symbol * loadRuleFromFile1(std::string filename);

/**
 * manual rule
 * load rule from with other structure like below text
 * line 1 contain number n is amount of rules in file
 * next is n section with first line rule, next line is number ni, which is amount of
 * reorder rule associate with this rule, and ni next lines are reorder rule
 * @param words
 * @param tags
 * @param chunks
 * @return
 */
Symbol * loadRuleFromFile2(std::string filename);

/**
 * load automatic rule from line
 * format of rule is
 * $VP:=$VP[H] $CC $X
 * $NP:=$NNP $NNP[H] $NAC $, $NAC $, $NAC $CC $NAC $: $CC $NP
 * @param line
 * @return
 */
Symbol * getRuleFromLine1(std::string line);
/**
 * load manual rule from line:
 * $VP -> $VBZ-H $PRT $PP $NP
 *
 * @param line
 * @return
 */
Symbol * getRuleFromLine2(std::string line);

std::vector<Symbol *> loadSentence(std::vector<std::string> words,
		std::vector<std::string> tags, std::vector<std::string> chunks);
std::vector<std::vector<Symbol *> > loadSentences(std::string filename);

std::vector<std::size_t> segment(std::vector<std::string> chunks);

void loadFile(std::string filename, Symbol * rules);
void loadFile(std::string filename, Symbol * rules, std::string output);

/**
 * compare between chunk in level 1 and rule
 * @param sentence - root of sentene
 * @param rule - rule need check
 * @return true or false
 */
bool isMatch(Symbol * chunk, Symbol * rule);

//bool isSymbolMatch (Symbol * chunk, Symbo * rule);
bool getReorderChunk(Symbol * chunk, Symbol * rule);
bool processSentence(Symbol * sentence, Symbol * rule, std::size_t &chunkIdx);

//build tree structure from sentence
//format of sentence (NP (NP hello) (VP (DT the) (VP world)))
Symbol * buildTree(std::string &sentence);

//flattern tree
Symbol * flatten(Symbol * sent);
void flattern1(Symbol * sente, Symbol * tree);

//get next token
std::string nextToken(std::string &sentence);

/**
 * do pre processing on tree structure with rule
 * @param chunk
 * @param rule
 */
bool doPreProcessing(Symbol* chunk, Symbol * rule);

void doPreProcessing(std::string ruleFileName, std::string inpFile, std::string outFile);

void surfTree(Symbol * sent);
#endif /* UTILS_H_ */

/*
 * Utils.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: thuvh
 */

#include <fstream>
#include <sstream>

#include <stack>

#include <cstdlib>

#include "Utils.h"

#include "Symbol.h"
#include "NonTerminal.h"
#include "Terminal.h"

std::vector<std::string> tokenize(std::string inpStr, std::string delim) {
	std::vector<std::string> retVal;
	std::size_t lenOfStr = inpStr.size();

	for (std::size_t bIdx = 0; bIdx < lenOfStr;) {
		std::size_t fIdx = inpStr.find_first_of(delim, bIdx);

		if (fIdx == std::string::npos) {
			fIdx = lenOfStr;
		}

		std::string cand = inpStr.substr(bIdx, fIdx - bIdx);
		if (!cand.empty()) {
			retVal.push_back(cand);
		}

		bIdx = fIdx + 1;
	}

	return retVal;
}
/**
 * input $AB
 * input $AB[H]
 * input $AB["the"]
 */
Symbol * getSymbol(std::string inpStr, int start, int end) {
	Symbol *retVal = NULL;
//	std::cout << inpStr << std::endl;
	std::vector<std::string> element = tokenize(inpStr, "$[]\"");
	std::size_t numOfElement = element.size();

	switch (numOfElement) {
	case NON_TERMINAL:
		retVal = new NonTerminal(element[0], start, end);
		break;
	case TERMINAL_OR_HEAD_NON_TERMINAL:
		if (element[1] == "H") {
			retVal = new NonTerminal(element[0], true, start, end);
		} else {
			retVal = new Terminal(element[0], start, end, element[1]);
		}

		break;

	case ERROR:
	default:
		for (size_t ci = 0; ci < numOfElement; ci++) {
			std::cerr << "ci = " << ci << ", tok = '" << element[ci] << "'"
					<< std::endl;
		}
		std::cerr << "loi: '" << inpStr << "', num of element = "
				<< numOfElement << std::endl;
		exit(1);
		break;
	}

	return retVal;
}

std::vector<int> getIntVect(std::string inpStr) {
	std::vector<int> retVal;

	std::vector<std::string> toks = tokenize(inpStr);
	std::size_t numOfToks = toks.size();

	for (std::size_t ci = 0; ci < numOfToks; ci++) {
		retVal.push_back(atoi(toks[ci].c_str()));
	}

	return retVal;
}

std::vector<int> getIntVect(std::string inpStr, size_t expSize) {
	std::vector<int> retVal;
	retVal.resize(expSize);

	std::size_t bIdx = 0;
	std::size_t lenOfStr = inpStr.size();
	std::size_t count = 0;

	while (bIdx < lenOfStr) {
		if (count >= expSize) {
			break;
		}

		std::size_t fIdx = inpStr.find_first_of(' ', bIdx);
		if (fIdx == std::string::npos) {
			fIdx = lenOfStr;
		}

		std::string tmp = inpStr.substr(bIdx, fIdx - bIdx);
		if (!tmp.empty()) {
			retVal[count++] = atoi(tmp.c_str());
		}

		bIdx = fIdx + 1;
	}

	return retVal;
}

Symbol * loadRuleFromFile(std::string filename) {
//	std::vector<Symbol *> retVal;
	Symbol * rules = new NonTerminal("Rules");

	std::ifstream fi(filename.c_str());

	if (!fi.good()) {
		std::cerr << "Error in open file: " << filename << std::endl;
	} else {
		bool flag = true;
		while (flag) {
			std::string firstLine;
			std::string secondLine;

			if (!fi.good()) {
				flag = false;
			}

			getline(fi, firstLine, '\n');
			getline(fi, secondLine, '\n');
			if (firstLine.empty() || secondLine.empty()) {
				continue;
			}

			if (firstLine[firstLine.length() - 1] == '\r') {
				firstLine = firstLine.substr(0, firstLine.length() - 1);
			}

			if (secondLine[secondLine.length() - 1] == '\r') {
				secondLine = secondLine.substr(0, secondLine.length() - 1);
			}

			std::vector<std::string> toks = tokenize(firstLine, " :=");
			std::string lhsTok = toks[0];
			Symbol * root = getSymbol(lhsTok, 0, toks.size() - 1);

			if (root == NULL) {
				std::cerr << "error in parse line: " << firstLine << ", "
						<< secondLine << std::endl;
				exit(1);
			}

			std::size_t numOfRhs = toks.size();
			for (std::size_t ci = 1; ci < numOfRhs; ci++) {
				std::string inpStr = toks[ci];
				Symbol *node = getSymbol(inpStr, ci - 1, ci);
				root->nonTerminal()->push_back(node);

			}

			std::vector<int> order = getIntVect(secondLine);
			root->nonTerminal()->setOrdered(order);

//			retVal.push_back(root);
			rules->nonTerminal()->push_back(root);
		}
	}
	return rules;
}

std::vector<Symbol *> loadSentence(std::vector<std::string> words,
		std::vector<std::string> tags, std::vector<std::string> chunks) {
	std::vector<Symbol *> retVal;

	if (words.size() == tags.size() && tags.size() == chunks.size()) {
		std::vector<std::size_t> segments = segment(chunks);
		std::size_t numOfSegments = segments.size();

		for (std::size_t ci = 0; ci < numOfSegments - 1; ci++) {
			std::size_t start = segments[ci];
			std::size_t end = segments[ci + 1];

			std::string function = chunks[start].substr(2);
			Symbol * root = new NonTerminal(function, start, end);
			for (size_t cj = start; cj < end; ci++) {
				Symbol * word = new Terminal(tags[cj], cj, cj + 1, words[cj]);
				root->nonTerminal()->push_back(word);
			}

			retVal.push_back(root);

		}
	} else {
		std::cerr << "size different check your input" << std::endl;
		exit(1);
	}

	return retVal;
}

std::vector<std::size_t> segment(std::vector<std::string> chunks) {
	std::vector<std::size_t> retVal;

	std::size_t lenOfSeg = chunks.size();

	for (size_t ci = 0; ci < lenOfSeg; ci++) {
		std::string tmp = chunks[ci];
		if (tmp[0] == 'B') {
			retVal.push_back(ci);
		} else if (tmp.length() == 1 && tmp == "O") {
			retVal.push_back(ci);
		}
	}
	retVal.push_back(lenOfSeg - 1); //end of string

	return retVal;
}

std::vector<std::vector<Symbol *> > loadSentences(std::string filename) {
	std::vector<std::vector<Symbol *> > sentences;

	std::ifstream fi(filename.c_str());

	std::vector<std::string> words;
	std::vector<std::string> tags;
	std::vector<std::string> chunks;

	std::string line;

	if (fi.good() == false) {
		std::cerr << "error in open file " << filename << std::endl;
		exit(1);
	}

	bool isContinue = true;
	while (isContinue) {

		getline(fi, line, '\n');

		isContinue = fi.good();
		std::cout << "line: " << line << ", " << isContinue << std::endl;
		if (line.empty() || line[0] == ' ') {
			std::vector<Symbol *> sentence = loadSentence(words, tags, chunks);
			sentences.push_back(sentence);
			words.clear();
			tags.clear();
			chunks.clear();
			std::cout << "he he" << std::endl;
		} else {
			std::vector<std::string> toks = tokenize(line, " \t");
			if (toks.size() != NUM_OF_ELE_IN_LINE) {
				std::cerr << " diff with element in '" << line << "'"
						<< std::endl;
				exit(1);
			}
			std::cout << toks[0] << " " << toks[1] << " " << toks[2]
					<< std::endl;
			words.push_back(toks[0]);
			tags.push_back(toks[1]);
			chunks.push_back(toks[2]);
		}
	}

	fi.close();
	return sentences;
}

void loadFile(std::string filename, Symbol * rules) {
	std::ifstream fi(filename.c_str());

	Symbol *sentence = new NonTerminal();
	std::string line;
	int wIdx = 0;
	std::string prev;
	std::string cur;

	while (fi.good()) {
		getline(fi, line, '\n');

		if (line.empty()) {
//			std::cout << sentence->toString() << std::endl;
			std::size_t numOfRule = rules->nonTerminal()->sizeOfChildren();
			for (std::size_t ruleIdx = 0; ruleIdx < numOfRule; ruleIdx++) {
				std::size_t chunkIdx;
				bool tmp = processSentence(sentence,
						rules->nonTerminal()->getChildrenAt(ruleIdx), chunkIdx);
				if (tmp) {
					break;
				}

			}

			std::cout << sentence->getSentence() << std::endl;

			sentence = new NonTerminal();
			wIdx = 0;
		} else {
			std::vector<std::string> toks = tokenize(line, " \t");

			Terminal * term = new Terminal(toks[1], wIdx, wIdx + 1, toks[0]);
//			std::cout<< term->toString() << std::endl;
			if (toks[2] != "O") {
				cur = toks[2].substr(2);
			} else {
				cur = toks[2];
			}

			Symbol * ele = NULL;

			if (toks[2] == "O") {
				ele = new NonTerminal(cur, wIdx, wIdx + 1);
				ele->nonTerminal()->push_back(term);
				sentence->nonTerminal()->push_back(ele);

			} else if (toks[2][0] == 'B') {
				Symbol * ele = new NonTerminal(cur, wIdx, wIdx + 1);
				ele->nonTerminal()->push_back(term);
				sentence->nonTerminal()->push_back(ele);
//				std::cout << sentence->toString() << std::endl;
//				std::cout << ele->toString() << std::endl;
			} else if (toks[2][0] == 'I') {

				ele = sentence->nonTerminal()->getChildrenAt(
						sentence->nonTerminal()->sizeOfChildren() - 1);
//
				ele->nonTerminal()->push_back(term);
//				sentence->nonTerminal()->setElementAt(term,
//						sentence->nonTerminal()->sizeOfChildren() - 1);
			} else {
				std::cerr << "error go here: '" << line << "'" << std::endl;
				exit(1);
			}
		}

		wIdx++;
	}

	fi.close();
}

void loadFile(std::string filename, Symbol * rules, std::string output) {
	std::ifstream fi(filename.c_str());
	std::ofstream fo(output.c_str());

	Symbol *sentence = new NonTerminal();
	std::string line;
	int wIdx = 0;
	std::string prev;
	std::string cur;

	int numOfMatching = 0;
	int numOfSentence = 0;

	while (fi.good()) {
		getline(fi, line, '\n');

		if (line.empty() || line[0] == '\r') {
			//	std::cerr << sentence->toString() << std::endl;
			std::size_t numOfRule = rules->nonTerminal()->sizeOfChildren();
			for (std::size_t ruleIdx = 0; ruleIdx < numOfRule; ruleIdx++) {
				std::size_t chunkIdx;
				bool tmp = processSentence(sentence,
						rules->nonTerminal()->getChildrenAt(ruleIdx), chunkIdx);
				if (tmp) {
//					std::cerr << "he he" << std::endl;
					std::cerr << "match " << ruleIdx << " ||| "
							<< rules->nonTerminal()->getChildrenAt(ruleIdx)->toString()
							<< " ||| "
							<< sentence->nonTerminal()->getChildrenAt(chunkIdx)
							<< std::endl;
					numOfMatching++;
					break;
				}

			}

			numOfSentence++;
			fo << sentence->getSentence() << std::endl;
//			std::cerr << sentence->getSentence() << std::endl;
			//reset
			sentence = new NonTerminal();
			wIdx = 0;
		} else {
			if (line[line.size() - 1] == '\r') {
				line = line.substr(0, line.size() - 1);
			}

			std::vector<std::string> toks = tokenize(line, " \t");

			Terminal * term = new Terminal(toks[1], wIdx, wIdx + 1, toks[0]);
//			std::cout<< term->toString() << std::endl;
			if (toks[2] != "O") {
				cur = toks[2].substr(2);
			} else {
				cur = toks[2];
			}

			Symbol * ele = NULL;

			if (toks[2] == "O") {
				ele = new NonTerminal(cur, wIdx, wIdx + 1);
				ele->nonTerminal()->push_back(term);
				sentence->nonTerminal()->push_back(ele);

			} else if (toks[2][0] == 'B') {
				Symbol * ele = new NonTerminal(cur, wIdx, wIdx + 1);
				ele->nonTerminal()->push_back(term);
				sentence->nonTerminal()->push_back(ele);
//				std::cout << sentence->toString() << std::endl;
//				std::cout << ele->toString() << std::endl;
			} else if (toks[2][0] == 'I') {

				ele = sentence->nonTerminal()->getChildrenAt(
						sentence->nonTerminal()->sizeOfChildren() - 1);
//
				ele->nonTerminal()->push_back(term);
//				sentence->nonTerminal()->setElementAt(term,
//						sentence->nonTerminal()->sizeOfChildren() - 1);
			} else {
				std::cerr << "error go here: '" << line << "'" << std::endl;
				exit(1);
			}
		}

		wIdx++;
	}

	std::cerr << "Num of matching: " << numOfMatching << "/" << numOfSentence
			<< std::endl;
	fi.close();
	fo.close();
}

/**
 * check match between one tree structure and one rule
 * @param chunk - chunk
 * @param rule - a rule
 * @return
 */

bool isMatch(Symbol * chunk, Symbol * rule) {
	bool retVal = false;

	//chunk is root node so that:
	//first is non terminal
	if (chunk->isNonTerminal()) {
		//check tag between them
//		std::cout << "chunk is satified" << std::endl;
		retVal = chunk->getSymbol() == rule->getSymbol();
		if (retVal) {
			//same size
			retVal = chunk->nonTerminal()->sizeOfChildren()
					== rule->nonTerminal()->sizeOfChildren();
//			std::cout << "chunk is satified" << std::endl;
			if (retVal) {
				std::size_t numOfChild = rule->nonTerminal()->sizeOfChildren();
//				std::cout << "chunk is satified" << std::endl;
				for (std::size_t ci = 0; ci < numOfChild; ci++) {
					//check each type
					Symbol * r = rule->nonTerminal()->getChildrenAt(ci);
//					std::cout << "chunk is satified" << std::endl;
					//neu note con cua rule la terminal
					//neu note con cua rule la nonterminal
					//otherwise error
					if (r->isTerminal()) {
						retVal = r->terminal()->isMatch(
								chunk->nonTerminal()->getChildrenAt(ci));

						if (!retVal) {
							break;
						}
					} else if (r->isNonTerminal()) {
						retVal =
								chunk->nonTerminal()->getChildrenAt(ci)->getSymbol()
										== r->getSymbol();
						if (!retVal) {
							break;
						}
					} else {
						std::cerr << "error in compare chunk: "
								<< chunk->toString() << ", rule: "
								<< rule->toString() << std::endl;
						exit(1);
					}
				}
			}
		}
	}

	return retVal;
}

bool processSentence(Symbol * sentence, Symbol * rule, std::size_t &chunkIdx) {
	bool retVal = false;
	chunkIdx = std::string::npos;
	std::size_t numOfChunk = sentence->nonTerminal()->sizeOfChildren();

	for (std::size_t ci = 0; ci < numOfChunk; ci++) {
		retVal = getReorderChunk(sentence->nonTerminal()->getChildrenAt(ci),
				rule);
		chunkIdx = ci;
		if (retVal) {
			break;
		}
	}

	return retVal;
}

bool getReorderChunk(Symbol * chunk, Symbol * rule) {
	bool retVal = false;

	if (chunk->isNonTerminal()) {
		retVal = isMatch(chunk, rule);
		if (retVal) {
//			std::vector<int> ordered = rule->nonTerminal()->getOrdered();
//			std::size_t sizeOfOrdered = ordered.size();
			chunk->nonTerminal()->setOrdered(rule->nonTerminal()->getOrdered());
		}
	}

	return retVal;
}

/**
 *
 * @param filename
 * @return
 */
Symbol * loadRuleFromFile1(std::string filename) {
	Symbol * root = new NonTerminal("__ROOT__");

	std::ifstream fi(filename.c_str());

	if (!fi.good()) {
		std::cerr << "Error in open file: " << filename << std::endl;
		exit(1);
	}

	std::string firstLine;
	std::string secondLine;
	bool isContinue = true;
	int count = 0;

	while (isContinue) {
		if (count % 1000 == 0) {
			std::cerr << count << "...." << std::endl;
			count = 0;
		}
		getline(fi, firstLine, '\n');
		getline(fi, secondLine, '\n');

		if (!fi.good()) {
			isContinue = false;
		}
	
		if (firstLine.empty () || firstLine[0] == '\r' || firstLine[0] == ' '){
			continue;
		}

		Symbol * rule = getRuleFromLine1(firstLine);
		std::vector<int> orderIdx = getIntVect(secondLine);
		rule->nonTerminal()->setOrdered(orderIdx);
		root->nonTerminal()->push_back(rule);
		count++;
	}

	fi.close();
	return root;
}

/**
 * manual rule
 * load rule from with with other structure like below text
 * line 1 contain number n is amount of rules in file
 * next is n section with first line rule,
 * next line is vector int of order
 *next line is number ni, which is amount of (not used)
 * reorder rule associate with this rule, and ni next lines are reorder rule (not used)
 * @param words
 * @param tags
 * @param chunks
 * @return
 */
Symbol * loadRuleFromFile2(std::string filename) {
	Symbol * root = new NonTerminal("__ROOT__");

	std::ifstream fi(filename.c_str());

	//read number of rule and clear stream
	int numOfRule = 0;
	fi >> numOfRule;

	std::string line;
	getline(fi, line, '\n');

//	std::cout << "n: " << numOfRule << std::endl;

	for (int i = 0; i < numOfRule; i++) {

		//read first line
		getline(fi, line, '\n');
		Symbol * rule = getRuleFromLine2(line);
		if (rule == NULL) {
			std::cerr << "error get rule from: '" << line << "'" << std::endl;
			exit(1);
		}

		getline(fi, line, '\n');
		std::vector<int> order = getIntVect(line);
		rule->nonTerminal()->setOrdered(order);

		root->nonTerminal()->push_back(rule);
	}

	fi.close();
	return root;
}

/** load automatic from line
 * $VP:=$VP[H] $CC $X
 * $NP:=$DT["any"] $NNP $NNP $CC $NN $NN[H]
 *
 * @param line
 * @return
 */
Symbol * getRuleFromLine1(std::string line) {
	std::size_t bIdx = 0;
	std::size_t lenOfLine = line.size();

	Symbol * rule = NULL;
	std::size_t fIdx = line.find_first_of("$", bIdx);
	bIdx = fIdx + 1;
	fIdx = line.find_first_of(" :", bIdx);
	if (fIdx == std::string::npos) {
		//error when reading
		std::cerr << "error in rule (first token):" << line << std::endl;
		exit(1);
	}

	rule = new NonTerminal(line.substr(bIdx, fIdx - bIdx));
	//bIdx = fIdx + 1;

	if (line[fIdx] == ' ') {
		bIdx = fIdx + 1;
		fIdx = line.find_first_of(":", bIdx);
		if (fIdx == std::string::npos) {
			//error when reading
			std::cerr << "error in rule (wait :): " << line << std::endl;
			exit(1);
		}

	}

	if (line[fIdx] == ':') {
		if (line[fIdx + 1] != '=') {
			std::cerr << "error in rule (wait =): " << line << std::endl;
			exit(1);
		}

		bIdx = fIdx + 2;
	}

	if (bIdx >= lenOfLine) {
		//error when reading
		std::cerr << "error in rule (no nonterminal): " << line << std::endl;
		exit(1);
	}

	while (bIdx < lenOfLine) {
		fIdx = line.find_first_of("$", bIdx);
		bIdx = fIdx + 1;
		fIdx = line.find_first_of(" ", bIdx);
		if (fIdx == std::string::npos) {
			//error when reading
			//std::cerr << "error in rule (error token): " << line << std::endl;
			//exit(1);
			fIdx = lenOfLine;
		}

		//rule = new NonTerminal(line.substr(bIdx, fIdx - bIdx));
		std::string token = line.substr(bIdx, fIdx - bIdx);
		bool isHead = false;

		//find [ and ]
		std::size_t bOIdx = token.find_first_of("[");
//		std::cerr << "token: " << token << ", idx[" << bOIdx << std::endl;
		if (bOIdx == std::string::npos) {
			Symbol * ruleEle = new NonTerminal(token);
			rule->nonTerminal()->push_back(ruleEle);
		} else {
			std::string function = token.substr(0, bOIdx);
			char nextChar = token[bOIdx + 1];
			if (nextChar == 'H') {
				isHead = true;
				Symbol * ruleEle = new NonTerminal(function, isHead);
				rule->nonTerminal()->push_back(ruleEle);
				bOIdx += 2;
			} else if (nextChar == '"') {
				std::size_t eOIdx = token.find_first_of("\"", bOIdx + 2);
				Symbol * ruleEle = new Terminal(function,
						token.substr(bOIdx + 2, eOIdx - bOIdx - 2));
//				std::cerr << "bOIdx: " << bOIdx << ", eOIdx: " << eOIdx << std::endl;
//				std::cerr << "token: " << token << ", str: " << token.substr(bOIdx + 2, eOIdx - bOIdx - 2) << std::endl;
				rule->nonTerminal()->push_back(ruleEle);
				bOIdx = eOIdx + 1;
			} else {
				std::cerr << "error in line (not \"): " << line << std::endl;
				exit(1);
			}

			if (token[bOIdx] != ']' && bOIdx != token.size() - 1) {
				std::cerr << "bOIdx = " << bOIdx << ", size: " << token.size()
						<< std::endl;
				std::cerr << "error in line (token not end by ]): " << line
						<< std::endl;
				exit(1);
			}
		}

		bIdx = fIdx + 1;
	}

	return rule;
}

/**
 * load manual rule from line:
 * $VP -> $VBZ-H $PRT $PP $NP
 *
 * @param line
 * @return
 */
Symbol * getRuleFromLine2(std::string line) {

	std::size_t lenOfLine = line.size();
	std::size_t bIdx = 0;
	std::size_t count = 0;

	Symbol * lhs = NULL;

	while (bIdx < lenOfLine) {
		std::size_t fIdx = line.find_first_of(' ', bIdx);
		if (fIdx == std::string::npos) {
			fIdx = lenOfLine;
		}

		std::string token = line.substr(bIdx, fIdx - bIdx);
		if (!token.empty()) {
			if (token[0] != '$' && count != 1) {
				std::cerr << "error in token format (start with $): '" << token
						<< "', line: '" << line << "'" << std::endl;
				exit(1);
			}

			if (count == 0) {
				if (token == "$NP_B") {
					token = "NP";
				} else {
					token = token.substr(1);
				}

				lhs = new NonTerminal(token);
			} else if (count == 1) {
				if (token != "->") {
					std::cerr << "error in format of line: '" << line << "'"
							<< std::endl;
					exit(1);
				}
			} else {

				// TODO: check NP_B ?
				bool isHead = token.substr(token.size() - 2) == "-H";
				if (isHead) {
					token = token.substr(1, token.size() - 3);
				} else {
					token = token.substr(1);
				}

				if (token == "NP_B") {
					token = "NP";
				}

				Symbol *rhs = new NonTerminal(token, isHead);
				lhs->nonTerminal()->push_back(rhs);
			}

			count++;
		}

		bIdx = fIdx + 1;
	}

	return lhs;
}

Symbol * buildTree(std::string &sentence) {
	Symbol * tree = NULL;

	std::string oBrk = nextToken(sentence);
	int h = 0;

	if (oBrk == "(") {
		std::string fTok = nextToken(sentence);

		std::vector<std::string> fToks = tokenize(fTok, "-");
		fTok = fToks[0];

		std::string sTok = nextToken(sentence);
		if (sTok == "(") {
			tree = new NonTerminal(fTok);
			sentence = "(" + sentence;

//			std::cerr << "'" << sentence << "'" << std::endl;

			int i = 0;

			while (true) {
//				std::cerr << "i = " << i << ", sent: " << sentence << std::endl;
				if (i >= 10) {
					break;
				}
				i++;

				Symbol * treeEle = buildTree(sentence);
				if (treeEle == NULL) {
					std::string cBrk = nextToken(sentence);
					if (cBrk == ")") {
						break;
					} else {
						std::cerr << "error in read last token: " << cBrk
								<< ", " << sentence << std::endl;
						exit(1);
					}
				} else {
					tree->nonTerminal()->push_back(treeEle);
					if (treeEle->getHeight() > h) {
						h = treeEle->getHeight();
					}
				}

				//check break
				std::string tmp = nextToken(sentence);
				if (tmp == ")") {
					tree->setHeight(h + 1);
					break;
				} else {
					sentence = tmp + " " + sentence;
				}
			}
		} else if (sTok == ")") {
			//error
			std::cerr << "error in second token: '" << sentence << "'"
					<< std::endl;
			exit(1);
		} else {
			tree = new Terminal(fTok, sTok);
			tree->setHeight(0);
			std::string tok = nextToken(sentence);
			if (tok != ")") {
				std::cerr << "error in end sentence: " << tok << ", "
						<< sentence << std::endl;
				exit(1);
			}
		}

	} else {
		std::cerr << "error in read first token: '" << oBrk << ", " << sentence
				<< std::endl;
		exit(1);
	}

	return tree;
}

std::string nextToken(std::string &sentence) {
	std::stringstream ss;

	std::size_t idx = 0;
	std::size_t lenOfSent = sentence.length();
	int found = 0;

	if (lenOfSent > 0) {
		//remove space at end of line

		while (idx < lenOfSent && sentence[idx] == ' ') {
			idx++;
		}
		//update sentence
		sentence = sentence.substr(idx);
		lenOfSent = sentence.length();
		idx = 0;

		while (idx < lenOfSent) {
			char ch = sentence[idx];

			if (ch == '(' || ch == ')') {
				found = 1;
				//neu rong
				//thi ky tu hien tai la (
				//cat den idx - 1
				if (ss.str().empty()) {
					ss << ch;
					idx++;
				}
//				else {
//					//ko rong thi la den ky tu -1 thoi
//					idx--;
//				}

				break;
			} else if (ch == ' ') {
				found = 2;
				break;
			} else {
				ss << ch;
			}

			idx++;
		}
	}

	if (found) {
		//if found update input
		sentence = sentence.substr(idx);

		//update
		idx = 0;
		lenOfSent = sentence.length();
		while (idx < lenOfSent && sentence[idx] == ' ') {
			idx++;
		}

		if (idx != 0) {
			sentence = sentence.substr(idx);
		}
	}

	return ss.str();
}

/**
 * flattern tree, k = 2, keep high node is 2 or lower
 * @param sent
 * @return
 */
Symbol * flatten(Symbol * tree) {
	Symbol * root = new NonTerminal("__ROOT__");
	flattern1(tree, root);
	return root;
}

void surfTree(Symbol * sent) {
////	std::queue<Symbol *> nodes;
//	nodes.push(sent);
//
//	while (!nodes.empty()) {
//		Symbol * top = nodes.front();
//		nodes.pop();
//
//		std::cout << "(";
//		if (top->isTerminal()) {
//			std::cout << top->getSymbol() + " " + top->terminal()->getWord();
//		} else if (top->isNonTerminal()) {
//			NonTerminal * tmp = top->nonTerminal();
//			int sizeOfChild = tmp->sizeOfChildren();
//
//			for (int i = 0; i < sizeOfChild; i++) {
//				nodes.push(tmp->getChildrenAt(i));
//			}
//		}
//		std::cout << ")";
//	}
}

void flattern1(Symbol * sent, Symbol * tree) {

	if (sent->isTerminal()) {
		tree->nonTerminal()->push_back(sent);
	} else if (sent->isNonTerminal()) {
		if (sent->getHeight() <= 2) {
			tree->nonTerminal()->push_back(sent);
		} else {
			int sizeOfChild = sent->nonTerminal()->sizeOfChildren();
			for (int i = 0; i < sizeOfChild; i++) {
				Symbol * sentEle = sent->nonTerminal()->getChildrenAt(i);
				flattern1(sentEle, tree);
			}
		}
	} else {
		std::cerr << tree->toString() << " is not terminal or non-terminal."
				<< std::endl;
		exit(1);
	}
}

/**
 * do pre processing on tree structure with rule
 * @param chunk
 * @param rule
 */
bool doPreProcessing(Symbol* chunk, Symbol * rules) {
	int count = 0;
	if (chunk->isNonTerminal()) {

		int _sizeOfRules = rules->nonTerminal()->sizeOfChildren();
		for (int i = 0; i < _sizeOfRules; i++) {
			if (chunk->nonTerminal()->isRuleMatch(
					rules->nonTerminal()->getChildrenAt(i))) {
				chunk->nonTerminal()->setOrdered(
						rules->nonTerminal()->getChildrenAt(i)->nonTerminal()->getOrdered());
				count++;
				std::cerr << "match level 2: " << chunk->toString () << std::endl;
				break;
			}
		}

		int sizeOfChild = chunk->nonTerminal()->sizeOfChildren();
		for (int i = 0; i < sizeOfChild; i++) {
			bool b = doPreProcessing(chunk->nonTerminal()->getChildrenAt(i),
					rules);
//			Symbol * tmp = chunk->nonTerminal()->getChildrenAt(i);
//			doProProcessing(tmp, rule);
			count += b;
		}
	}
	return (count != 0);
}

void doPreProcessing(std::string ruleFileName, std::string inpFile,
		std::string outFile) {
	Symbol * rules = loadRuleFromFile1(ruleFileName);

	std::ifstream fi(inpFile.c_str());

	if (!fi.good()) {
		std::cerr << "can not open file: " << inpFile << std::endl;
		exit(1);
	}

	std::ofstream fo(outFile.c_str());
	if (!fo.good()) {
		std::cerr << "can not open file: " << outFile << std::endl;
		exit(1);
	}

	int lineNumber = 0;
	int matchCount = 0;

	while (true) {
		std::string line;
		getline(fi, line, '\n');
		//lineNumber++;
		if (lineNumber % 1000 == 0) {
			std::cerr << lineNumber << "...." << std::endl;
		}

		if (!fi.good()) {
			break;
		}
		if (line.empty() || line[0] == ' ') {
			continue;
		}
		lineNumber++;

		Symbol * fTree = buildTree(line);
		if (fTree == NULL) {
			std::cerr << "error in build tree: " << line << std::endl;
		} else {

			Symbol * cTree = flatten(fTree);
			int _treeSize = cTree->nonTerminal()->sizeOfChildren();
			bool f = false;
			for (int _treeIdx = 0; _treeIdx < _treeSize; _treeIdx++) {
				f  = doPreProcessing(
						cTree->nonTerminal()->getChildrenAt(_treeIdx), rules);
				//if (b){
				//	matchCount++;
				//}
			}

			if (f){
			    matchCount++;
			}
			fo << cTree->getSentence() << std::endl;
//			fo << std::endl;
		}
	}

	std::cerr << "match: " << matchCount << "/" << lineNumber << std::endl;
	fi.close();
	fo.close();
}

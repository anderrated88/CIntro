/*
 * main.cpp
 *
 *  Created on: Jun 5, 2012
 *      Author: thuvh
 */

#include <iostream>
#include <cstdlib>
#include "NonTerminal.h"
#include "Utils.h"

using namespace std;

int process(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr
			<< "program <rules input file> <sentence input file> <output file> "
			<< std::endl;
		return 1;
	}

	string ruleInputFileName = argv[1];
	string sentenceInputFileName = argv[2];
	string sentenceOutputFileName = argv[3];

	doPreProcessing(ruleInputFileName, sentenceInputFileName,
					sentenceOutputFileName);
	std::cerr << "Done!!!" << std::endl;
	return 0;
}

int main(int argc, char *argv[])
{
	//	doPreProcessing("rules.txt", "sents.inp", "sents.out");
	process(argc, argv);
	return 0;
}

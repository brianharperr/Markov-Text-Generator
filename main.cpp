#include "markov.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		std::cout << "usage: markov [filepath] [wordcount]" << std::endl;
	}

	MarkovChainTextGenerator generator;
	generator.ExtractWords(argv[1]);
	generator.CalculateSuffixProbability();
	generator.GenerateSentence(atoi(argv[2]));

	return 0;
}
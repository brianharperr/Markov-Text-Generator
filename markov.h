#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::map<std::string, float>> ProbabilityList;

class MarkovChainTextGenerator
{
	public:
		MarkovChainTextGenerator(){};
		std::vector<std::string> wordLog;
		std::vector<std::string> fullTextLog;
		std::map<std::string, float> probabilityMap;
		ProbabilityList completeList;
		void ExtractWords(std::string filepath);
		void CalculateSuffixProbability();
		void RemoveDuplicates(std::vector<std::string> *T);
		void GenerateSentence(int word_count);
};
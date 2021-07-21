#include <fstream>
#include <algorithm>
#include <time.h>

#include "markov.h"

using namespace std;

void MarkovChainTextGenerator::RemoveDuplicates(std::vector<std::string> *T)
{
	sort(T->begin(), T->end());
	T->erase(unique(T->begin(), T->end()), T->end());
}

void MarkovChainTextGenerator::ExtractWords(std::string filepath)
{
	ifstream file;
	file.open(filepath);
	if(!file.is_open()) return;

	string word;
	while(file >> word)
	{
		wordLog.push_back(word);
		fullTextLog.push_back(word);
	}

	RemoveDuplicates(&wordLog);
}

void MarkovChainTextGenerator::CalculateSuffixProbability()
{
	//Get suffix list
	std::vector<std::string> suffixLog;
	for(int i = 0; i < (int)wordLog.size(); i++)
	{
		cout << "\rLoading: "<< (int)(((float)(i+1)/(float)wordLog.size())*100) << "%" << flush;
		for(int j = 0; j < (int)fullTextLog.size() - 1; j++)
		{
			if(wordLog[i] == fullTextLog[j])
			{
				suffixLog.push_back(fullTextLog[j+1]);
			}
		}
		if(suffixLog.empty()) continue;

		//Sort suffix list
		sort(suffixLog.begin(), suffixLog.end());

		//Calculate probabilites
		string idx = suffixLog.at(0);
		int n = suffixLog.size();
		int count = 1;
		for(int j = 1; j < n + 1; j++)
		{
			if(j == n)
			{
				probabilityMap.insert(std::pair<string,float>(idx, (float)count/(float)n));
				break;
			}
			if(idx == suffixLog.at(j)){
				count++;
			}else{
				probabilityMap.insert(std::pair<string,float>(idx, (float)count/(float)n));
				idx = suffixLog.at(j);
				count = 1;
			}
		}
		completeList.insert(std::pair<std::string, std::map<std::string, float>>(wordLog[i], probabilityMap));
		probabilityMap.clear();
		suffixLog.clear();
	}

	fullTextLog.clear();
	
}

void MarkovChainTextGenerator::GenerateSentence(int word_count)
{
	srand((unsigned)time(NULL));
    float roll = (float)rand()/RAND_MAX;
    
    int firstWord = (rand() % wordLog.size());
    float meet_value = 0.0;
    std::map<std::string, float> internal_map;
    std::string word = wordLog[firstWord];
    std::cout << "\n" << word << " ";

    for(int i = 0; i < word_count-1; i++){

        roll = (float)rand()/RAND_MAX;

    	if(completeList.at(word).empty())
	    {
	    	word = "a";
	    }
		internal_map = completeList.at(word);

	    for (std::map<std::string, float>::iterator it = internal_map.begin(); it != internal_map.end(); ++it){
	        if(meet_value < roll)
	        {
	        	meet_value += it->second;
	        }else{
	        	word = it->first;
	        	cout << word << " ";
	       		meet_value = 0.0;
	       		break;
	        }
	    }
	}

	cout << "\n";

}

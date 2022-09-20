// GraphistoftTeaser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "WordleSolver.h"


int main()
{
    // Read all options file
    std::vector<std::string> allOptions;
    std::string line;
    std::ifstream optionsFile("options.txt");
    while (std::getline(optionsFile, line))
    {
        allOptions.push_back(line);
    }

    // Read results and tries
    std::vector<WordleSolver> wordleSolvers;
	std::ifstream triesFile("trys.txt");
    int i = 0;
    WordleSolver wordleSolver;
	while (std::getline(triesFile, line))
	{
        if (line == "")
        {
			wordleSolver.setOptions(allOptions);
			wordleSolvers.push_back(wordleSolver);
			wordleSolver = WordleSolver();
            continue;
        }
        if (i % 2 == 0)
        {
            wordleSolver.addTip(line);
        }else
        {
            wordleSolver.addResult(line);
        }
        ++i;
	}

    // last line
	wordleSolver.setOptions(allOptions);
	wordleSolvers.push_back(wordleSolver);

    int num = 0;
    for (auto& wordleSolver : wordleSolvers)
    {
        ++num;
        std::cout << std::to_string(num) << ". Feladat" << std::endl;
		wordleSolver.process();
		wordleSolver.printPossibleSolutions();
    }
}
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

	wordleSolver.setOptions(allOptions);
	wordleSolvers.push_back(wordleSolver);
	//wordleSolver = WordleSolver();

    int num = 0;
    for (auto& wordleSolver : wordleSolvers)
    {
        ++num;
        std::cout << std::to_string(num) << ". Feladat" << std::endl;
		wordleSolver.process();
		wordleSolver.printPossibleSolutions();
    }

    //std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

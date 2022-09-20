#pragma once

#include <string>
#include <vector>

class WordleSolver
{
public:
	WordleSolver() {}

	void printPossibleSolutions() const;
	void process();

	void addTip(const std::string& tip);
	void addResult(const std::string& result);
	void setOptions(const std::vector<std::string>& allOptions);

private:
	static bool checkForRepatingChar(const std::string& word, char c);

	void processPair(const std::string& result, const std::string& tip);

	void removeOptionsCharNotInPosition(char c, int position);
	void removeOptionsCharInWord(char c);
	void removeOptionsCharNotInWord(char c, int position);
	void removeOptionsWithRepeatingChar(char c);
	void removeOptionsWithoutRepatingChar(char c);

private:
	std::vector<std::string> m_AllOption;
	std::vector<std::string> m_Tips;
	std::vector<std::string> m_Results;
};


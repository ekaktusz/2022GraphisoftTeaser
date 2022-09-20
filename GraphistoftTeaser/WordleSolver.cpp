#include "WordleSolver.h"

#include <iostream>

// Static
bool WordleSolver::checkForRepatingChar(const std::string& word, char c)
{
	int num = std::count(word.begin(), word.end(), c);
	return num > 1;
}

void WordleSolver::process()
{
	for (int i = 0; i < m_Tips.size(); ++i)
	{
		processPair(m_Results[i], m_Tips[i]);
	}
}

void WordleSolver::processPair(const std::string& result, const std::string& tip)
{
	for (int char_pos = 0; char_pos < 5; ++char_pos)
	{
		//std::cout << std::to_string(char_pos) << ". iter: ";
		//printPossibleSolutions();

		char tip_char = tip[char_pos];
		char result_char = result[char_pos];

		std::string temp_tip = tip;
		temp_tip[char_pos] = 0; // replace all tip_char to 0
		int other_occurence_position = temp_tip.find(tip_char);
		char other_result_char = '0';

		int num = std::count(tip.begin(), tip.end(), tip_char);

		if (other_occurence_position != std::string::npos)
		{
			other_result_char = result[other_occurence_position];
		}

		if (result_char == 'o')
		{
		//	if (other_result_char == 'o') removeOptionsWithoutRepatingChar(tip_char);
		//	if (other_result_char == 'x') removeOptionsWithoutRepatingChar(tip_char);
			// remove every instance where char is not in the position
			removeOptionsCharNotInPosition(tip_char, char_pos);
		}
		else if (result_char == 'x')
		{
			if (other_result_char == 'o') removeOptionsWithoutRepatingChar(tip_char);
			if (other_result_char == 'x') removeOptionsWithoutRepatingChar(tip_char);
			// remove every word, where char is not in the word
			removeOptionsCharNotInWord(tip_char, char_pos);
		}
		else if (result_char == '-')
		{
			if (other_result_char == 'o')
			{
				if (num == 2) {
					removeOptionsWithRepeatingChar(tip_char);
				}
				continue;
			}
			if (other_result_char == 'x')
			{
				if (num == 2) {
					removeOptionsWithRepeatingChar(tip_char);
				}
				continue;
			}
			// remove every word where char is in the word (és az elõzõek között nincs x vagy o ugyanilyen karakterre)
			removeOptionsCharInWord(tip_char);
		}
	}
}

// Remove options, where char is not on position
void WordleSolver::removeOptionsCharNotInPosition(char c, int position)
{
	m_AllOption.erase(std::remove_if(
		m_AllOption.begin(), m_AllOption.end(),
		[&](std::string& x) {
			return c != x[position];
		}), m_AllOption.end());
}

// Remove options, where char is in word
void WordleSolver::removeOptionsCharInWord(char c)
{
	m_AllOption.erase(std::remove_if(
		m_AllOption.begin(), m_AllOption.end(),
		[&](std::string& x) {
			return x.find(c) != std::string::npos;
		}), m_AllOption.end());
}

// Remove options, where char is not in word or it is, but not on the given position
void WordleSolver::removeOptionsCharNotInWord(char c, int position)
{
	m_AllOption.erase(std::remove_if(
		m_AllOption.begin(), m_AllOption.end(),
		[&](std::string& x) {
			return x.find(c) == std::string::npos || (x.find(c) != std::string::npos && x[position] == c); 
		}), m_AllOption.end());
}

// Remove options where there is a repating char
void WordleSolver::removeOptionsWithRepeatingChar(char c)
{
	m_AllOption.erase(std::remove_if(
		m_AllOption.begin(), m_AllOption.end(),
		[&](std::string& x) {
			return checkForRepatingChar(x, c);
		}), m_AllOption.end());
}

// Remove options where there is no repating char
void WordleSolver::removeOptionsWithoutRepatingChar(char c)
{
	m_AllOption.erase(std::remove_if(
		m_AllOption.begin(), m_AllOption.end(),
		[&](std::string& x) {
			return !checkForRepatingChar(x, c); // a char nincs benne VAGY benne van, de ezen a pizíción
		}), m_AllOption.end());
}

void WordleSolver::printPossibleSolutions() const
{
	std::cout << "Possible solutions: ";
	for (const auto& option : m_AllOption)
	{
		std::cout << option << ", ";
	}
	std::cout << "\n";
}

void WordleSolver::addTip(const std::string& tip)
{
	m_Tips.push_back(tip);
}

void WordleSolver::addResult(const std::string& result)
{
	m_Results.push_back(result);
}

void WordleSolver::setOptions(const std::vector<std::string>& allOptions)
{
	m_AllOption = allOptions;
}
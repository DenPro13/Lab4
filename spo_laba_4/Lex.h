#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

struct token_pair
{
	std::string name;
	std::string value;
};

class Lex
{
public:
	std::vector<token_pair> getTokens(std::string fname);
	struct tokens
	{
		std::string name;
		std::string rx;
		int priority;
	};
	std::vector<Lex::tokens> getRegexFromFile();
	std::vector<Lex::tokens> findMatch(std::string str, std::vector<Lex::tokens> & myRegex);
private:
	void eraseWhitespaces(std::string & str);
	std::string readCodeFromFile(std::string fname);
};
#pragma once
#include "Pars.h"


class Interpretator
{


public:
	std::vector<std::string> get_reverse_polish_notation(std::vector<token_pair> code);

private:
	std::vector<std::string> getSimpleRPN(std::vector<token_pair> code);
	

};
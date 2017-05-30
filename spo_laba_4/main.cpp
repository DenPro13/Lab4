#include "Lex.h"
#include "Pars.h"
#include "Interpretator.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "ѕрактическое задание є4\n\n";
	std::cout << "¬ведите им€ *.txt файла \n(файл должен располагатьс€ в одной папке с программой)\n";
	std::string fname;
	std::cin >> fname;

	Lex Lex;
	std::vector<token_pair> tokens = Lex.getTokens(fname);

	if (!tokens.empty())
	{
		std::cout << "\nЋексер не вы€вил ошибок.";

		Pars Pars;
		bool correct = Pars.checkSyntax(tokens);
		if (correct)
		{
			std::cout << "\nѕарсер не вы€вил ошибок.\n";
		}
		else
		{
			std::cout << "\nѕарсер вы€вил ошибку.\n";
		}
	}
	else
	{
		std::cout << "\nЋексер вы€вил ошибку.\n";
	}

	Interpretator Interpretator;
	std::vector<std::string> rpn = Interpretator.get_reverse_polish_notation(tokens);
	//Interpretator.get_reverse_polish_notation(tokens);

	std::cout << "\n";
	for (int i = 0; i < rpn.size(); ++i)
	{
		std::cout << std::left << std::setw(3) << i + 1 << rpn[i] << "\n";
	}

	std::cout << "\n";
	system("pause");
	return 0;
}





/*std::cout << "\n\n–езультат работы лексера:\n\n";
for (int i = 0; i < tokens.size(); ++i)
{
std::cout << std::left << std::setw(18) << tokens[i].name << " " << tokens[i].value << "\n";
}*/
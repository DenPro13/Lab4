#include "Interpretator.h"

std::vector<std::string> Interpretator::get_reverse_polish_notation(std::vector<token_pair> code)
{
	std::vector<std::string> rpn;

	std::vector<token_pair> buffer;
	std::vector<token_pair> buffer2;
	std::vector<token_pair> buffer3;
	std::vector<int> labels;
	code.push_back({ "end", "end" });

	for (int i = 0; i < code.size(); ++i)
	{
		if (i == 57)
		{
			int s = 13;
		}

		if (code[i].name == "KW_IF" || code[i].name == "KW_FOR")
		{
			buffer3.push_back(code[i]);
		}
		else
		{
			if (code[i].name == "LBRACE")
			{
				buffer2.push_back(code[i]);
			}
			else
			{
				if (code[i].name == "DIGIT" || code[i].name == "VAR" || code[i].name == "UNA_ARITHM_OPER")
				{
					rpn.push_back(code[i].value);
				}
				else
				{
					if (buffer.empty() && code[i].value != "=" && code[i].value != "}" && code[i].value != ";" && code[i].value != "end")
					{
						buffer.push_back(code[i]);
					}
					else
					{
						/*========================================================================*/
						if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
						{
							while (!buffer.empty())
							{
								if (buffer.back().name == "BIN_ARITHM_OPER")
								{
									rpn.push_back(buffer.back().value);
									buffer.pop_back();
								}
								else break;
							}
							buffer.push_back(code[i]);
						}
						/*========================================================================*/

						if (code[i].value == "*" || code[i].value == "/")
						{
							if (buffer.back().value == "*" || buffer.back().value == "/")
							{
								rpn.push_back(buffer.back().value);
								buffer.pop_back();
							}
							else
							{
								buffer.push_back(code[i]);
							}
						}
						/*========================================================================*/

						if (code[i].value == ")")
						{
							while (buffer.back().value != "(")
							{
								rpn.push_back(buffer.back().value);
								buffer.pop_back();
							}
							if (buffer.back().value == "(")
							{
								buffer.pop_back();
							}
							/*if (!buffer2.empty() && buffer3.back().value == "if")
							{*/
							if (buffer3.back().value == "if" && buffer3.size() > labels.size())
							{
								labels.push_back(rpn.size());
								rpn.push_back("void_label");
								rpn.push_back("!F");
							}
							if (!buffer2.empty() && buffer2.back().value != "{")
							{
								buffer2.pop_back();
							}
						}
						/*========================================================================*/

						if (code[i].value == "(")
						{
							buffer.push_back(code[i]);
						}
						/*========================================================================*/

						if (code[i].value == "}")
						{
							if (!buffer2.empty())
							{
								if (buffer2.back().value == "{" && buffer3.back().name == "KW_IF")
								{
									rpn[labels.back()] = "@" + std::to_string(rpn.size() + 1);
									labels.pop_back();
									buffer2.pop_back();
									buffer3.pop_back();
								}
								else
								{
									if (buffer2.back().value == "{" && buffer3.back().name == "KW_FOR")
									{
										rpn.push_back("@" + std::to_string(labels.back() + 1));
										rpn.push_back("!");
										labels.pop_back();
										buffer2.pop_back();
										buffer3.pop_back();

										rpn[labels.back()] = "@" + std::to_string(rpn.size() + 1);
										labels.pop_back();
										buffer2.pop_back();
										buffer3.pop_back();
									}
								}
							}
						}
						/*========================================================================*/

						if (code[i].value == "=")
						{
							buffer2.push_back(code[i]);
						}
						/*========================================================================*/

						if (code[i].value == ";")
						{
							while (!buffer.empty() && buffer.back().value != "(")
							{
								rpn.push_back(buffer.back().value);
								buffer.pop_back();
							}

							while (!buffer2.empty() && buffer2.back().value != "{")
							{
								rpn.push_back(buffer2.back().value);
								buffer2.pop_back();
							}

							if (!buffer3.empty())
							{
								if (buffer3.back().name == "KW_FOR")
								{
									if (buffer3.size() > labels.size())
									{
										labels.push_back(rpn.size());
									}
									else
									{
										if (buffer3.size() == labels.size())
										{
											if (buffer3.back().value == "for")
											{
												buffer3.push_back({ "KW_IF", "if" });
												labels.push_back(rpn.size());
												rpn.push_back("void_label");
												rpn.push_back("!F");
											}
										}
									}
								}
							}
						}
						/*========================================================================*/

						if (code[i].value == "end")
						{
							while (!buffer.empty())
							{
								rpn.push_back(buffer.back().value);
								buffer.pop_back();
							}
							while (!buffer3.empty())
							{
								if (buffer3.back().name == "KW_IF")
								{
									rpn[labels.back()] = "@" + std::to_string(rpn.size() + 1);
									labels.pop_back();
									buffer3.pop_back();
								}
							}
						}
					}
				}
			}
		}
	}

	return rpn;
}

std::vector<std::string> Interpretator::getSimpleRPN(std::vector<token_pair> code)
{
	std::vector<std::string> rpn;
	std::vector<token_pair> buffer;
	code.push_back({ "end", "end" });

	for (int i = 0; i < code.size(); ++i)
	{
		if (code[i].name == "DIGIT" || code[i].name == "VAR")
		{
			rpn.push_back(code[i].value);
		}
		else
		{
			if (buffer.empty())
			{
				buffer.push_back(code[i]);
			}
			else
			{
				/*========================================================================*/
				if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
				{
					while (!buffer.empty())
					{
						if (buffer.back().name == "BIN_ARITHM_OPER")
						{
							rpn.push_back(buffer.back().value);
							buffer.pop_back();
						}
						else break;
					}
					buffer.push_back(code[i]);
				}
				/*========================================================================*/

				if (code[i].value == "*" || code[i].value == "/")
				{
					if (buffer.back().value == "*" || buffer.back().value == "/")
					{
						rpn.push_back(buffer.back().value);
						buffer.pop_back();
					}
					else
					{
						buffer.push_back(code[i]);
					}
				}
				/*========================================================================*/

				if (code[i].value == ")")
				{
					while (buffer.back().value != "(")
					{
						rpn.push_back(buffer.back().value);
						buffer.pop_back();
					}
					if (buffer.back().value == "(")
					{
						buffer.pop_back();
					}
				}
				/*========================================================================*/

				if (code[i].value == "(")
				{
					buffer.push_back(code[i]);
				}
				/*========================================================================*/

				if (code[i].value == "end")
				{
					while (!buffer.empty())
					{
						rpn.push_back(buffer.back().value);
						buffer.pop_back();
					}
				}
			}
		}
	}

	return rpn;
}


/*
Parser parser;
std::vector<token> syntax = parser.getSyntaxRegEx();

std::string if_expr;
std::string if_expr_head;
std::string if_condition;
std::string if_expr_body;
for (int i = 0; i < syntax.size(); ++i)
{
if (syntax[i].name == "if_expr")      { if_expr = syntax[i].rx;      }
if (syntax[i].name == "if_expr_head") { if_expr_head = syntax[i].rx; }
if (syntax[i].name == "if_condition") { if_condition = syntax[i].rx; }
if (syntax[i].name == "if_expr_body") { if_expr_body = syntax[i].rx; }
}

while (!code.empty())
{
if (code[0].name == "KW_IF")
{
// Запишем все токены всего кода в строку через пробел
std::string tokensInStr;
for (int i = 0; i < code.size(); ++i)
{
tokensInStr = tokensInStr + code[i].name + " ";
}
tokensInStr.erase(tokensInStr.size() - 1, 1);

// Среди них найдем токены составляющие if_expr и вырежем их в отделюную строку
std::string ifStr;
std::tr1::regex rxN(if_expr);
std::tr1::match_results<const char *> expr;
std::tr1::regex_search(tokensInStr.c_str(), expr, rxN);
ifStr = expr.str();
tokensInStr.erase(0, ifStr.size() + 1);

ifStr = ifStr + " ";
// Посчитаем количество токенов в строке if_expr
int count = 0;
while (!ifStr.empty())
{
std::tr1::regex tok("^[_A-Z]*");
std::tr1::match_results<const char *> res;
std::tr1::regex_search(ifStr.c_str(), res, tok);
ifStr.erase(0, res.str().size() + 1);
count++;
}

// Найдем условие
for (int i = 0; i < count; ++i)
{
/*if ()
{

}*/
			/*}

		}

		if (code[0].name == "KW_FOR")
		{

		}

	}*/

/*
for (int i = 0; i < code.size(); ++i)
{
if (i == 15)
{
int s = 13;
}

if (code[i].name == "KW_IF" || code[i].name == "LBRACE")
{
buffer2.push_back(code[i]);
}
else
{
if (code[i].name == "DIGIT" || code[i].name == "VAR" || code[i].name == "UNA_ARITHM_OPER")
{
rpn.push_back(code[i].value);
}
else
{
if (buffer.empty() && code[i].value != "=" && code[i].value != "}" && code[i].value != ";")
{
buffer.push_back(code[i]);
}
else
{
/*========================================================================*/
//if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
//{
//	while (!buffer.empty())
//	{
//		if (buffer.back().name == "BIN_ARITHM_OPER")
//		{
//			rpn.push_back(buffer.back().value);
//			buffer.pop_back();
//		}
//		else break;
//	}
//	buffer.push_back(code[i]);
//}
///*========================================================================*/
//
//if (code[i].value == "*" || code[i].value == "/")
//{
//	if (buffer.back().value == "*" || buffer.back().value == "/")
//	{
//		rpn.push_back(buffer.back().value);
//		buffer.pop_back();
//	}
//	else
//	{
//		buffer.push_back(code[i]);
//	}
//}
///*========================================================================*/
//
//if (code[i].value == ")")
//{
//	while (buffer.back().value != "(")
//	{
//		rpn.push_back(buffer.back().value);
//		buffer.pop_back();
//	}
//	if (buffer.back().value == "(")
//	{
//		buffer.pop_back();
//	}
//	if (!buffer2.empty())
//	{
//		if (buffer2.back().name == "KW_IF")
//		{
//			buffer2.pop_back();
//			labels.push_back(rpn.size());
//			rpn.push_back("void_label");
//			rpn.push_back("!F");
//		}
//	}
//}
///*========================================================================*/
//
//if (code[i].value == "(")
//{
//	buffer.push_back(code[i]);
//}
///*========================================================================*/
//
//if (code[i].value == "}")
//{
//	if (buffer2.back().value == "{")
//	{
//		buffer2.pop_back();
//		rpn[labels.back()] = "@" + std::to_string(rpn.size() + 1);
//		labels.pop_back();
//	}
//}
///*========================================================================*/
//
//if (code[i].value == "=")
//{
//	buffer2.push_back(code[i]);
//}
///*========================================================================*/
//
//if (code[i].value == ";")
//{
//	while (!buffer.empty())
//	{
//		rpn.push_back(buffer.back().value);
//		buffer.pop_back();
//	}
//	rpn.push_back(buffer2.back().value);
//	buffer2.pop_back();
//}
///*========================================================================*/
//
//if (code[i].value == "end")
//{
//	while (!buffer.empty())
//	{
//		rpn.push_back(buffer.back().value);
//		buffer.pop_back();
//	}
//}
//				}
//			}
//		}
//	}









//for (int i = 0; i < code.size(); ++i)
//{
//	if (i == 15)
//	{
//		int s = 13;
//	}
//
//	if (code[i].name == "KW_IF" || code[i].name == "LBRACE" || code[i].name == "KW_FOR")
//	{
//		buffer2.push_back(code[i]);
//	}
//	else
//	{
//		if (code[i].name == "DIGIT" || code[i].name == "VAR" || code[i].name == "UNA_ARITHM_OPER")
//		{
//			rpn.push_back(code[i].value);
//		}
//		else
//		{
//			if (buffer.empty() && code[i].value != "=" && code[i].value != "}" && code[i].value != ";")
//			{
//				buffer.push_back(code[i]);
//			}
//			else
//			{
//				/*========================================================================*/
//				if (code[i].value == "+" || code[i].value == "-" || code[i].value == ">" || code[i].value == "<" || code[i].value == "==" || code[i].value == "!=")
//				{
//					while (!buffer.empty())
//					{
//						if (buffer.back().name == "BIN_ARITHM_OPER")
//						{
//							rpn.push_back(buffer.back().value);
//							buffer.pop_back();
//						}
//						else break;
//					}
//					buffer.push_back(code[i]);
//				}
//				/*========================================================================*/
//
//				if (code[i].value == "*" || code[i].value == "/")
//				{
//					if (buffer.back().value == "*" || buffer.back().value == "/")
//					{
//						rpn.push_back(buffer.back().value);
//						buffer.pop_back();
//					}
//					else
//					{
//						buffer.push_back(code[i]);
//					}
//				}
//				/*========================================================================*/
//
//				if (code[i].value == ")")
//				{
//					while (buffer.back().value != "(")
//					{
//						rpn.push_back(buffer.back().value);
//						buffer.pop_back();
//					}
//					if (buffer.back().value == "(")
//					{
//						buffer.pop_back();
//					}
//					if (!buffer2.empty())
//					{
//
//						buffer2.pop_back();
//						labels.push_back(rpn.size());
//						rpn.push_back("void_label");
//						rpn.push_back("!F");
//
//					}
//				}
//				/*========================================================================*/
//
//				if (code[i].value == "(")
//				{
//					buffer.push_back(code[i]);
//				}
//				/*========================================================================*/
//
//				if (code[i].value == "}")
//				{
//					if (buffer2.back().value == "{")
//					{
//						if (buffer2.back().name == "KW_FOR")
//						{
//							int stop = 0;
//						}
//						else
//						{
//							buffer2.pop_back();
//							rpn[labels.back()] = "@" + std::to_string(rpn.size() + 1);
//							labels.pop_back();
//						}
//					}
//				}
//				/*========================================================================*/
//
//				if (code[i].value == "=")
//				{
//					buffer2.push_back(code[i]);
//				}
//				/*========================================================================*/
//
//				if (code[i].value == ";")
//				{
//					while (!buffer.empty() && buffer.back().value != "(")
//					{
//						rpn.push_back(buffer.back().value);
//						buffer.pop_back();
//					}
//					if (!buffer2.empty())
//					{
//						if (buffer2.back().name != "KW_FOR")
//						{
//							rpn.push_back(buffer2.back().value);
//							buffer2.pop_back();
//						}
//						if (buffer2.back().name == "KW_FOR")
//						{
//							buffer2.pop_back();
//							labels.push_back(rpn.size());
//						}
//					}
//				}
//				/*========================================================================*/
//
//				if (code[i].value == "end")
//				{
//					while (!buffer.empty())
//					{
//						rpn.push_back(buffer.back().value);
//						buffer.pop_back();
//					}
//				}
//			}
//		}
//	}
//}
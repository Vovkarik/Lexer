#include "stdafx.h"
#include "Lexer.h"
#include "Token.h"

int main()
{
	std::ifstream in("input.txt");
	std::string buffer;
	std::vector<Token> tokens;
	while (getline(in, buffer))
	{
		Lexer lexer(buffer);
		tokens = lexer.Tokenize();
		for (auto & elem : tokens)
		{
			switch (elem.getType())
			{
			case OPERATOR:
				std::cout << "OPERATOR->" << elem.getText() << std::endl;
				break;
			case INTEGER:
				std::cout << "INTEGER->" << elem.getText() << std::endl;
				break;
			case FLOAT:
				std::cout << "FLOAT->" << elem.getText() << std::endl;
				break;
			case COMMENT:
				std::cout << "COMMENT->" << elem.getText() << std::endl;
				break;
			case IDENTIFIER:
				std::cout << "IDENTIFIER->" << elem.getText() << std::endl;
				break;
			case SEPARATOR:
				std::cout << "SEPARATOR->" << elem.getText() << std::endl;
				break;
			case STRING:
				std::cout << "STRING->" << elem.getText() << std::endl;
				break;
			case ERROR:
				std::cout << "ERROR->" << elem.getText() << std::endl;
				break;
			}
		}
	}
}


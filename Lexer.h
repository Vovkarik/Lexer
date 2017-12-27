#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Token.h"

class Lexer
{
public:
	Lexer();
	Lexer(std::string input);
	~Lexer();
	std::vector<Token> Tokenize();
private:
	std::string m_input;
	std::vector<Token> m_tokens;
	size_t m_pos, m_length;
	std::string OPERATOR_CHARS = "=+-*/^%!&|";
	std::string SEPARATOR_CHARS = ";,:'(){}[]";
	std::vector<std::string> KEY_WORD = {"IF", "WHILE", "THEN", "ELSE", "FOR", "RETURN"};
	void tokenizeInteger();
	void tokenizeBinary();
	void tokenizeOctal();
	void tokenizeHex();
	void tokenizeFloat(std::string buffer);
	void tokenizeOperator();
	void tokenizeSeparator();
	void tokenizeIdentifier();
	void tokenizeString();
	void tokenizeError(std::string buffer);
	void addToken(const TokenType & type, const std::string & text);
	char peek(const int & relativePosition);
	char next();
};


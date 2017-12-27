#pragma once
#include <string>

enum TokenType
{
	INTEGER,
	FLOAT,
	OPERATOR,
	COMMENT,
	IDENTIFIER,
	KEYWORD,
	SEPARATOR,
	STRING,
	ERROR
};

class Token
{
public:
	Token();
	Token(TokenType type, std::string text);
	Token(const Token& other);
	Token(Token&& other);
	Token& operator=(const Token& other);
	TokenType const getType();
	void setType(TokenType type);
	std::string const getText();
	void setText(std::string text);
private:
	TokenType m_type;
	std::string m_text;
};
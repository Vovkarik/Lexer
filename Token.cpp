#include "stdafx.h"
#include "Token.h"


Token::Token()
{
}

Token::Token(TokenType type, std::string text)
{
	setType(type);
	setText(text);
}

Token::Token(const Token & other)
	:Token(other.m_type, other.m_text)
{
}

Token::Token(Token && other)
	: Token()
{
	Token tmp;
	tmp = *this;
	*this = other;
	other = tmp;
}

Token & Token::operator=(const Token & other)
{
	if (this != std::addressof(other))
	{
		m_type = other.m_type;
		m_text = other.m_text;
	}
	return *this;
}

const TokenType Token::getType()
{
	return m_type;
}

void Token::setType(TokenType type)
{
	m_type = type;
}

const std::string Token::getText()
{
	return m_text;
}

void Token::setText(std::string text)
{
	m_text = text;
}
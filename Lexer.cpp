#include "stdafx.h"
#include "Lexer.h"
#include "Token.h"

Lexer::Lexer()
{
}

Lexer::Lexer(std::string input)
{
	m_input = input;
	m_length = input.length();
}


Lexer::~Lexer()
{
}

std::vector<Token> Lexer::Tokenize()
{
	while (m_pos < m_length)
	{
		char current = peek(0);
		if (isdigit(current)) tokenizeInteger();
		else if (current == '.') tokenizeFloat("");
		else if (isalpha(current)) tokenizeIdentifier();
		else if (current == '"') tokenizeString();
		else if (OPERATOR_CHARS.find(current) != std::string::npos) tokenizeOperator();
		else if (SEPARATOR_CHARS.find(current) != std::string::npos) tokenizeSeparator();
		else if (current == ' ') current = next();
		else
		{
			std::string buffer;
			tokenizeError(buffer);
		}
	}
	return m_tokens;
}

void Lexer::tokenizeFloat(std::string buffer)
{
	char current = peek(0);
	buffer += current;
	current = next();
	if (!isdigit(current))
	{
		tokenizeError(buffer);
		return;
	}
	while (isdigit(current))
	{
		buffer += current;
		current = next();
	}
	if ((OPERATOR_CHARS.find(current) == std::string::npos) && (SEPARATOR_CHARS.find(current) == std::string::npos) && (current != ' ') && (current != '\0'))
	{
		tokenizeError(buffer);
	}
	else
	{
		addToken(FLOAT, buffer);
	}
}

void Lexer::tokenizeInteger()
{
	std::string buffer;
	char current = peek(0);
	/*buffer += current;
	current = next();
	if (current == 'b')*/
	while (isdigit(current))
	{
		buffer += current;
		current = next();
	}
	if (current == '.')
	{
		tokenizeFloat(buffer);
	}
	else if ((OPERATOR_CHARS.find(current) == std::string::npos) && (SEPARATOR_CHARS.find(current) == std::string::npos) && (current != ' ') && (current != '\0'))
	{
		tokenizeError(buffer);
	}
	else
	{
		addToken(INTEGER, buffer);
	}
}

void Lexer::tokenizeOperator()
{
	std::stringstream op;
	std::string opS;
	char currentCh = peek(0);
	char nextCh = next();
	if (nextCh == '*')
	{
		nextCh = next();
		while (nextCh != '*' || peek(1) != '/')
		{
			op << nextCh;
			nextCh = next();
		}
		m_pos += 2;
		op >> opS;
		addToken(COMMENT, opS);
	}
	else if (nextCh == '/')
	{
		nextCh = next();
		while (static_cast<int>(nextCh) != 0)
		{
			op << nextCh;
			nextCh = next();
		}
		op >> opS;
		addToken(COMMENT, opS);
	}
	else
	{
		op << currentCh;
		op >> opS;
		addToken(OPERATOR, opS);
	}
}

void Lexer::tokenizeSeparator()
{
	std::stringstream sep;
	std::string sepS;
	sep << peek(0);
	sep >> sepS;
	addToken(SEPARATOR, sepS);
	m_pos++;
}

void Lexer::tokenizeIdentifier()
{
	std::string buffer;
	char current = peek(0);
	buffer += current;
	current = next();
	while (isalpha(current) || isdigit(current))
	{
		buffer += current;
		current = next();
	}
	if ((OPERATOR_CHARS.find(current) == std::string::npos) && (SEPARATOR_CHARS.find(current) == std::string::npos) && (current != ' ') && (current != '\0'))
	{
		tokenizeError(buffer);
	}
	else
	{
		addToken(IDENTIFIER, buffer);
	}
}

void Lexer::tokenizeString()
{
	std::string buffer;
	next();
	char current = peek(0);
	while (!(current == '"' && buffer[buffer.size() - 1] != '\\'))
	{
		if (current == '\0')
		{
			addToken(ERROR, "\"" + buffer);
			return;
		}
		else if ((current == '"' && buffer[buffer.size() - 1] != '\\'))
		{
			current = next();
		}
		buffer += current;
		current = next();
	}
	next();
	addToken(STRING, buffer);
}

void Lexer::tokenizeError(std::string buffer)
{
	char current = peek(0);
	while ((OPERATOR_CHARS.find(current) == std::string::npos) && (SEPARATOR_CHARS.find(current) == std::string::npos) && (current != ' ') && (current != '\0'))
	{
		buffer += current;
		current = next();
	}
	addToken(ERROR, buffer);
}

void Lexer::addToken(TokenType const & type, std::string const & text)
{
	m_tokens.push_back(Token(type, text));
}

char Lexer::peek(int const & relativePosition)
{
	int position = m_pos + relativePosition;
	if (position >= m_length) return '\0';
	return m_input[position];
}

char Lexer::next()
{
	m_pos++;
	return peek(0);
}

#include "token.h"

Token::Token(string token_type_in, string token_value_in, int line_number_in)
{
	token_type = token_type_in;
	token_value = token_value_in;
	line_number = line_number_in;
}

Token::~Token()
{
 
}

string Token::toString(Token token_to_print)
{
  return "";
}

string Token::getTokenType()
{
	return token_type;
}

string Token::getTokenValue()
{
	return token_value;
}
int Token::getLineNumber()
{
	return line_number;
}

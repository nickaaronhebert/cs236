#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <queue>

using namespace std;

class Token
{
	private:
	
	public:
	string token_type = "";
	string token_value = "";
	int line_number = 0;
	Token(string token_type, string token_value, int line_number);
	~Token();
	string toString(Token token_to_print);

};

	// string getTokenType();
	// string getTokenValue();
	// int getLineNumber();
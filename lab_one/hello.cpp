#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "scanner.h"


using namespace std;

// bool isPunctuation(char chary, Token* token_array[])
// {
// 	for (int i = 0; i < token_array.length() ; ++i)
// 	{
		
// 	}

// 	return true;
// }

// void analyze_string(string string_to_analyze, Token* token_array[])
// {
// 	for (int i = 0; i < string_to_analyze.length(); i++)
// 	{
// 		if (isPunctuation(string_to_analyze[i], token_array))
// 		{
			
// 		}
// 	}
// 	return;
// }

// int open_file(string file_to_read)
// {
// 	string line;
// 	ifstream myfile ("input1.txt");
// 	if (myfile.is_open())
// 	{
// 		while (getline(myfile, line))
// 		{
// 			string testString = line;
// 			cout << testString << endl;
// 			analyze_string(testString);
// 		}
// 	}
// 	return 0;
// }

int main ()
{
	
	Scanner scanner = Scanner();
	scanner.input_and_prepare_file("in61.txt");
  return 0;
}

// RULES	The string "Rules"	Rules
// QUERIES	The string "Queries"	Queries
// ID	An identifier is a letter followed by zero or more letters or digits, and is not a keyword (Schemes, Facts, Rules, Queries).	
// Valid Identifiers	Invalid Identifiers
// Identifier1	1stPerson
// Person	Schemes
// STRING	A string is a sequence of characters enclosed in single quotes. White space (space, tab) is not skipped when inside a string. Newlines are not allowed in a string. If the end of line or end of file is found before the end of the string, it is an error.	'This is a string'
// '' -- (The empty string)
//EOF	The end of the input file.	
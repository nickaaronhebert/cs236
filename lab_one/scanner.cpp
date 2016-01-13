#include "scanner.h"
#include <stdio.h>
#include <ctype.h>

Scanner::Scanner()
{

}

Scanner::~Scanner()
{

}

void Scanner::check_token_list(queue<Token>token_queue)
{
  queue<Token>temp_queue;
  temp_queue = token_queue;
  while (!temp_queue.empty())
  {
    cout << temp_queue.front().token_type;
    cout << temp_queue.front().token_value;
    cout << temp_queue.front().line_number;
    temp_queue.pop();
  }
}

string Scanner::scan_string(char char_to_add)
{
  while (!char_queue.front() == '\'')
  {
    id_string+= char_to_add;
    char_queue.pop();
  }
  return id_string;
}

string Scanner::scan_id()
{
  bool isLetter = isalpha(char_queue.front());
  string id;
  if (isLetter == false)
  {
    return "An error has occured.";
  }
  while (isalnum(char_queue.front()))
  {
    id = id + char_queue.front();
    char_queue.pop();
  }
  return id;
}

void Scanner::recognize_ids(string token_name, int line_number)
{
  if (token_name == "Schemes")
  {
    Token token = Token("SCHEMES", "Schemes", line_number);
    token_list.push(token);
  }
  else if (token_name == "Rules")
  {
    Token token = Token("RULES", "Rules", line_number);
    token_list.push(token);
  }
  else if (token_name == "Queries")
  {
    Token token = Token("QUERIES", "Queries", line_number);
    token_list.push(token);
  }
  else if (token_name == "Facts")
  {
    Token token = Token("FACTS", "Facts", line_number);
    token_list.push(token);
  }
  else
  {
    Token token = Token("ID", token_name , line_number);
    token_list.push(token); 
  }
  return;
}

void Scanner::recognize_tokens()
{
  char curr_char = char_queue.front();

  //cout << endl << endl << curr_char << curr_char<<curr_char;
  switch(curr_char)
  {
      case ',':
      {
        Token token = Token("COMMA", ",", line_number);
        token_list.push(token);
        break;
      }
      case '+':
      {
        line_number++;
        break;
      }
      case '.':
      {
        Token token = Token("PERIOD", ".", line_number);
        token_list.push(token);
        break;
      }
      case '?':
      {
        Token token = Token("Q_MARK", "?", line_number);
        token_list.push(token);
        break;
      }
      case '(':
      {
        Token token = Token("LEFT_PAREN", "(", line_number);
        token_list.push(token);
        break;
      }
      case ')':
      {
        Token token = Token("RIGHT_PAREN", ")", line_number);
        token_list.push(token);
        break;
      }
      case ':':
      {
        if (char_queue.front() == '-')
        {
          Token token = Token("COLON_DASH", ":-", line_number);
          token_list.push(token);
          break;
        }
        Token token = Token("COLON", ":", line_number);
        token_list.push(token);
        break;
      }
      case '\'':
      {
        string token_string = scan_string(curr_char);
        Token token = Token("STRING", token_string, line_number);
        token_list.push(token);
        break;
      }
      default:
        string token_id = scan_id();
        recognize_ids(token_id, line_number);
        break;
  }
  
  // switch (curr_char)
}

queue <Token>Scanner::scan_file(queue<char>char_queue_to_scan)
{
  while (!char_queue_to_scan.empty())
  {
    cout << char_queue_to_scan.front();
    //cout << char_queue_to_scan.front();
    //check_token_list(token_list);
    recognize_tokens();
    char_queue_to_scan.pop();
  }
  return token_list;
}

void Scanner::input_and_prepare_file(string file_name)
{
  ifstream myfile (file_name);
  char curr_char;
  if (myfile.is_open())
  {
    while (myfile.get(curr_char))
    {
      switch (curr_char)
      {
        case '\'':
          char_queue.push(curr_char);
          while (curr_char != '\'')
          {
            char_queue.push(curr_char);
          }
          break;
        case '#':
          while (curr_char != '\n')
          {
            myfile.get(curr_char);
          }
          break;
        case ' ':
          break;
          break;
        case '\n':
          char_queue.push('+');
        case '\t':
          break;
        default:
          char_queue.push(curr_char);
          break;
      }
    }    
  }
  queue<char>temp_queue;
  temp_queue = char_queue;
  while (!temp_queue.empty())
  {
    cout << temp_queue.front();
    temp_queue.pop();
  }
  scan_file(char_queue);
  // while (!token_list.empty())
  // {
  //   cout << endl << token_list.front().token_type;
  //   cout << endl << token_list.front().token_value;
  //   cout << endl << token_list.front().line_number;
  //   cout <<endl;
  //   token_list.pop();
  // }
  
}

// COMMA The ',' character ,
// PERIOD  The '.' character .
// Q_MARK  The '?' character ?
// LEFT_PAREN  The '(' character (
// RIGHT_PAREN The ')' character )
// COLON The ':' character :
// COLON_DASH  The string ":-" :-
// SCHEMES The string "Schemes"  Schemes
// FACTS The string "Facts"  Facts
// RULES The string "Rules"  Rules
// QUERIES The string "Queries"  Queries
// ID  An identifier is a letter followed by zero or more letters or digits, and is not a keyword (Schemes, Facts, Rules, Queries).  
// Valid Identifiers Invalid Identifiers
// Identifier1 1stPerson
// Person  Schemes
// STRING  A string is a sequence of characters enclosed in single quotes. White space (space, tab) is not skipped when inside a string. Newlines are not allowed in a string. If the end of line or end of file is found before the end of the string, it is an error.  'This is a string'
// '' -- (The empty string)
// EOF The end of the input file.  







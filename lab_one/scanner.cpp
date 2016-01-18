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
	id_string = "";
	char_queue.pop();
  while (char_queue.front() != '\'')
  {
   if (char_queue.front() == '+')
    {
	   return "";
	}
    id_string+= char_queue.front();
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
	char_queue.pop();
    return "";
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
		char_queue.pop();
        break;
      }
      case '+':
      {
        line_number++;
		char_queue.pop();
        break;
      }
      case '.':
      {
        Token token = Token("PERIOD", ".", line_number);
        token_list.push(token);
		char_queue.pop();
        break;
      }
      case '?':
      {
        Token token = Token("Q_MARK", "?", line_number);
        token_list.push(token);
		char_queue.pop();
        break;
      }
      case '(':
      {
        Token token = Token("LEFT_PAREN", "(", line_number);
        token_list.push(token);
		char_queue.pop();
        break;
      }
      case ')':
      {
        Token token = Token("RIGHT_PAREN", ")", line_number);
        token_list.push(token);
		char_queue.pop();
        break;
      }
      case ':':
      {
		char_queue.pop();
        if (char_queue.front() == '-')
        {
          Token token = Token("COLON_DASH", ":-", line_number);
          token_list.push(token);
		  char_queue.pop();
          break;
        }
        Token token = Token("COLON", ":", line_number);
        token_list.push(token);
        break;
      }
      case '\'':
      {
        string token_string = scan_string(curr_char);
		if (token_string == "")
		{
			handle_error(char_queue);
			break;
		}
        Token token = Token("STRING", token_string, line_number);
        token_list.push(token);
		char_queue.pop();
        break;
      }
	  case '%':
	  {
		  Token token = Token("EOF", "", line_number);
		  token_list.push(token);
		  char_queue.pop();
		  break;
	  }

      default:
        string token_id = scan_id();
		if (token_id == "")
		{
			handle_error(char_queue);
			break;
		}
        recognize_ids(token_id, line_number);
        break;
  }
}

queue <Token>Scanner::scan_file()
{
  while (!char_queue.empty())
  {
    cout << char_queue.front();
    //cout << char_queue_to_scan.front();
    //check_token_list(token_list);
    recognize_tokens();
    //char_queue.pop();
  }
  return token_list;
}

queue<Token> Scanner::input_and_prepare_file(string file_name)
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
		  myfile.get(curr_char);
          while (curr_char != '\'' && curr_char != '\n')
          {
            char_queue.push(curr_char);
			myfile.get(curr_char);
          }
		  char_queue.push(curr_char);
          break;
        case '#':
          while (curr_char != '\n')
          {
            myfile.get(curr_char);
          }
		  line_number++;
          break;
        case ' ':
          break;
        case '\n':
          char_queue.push('+');
		  break;
        case '\t':
          break;
        default:
          char_queue.push(curr_char);
          break;
      }
    }
	char_queue.push('%');
  }
  queue<char>temp_queue;
  temp_queue = char_queue;
  while (!temp_queue.empty())
  {
    cout << temp_queue.front();
    temp_queue.pop();
  }
  scan_file();
 
  return token_list;
}

void Scanner::print_file(queue<Token>token_queue, string output_file)
{
	int total_tokens = 0;
	while (!token_queue.empty())
	{
		if (token_queue.front().token_type == "ERROR")
		{
			final_string += "Input error on line " + to_string(token_queue.front().line_number);
			ofstream out;
			out.open(output_file);
			out << final_string;
			out.close();
			return;
		}
		total_tokens++;
		final_string += token_queue.front().toString();
		token_queue.pop();
	}
	ofstream out;
	out.open(output_file);
	out << final_string;
	out.close();
}

void Scanner::handle_error(queue<char>&char_queue)
{
	while (char_queue.empty() == false) { char_queue.pop(); }
	Token token = Token("ERROR", "", line_number);
	token_list.push(token);

}

 







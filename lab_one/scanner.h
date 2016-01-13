#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include "token.h"
#include <queue>

using namespace std;

class Scanner
{
  private:
  queue<char>char_queue;
  queue<Token>token_list;
  string id_string;

  public: 
  Scanner();
  ~Scanner();
  int line_number = 1;
  void input_and_prepare_file(string file_name);
  void recognize_tokens();
  string scan_id();
  string scan_string(char chary);
  void recognize_ids(string token_name, int line_number);
  queue <Token>scan_file();
  void check_token_list(queue<Token>token_queue);
};
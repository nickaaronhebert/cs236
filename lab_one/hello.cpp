#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "scanner.h"


using namespace std;


int main ()
{
	
	Scanner scanner = Scanner();
	scanner.input_and_prepare_file("in61.txt");
  return 0;
}


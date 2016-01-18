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
	scanner.print_file(scanner.input_and_prepare_file("in12.txt"), "out61.txt");
	return 0;
}


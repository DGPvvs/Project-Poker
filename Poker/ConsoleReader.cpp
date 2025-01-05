#include "ConsoleReader.h"
#include <iostream>

std::string ConsoleReader::ReadLine()
{
	std::string s;

	std::getline(std::cin, s);

	return s;
}

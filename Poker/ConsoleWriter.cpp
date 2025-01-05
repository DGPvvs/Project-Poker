#include <iostream>

#include "ConsoleWriter.h"

void ConsoleWriter::WriteLine(std::string s)
{
	std::cout << s << std::endl;
}

void ConsoleWriter::WriteLine()
{
	std::cout << std::endl;
}

void ConsoleWriter::Write(std::string s)
{
	std::cout << s;
}

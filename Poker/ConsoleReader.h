#pragma once
#include "IReader.h"
class ConsoleReader : public IReader
{
public:
    ConsoleReader() {}
    virtual ~ConsoleReader() {}
    virtual std::string ReadLine();
};


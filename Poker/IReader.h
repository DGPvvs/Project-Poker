#pragma once
#include <string>

class IReader
{
public:
    IReader() {}
    virtual ~IReader() {}
    virtual std::string ReadLine() = 0;
};

#pragma once
#include <string>

class IWriter
{
public:
    IWriter() {}
    virtual ~IWriter() {}
    virtual void WriteLine(std::string s) = 0;
    virtual void WriteLine() = 0;
    virtual void Write(std::string s) = 0;
};

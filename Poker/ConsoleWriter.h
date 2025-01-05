#pragma once

#include "IWriter.h"

class ConsoleWriter : public IWriter
{
public:
    ConsoleWriter() {}
    virtual ~ConsoleWriter() {}
    virtual void WriteLine(std::string s);
    virtual void WriteLine();
    virtual void Write(std::string s);
};


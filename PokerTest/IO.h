#pragma once
#include <string>
#include <vector>

#include "../Poker/IReader.h"
#include "../Poker/IWriter.h"

class IO : public IWriter, public IReader
{
private:
    std::vector<std::string> outputs;
    int outputIndex;

public:
    IO(std::vector<std::string>& v) :
        outputs(v),
        outputIndex(0)
    {
    }

    virtual ~IO() {}
    virtual void WriteLine(std::string s);
    virtual void WriteLine();
    virtual void Write(std::string s);
    virtual std::string ReadLine();
};


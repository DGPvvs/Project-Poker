#include "pch.h"
#include "IO.h"

std::string IO::ReadLine()
{
    return this->outputs[this->outputIndex++];
}

#include <number.h>

#include <keywords.h>

#include <regex>

bool Number::isAValidNumber(std::string digits)
{
    std::smatch dummy;
    return std::regex_match(digits, dummy, std::regex(R"(^\s*\d+(?:\s*\d+)*\s*$)"));
}

Number::Number(std::string digits)
{
    require (Number::isAValidNumber(digits));

    this->digits = digits;
}

Number::Number(const char* digits) : Number(std::string(digits))
{
    ;
}

Number operator "" nb(const char* str, size_t _)
{
    return Number(str);
}


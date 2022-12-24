#include <number.h>

#include <utils/require.h>

Number::Number(String digits)
{
    require (digits =~ R"(^\s*\d+(?:\s*\d+)*\s*$)"_regex);

    this->digits = digits;
}

Number::Number(std::string digits) : Number(String(digits))
{
    ;
}

Number::Number(const char* digits) : Number(String(digits))
{
    ;
}

Number operator "" nb(const char* str, size_t _)
{
    return Number(str);
}

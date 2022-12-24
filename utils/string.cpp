#include "string.h"

#include <regex> // std::regex_match

String::String() : str(){}
String::String(const char* str) : str(str){}
String::String(std::string str) : str(str){}

bool String::operator=(RegexToCheck regex)
{
    std::smatch dummy;
    return std::regex_match(this->str, dummy, std::regex(regex.str));
}

Regex::Regex(std::string str) : str(str){}

RegexToCheck Regex::operator~()
{
    return RegexToCheck{this->str};
}

Regex operator "" _regex(const char* str, size_t _)
{
    return Regex(std::string(str));
}

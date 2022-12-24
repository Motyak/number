#include "string.h"

#include <regex> // std::regex_match, std::regex_replace

String::String() : str(){}
String::String(const char* str) : str(str){}
String::String(std::string str) : str(str){}

String::operator std::string() const
{
    return this->str;
}

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

Regex::operator std::string() const
{
    return this->str;
}

Regex operator "" _regex(const char* str, size_t _)
{
    return Regex(std::string(str));
}

String erase(Regex p_regex, String p_str)
{
    auto str = std::string(p_str);
    auto regex = std::regex(std::string(p_regex));
    return std::regex_replace(str, regex, "");
}

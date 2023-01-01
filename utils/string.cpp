#include "string.h"

#include <regex> // std::regex_match, std::regex_replace

Matches::Matches(std::vector<std::string> val)
{
    this->val = val;
}

Matches::operator bool() const
{
    return this->val.size() > 0;
}

Matches::operator std::vector<std::string>() const
{
    return this->val;
}

String::String(std::string str)
{
    this->str = str;
}

String::operator std::string() const
{
    return this->str;
}

Matches String::operator=(RegexToCheck p_regex)
{
    std::regex regex(p_regex.str);
    std::sregex_iterator it(this->str.begin(), this->str.end(), regex);
    std::sregex_iterator end;

    std::vector<std::string> res;
    auto get_str = [](std::smatch m){return m[0];};
    std::transform(it, end, std::back_inserter(res), get_str);
    
    return res;
}

Regex::Regex(std::string str)
{
    this->str = str;
}

RegexToCheck Regex::operator~()
{
    return RegexToCheck{this->str};
}

Regex::operator std::string() const
{
    return this->str;
}

Regex operator "" _regex(const char* str, size_t)
{
    return std::string(str);
}

String operator-(String p_str, Regex p_regex)
{
    auto str = std::string(p_str);
    auto regex = std::regex(std::string(p_regex));
    return std::regex_replace(str, regex, "");
}

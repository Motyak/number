#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string> // std::string
#include <vector> // std::vector

struct RegexToCheck
{
    std::string str;
};

class Matches
{
  private:
    std::vector<std::string> val;

  public:
    Matches(std::vector<std::string> val);

    operator bool() const;
    operator std::vector<std::string>() const;
};

class String
{
  private:
    std::string str;

  public:
    String();
    String(const char* str);
    String(std::string str);

    operator std::string() const;
    Matches operator=(RegexToCheck regex);
};

class Regex
{
  private:
    std::string str;
    
  public:
    Regex(std::string str);
    
    RegexToCheck operator~();

    operator std::string() const;
};

Regex  operator "" _regex(const char* str, size_t _);

String operator-(String, Regex);

#endif // UTILS_STRING_H

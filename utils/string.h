#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string> // std::string

struct RegexToCheck
{
    std::string str;
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
    bool operator=(RegexToCheck regex);
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

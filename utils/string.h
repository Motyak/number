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
    
    bool operator=(RegexToCheck regex);
};

class Regex
{
  private:
    std::string str;
    
  public:
    Regex(std::string str);
    
    
    RegexToCheck operator~();
};

Regex  operator "" _regex(const char* str, size_t _);

#endif // UTILS_STRING_H

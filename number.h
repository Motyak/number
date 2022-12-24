#ifndef NUMBER_H
#define NUMBER_H

#include <utils/string.h> // String

#include <string> // std::string

class Number
{
  private:
    String digits;

  public:
    Number(String digits);
    Number(std::string digits);
    Number(const char* digits);
};

Number operator "" nb(const char*, size_t);

#endif // NUMBER_H

#ifndef NUMBER_H
#define NUMBER_H

#include <utils/string.h> // String

#include <string> // std::string
#include <vector> // std::vector

class Digit
{
  private:
    int val;

  public:
    Digit(int);
    Digit(char);

    Digit operator~();

    bool equals(Digit);
};

bool operator==(Digit, Digit);

class Number
{
  private:
    std::vector<Digit> digits;

  public:
    Number(std::vector<Digit>);
    Number(String);
    Number(std::string);
    Number(const char*);

    bool operator==(Number other);
};

Number operator "" nb(const char*, size_t);

class Quantifier
{
  private:
    int val;

  public:
    Quantifier(int);

    int to_int();
};

using integral = unsigned long long int;
Quantifier operator "" _(integral);

Number operator*(Quantifier, Digit);

#endif // NUMBER_H

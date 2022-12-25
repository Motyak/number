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

    // called by '''bool operator==(Digit, Digit)'''
    bool equals(Digit);
};

// required by std::vector, when doing std::vector<Digit> comparison
bool operator==(Digit, Digit);

class Number
{
  private:
    std::vector<Digit> digits;
    
    Number(String);

  public:
    Number(std::vector<Digit>);
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

    explicit operator int() const;
};

using integral = unsigned long long int;
Quantifier operator "" _(integral);

Number operator*(Quantifier, Digit);

#endif // NUMBER_H

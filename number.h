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

    explicit operator char() const;

    // called by '''bool operator==(Digit, Digit)'''
    bool equals(Digit);
};

// required by std::vector, when doing std::vector<Digit> comparison
bool operator==(Digit, Digit);

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

std::string operator*(Quantifier, char);

class Number
{
  private:
    std::vector<Digit> digits;
    
    Number(String);
    explicit operator String() const;

  public:
    Number(std::vector<Digit>);
    Number(std::string);
    Number(const char*);

    // called by '''bool operator==(Number, Number)'''
    bool equals(Number);
    std::vector<Number> operator[](Quantifier);
};

// required by std::vector, when doing std::vector<Number> comparison
bool operator==(Number, Number);

Number operator "" nb(const char*, size_t);

#endif // NUMBER_H

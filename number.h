#ifndef NUMBER_H
#define NUMBER_H

#include <utils/string.h> // String

#include <string> // std::string
#include <vector> // std::vector

using llong = long long; //convenient

class Digit
{
  private:
    int val;

  public:
    Digit(int val);
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
    Quantifier(int val);

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
    Number(int);
    explicit operator String() const;
    explicit operator int() const;
    explicit operator llong() const;

  public:
    Number(std::vector<Digit> digits);
    Number(std::string);
    Number(const char*);

    // called by '''bool operator==(Number, Number)'''
    bool equals(Number);

    std::vector<Number> operator[](Quantifier);
    Number operator+(Number);
};

// required by std::vector, when doing std::vector<Number> comparison
bool operator==(Number, Number);

Number operator "" nb(const char*, size_t);

// used by variadic function sum
Number sum(Number, Number);

template <typename ...T>
Number sum(Number a, Number b, T... others)
{
    return a + sum(b, others...);
}

Number sum(std::vector<Number>);

#endif // NUMBER_H

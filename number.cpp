#include <number.h>

#include <utils/require.h>

#include <bits/stdc++.h> // INT_MAX
#include <sstream> // std::stringstream

Digit::Digit(int i)
{
    require (0 <= i and i <= 9);

    this->val = i;
}

Digit::Digit(char c) : Digit(int(c - '0'))
{
    ;
}

Digit Digit::operator~()
{
    return 9 - this->val;
}

bool Digit::equals(Digit other)
{
    return this->val == other.val;
}

bool operator==(Digit a, Digit b)
{
    return a.equals(b);
}

Number::Number(std::vector<Digit> digits)
{
    this->digits = digits;
}

Number::Number(String p_digits)
{
    require (p_digits =~ R"(^\s*\d+(?:\s*\d+)*\s*$)"_regex);

    std::string digits = (p_digits - R"(\s+)"_regex);
    this->digits = std::vector<Digit>(digits.begin(), digits.end());
}

Number::Number(std::string digits) : Number(String(digits))
{
    ;
}

Number::Number(const char* digits) : Number(String(digits))
{
    ;
}

Number operator "" nb(const char* str, size_t _)
{
    return Number(str);
}

bool Number::operator==(Number other)
{
    return this->digits == other.digits;
}

Quantifier::Quantifier(int val)
{
    require (val >= 0);

    this->val = val;
}

Quantifier::operator int() const
{
    return this->val;
}

Quantifier operator "" _(integral i)
{
    require (0 <= i and i <= INT_MAX); // 2 147 483 647 <=> 2^31 - 1

    return Quantifier{int(i)};
}

Number operator*(Quantifier quantifier, Digit digit)
{
    return Number(std::vector<Digit>(int(quantifier), digit));
}

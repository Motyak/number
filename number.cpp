#include <number.h>

#include <utils/require.h>

#include <bits/stdc++.h> // INT_MAX

Digit::operator char() const
{
    return this->val + '0';
}

Digit::Digit(int val)
{
    require (0 <= val and val <= 9);

    this->val = val;
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

    std::string digits = p_digits - R"(\s+)"_regex;
    this->digits = std::vector<Digit>(digits.begin(), digits.end());
}

Number::Number(int i) : Number(std::to_string(i))
{
    ;
}

Number::operator String() const
{
    std::vector<char> chars;
    auto to_char = [](Digit d){return char(d);};
    std::transform(this->digits.begin(), this->digits.end(), std::back_inserter(chars), to_char);
    return std::string(chars.begin(), chars.end());
}

Number::operator int() const
{
    std::string str = String(*this);
    return std::stoi(str);
}

Number::operator llong() const
{
    return int(*this);
}

Number::Number(std::string digits) : Number(String(digits))
{
    ;
}

Number::Number(const char* digits) : Number(String(digits))
{
    ;
}

Number operator "" nb(const char* str, size_t)
{
    return str;
}

bool Number::equals(Number other)
{
    return this->digits == other.digits;
}

std::vector<Number> Number::operator[](Quantifier qu)
{
    bool equally_dividable = this->digits.size() % int(qu) == 0;
    require (equally_dividable);

    Quantifier chunk_size = this->digits.size() / int(qu);
    Regex regex = chunk_size * '.';
    std::vector<std::string> matches = String(*this) =~ regex;

    return std::vector<Number>(matches.begin(), matches.end());
}

Number Number::operator+(Number other)
{
    require ( llong(*this) + llong(other) <= INT_MAX);

    return int(*this) + int(other);
}

bool operator==(Number a, Number b)
{
    return a.equals(b);
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

    return int(i);
}

std::string operator*(Quantifier qu, char ch)
{
    return std::string(int(qu), ch);
}

Number sum(Number a, Number b)
{
    return a + b;
}

Number sum(std::vector<Number> numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), "0"nb);
}

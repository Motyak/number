#include <number.h>

#include <utils/require.h>

#include <bits/stdc++.h> // INT_MAX

Digit::operator char() const
{
    return char(this->val + '0');
}

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

Number::operator String() const
{
    std::vector<char> chars;
    auto to_char = [](Digit d){return char(d);};
    std::transform(this->digits.begin(), this->digits.end(), std::back_inserter(chars), to_char);
    return std::string(chars.begin(), chars.end());
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

bool Number::equals(Number other)
{
    return this->digits == other.digits;
}

std::vector<Number> Number::operator[](Quantifier qu)
{
    bool equally_dividable = ((this->digits.size() % int(qu)) == 0);
    require (equally_dividable);

    Quantifier chunk_size = this->digits.size() / int(qu);
    Regex regex = (chunk_size * '.');
    std::vector<std::string> matches = (String(*this) =~ regex);

    std::vector<Number> numbers;
    auto to_number = [](std::string str){return Number(str);};
    std::transform(matches.begin(), matches.end(), std::back_inserter(numbers), to_number);
    return numbers;
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

    return Quantifier{int(i)};
}

std::string operator*(Quantifier qu, char ch)
{
    return std::string(int(qu), ch);
}

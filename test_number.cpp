#include <number.h>

#include <catch_amalgamated.hpp>

#include <bits/stdc++.h> // INT_MAX

TEST_CASE("Create a digit -succeeds-")
{
    { Digit digit = 9; }

    { Digit digit = '9'; }

    { auto digit = Digit(9); }

    { auto digit = Digit{9}; }
}

TEST_CASE("Create a digit -fails- (negative number)")
{
    REQUIRE_THROWS(Digit(-1));
}

TEST_CASE("Create a digit -fails- (number exceeding 1 digit)")
{
    REQUIRE_THROWS(Digit(11));
}

TEST_CASE("Create a digit -fails- (char which isn't a number")
{
    REQUIRE_THROWS(Digit('x'));
}

TEST_CASE("Create a number -succeeds-")
{

    { Number nb = "123 456"; }

    { auto nb = "123 456"nb; }

    {
        std::string str = "123 456";
        Number nb = str;
    }


    { Number nb("123 456"); }

    { auto nb = Number("123 456"); }

    {
        std::string str = "123 456";
        Number nb(str);
    }

    {
        std::string str = "123 456";
        auto nb = Number(str);
    }


    { Number nb{"123 456"}; }

    { auto nb = Number{"123 456"}; }

    {
        std::string str = "123 456";
        Number nb{str};
    }

    {
        std::string str = "123 456";
        auto nb = Number{str};
    }
}

TEST_CASE("Create a number -fails-")
{
    REQUIRE_THROWS(Number("fds"));
}

TEST_CASE("Create a quantifier -succeeds-")
{
    { auto nb = Quantifier{3}; }
    { auto nb = 3_; }
}

TEST_CASE("Create a quantifier -fails- (negative number)")
{
    REQUIRE_THROWS(Quantifier{-1});
}

TEST_CASE("Create a quantifier -fails- (number exceeding max value)")
{
    REQUIRE_THROWS(2147483648_);
}

TEST_CASE("Quantifier multiply operator, Number equal operator")
{
    bool equality = ( Number(6_ * '9') == "999 999"nb );
    REQUIRE (equality);
}

TEST_CASE("Number subscript operator with Quantifier")
{
    std::vector<Number> a = "123 456"nb[3_];
    std::vector<Number> b = {"12"nb, "34"nb, "56"nb};

    REQUIRE (a == b);
}

TEST_CASE("sum of Number -succeeds-")
{
    Number a = std::to_string(INT_MAX);
    Number b = "0";
    a + b;
}

TEST_CASE("sum of Number -fail- (exceeding max value)")
{
    Number a = std::to_string(INT_MAX);
    Number b = "1";
    REQUIRE_THROWS(a + b);
}

TEST_CASE("sum of a vector<Number>")
{
    std::vector<Number> numbers = {"123"nb, "111"nb, "0"nb};
    Number res = sum(numbers);
    REQUIRE (res == "234"nb);
}

TEST_CASE("varidiac function sum of a multiple Number")
{
    Number res = sum("123"nb, "111"nb, "0"nb);
    REQUIRE (res == "234"nb);
}

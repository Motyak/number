#include <number.h>

#include <catch_amalgamated.hpp>

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
    bool equality = ( (6_ * '9') == "999 999"nb );
    REQUIRE (equality);
}

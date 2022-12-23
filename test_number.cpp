#include <number.h>

#include <lib/catch_amalgamated.hpp>

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


#include <string>

class Number
{
  public:
    static bool isAValidNumber(std::string);

  private:
    std::string digits;

  public:
    Number(std::string digits);
    Number(const char* digits);
};

Number operator "" nb(const char*, size_t);

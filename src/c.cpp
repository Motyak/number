#include <keywords.h>

#include <cmath> // pow()

template <typename T>
using List = std::vector<T>;

struct Digit {
    int val;

    Digit(int n) {
        require (0 <= n and n <= 9);

        this->val = n;
    }

    operator int() const {
        return this->val;
    }   
};

class Number {
  public:
    static const int SIZE = 6;

    List<Digit> digits;

    Number(int n) : Number(std::to_string(n)) {}

    Number(List<Digit> digits) {
        this->digits = digits;
    }

  private:
    Number(const std::string& str) {
        require (str.size() == Number::SIZE);

        for (int i = 0; i < Number::SIZE; ++i) {
            this->digits.push_back(Digit(str[i] -  '0'));
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Number& nb) {
    for (int i = 0; i < Number::SIZE; i++) {
        os << nb.digits.at(i);
    }
    return os;
}

Number operator<<(Number& nb, int shiftValue) {
    List<Digit> res = {};
    int curDigitIndex = shiftValue % Number::SIZE;
    Digit firstDigit = nb.digits.at(curDigitIndex);
    res.push_back(firstDigit);
    for (auto _ : range (1, 5)) {
        curDigitIndex = (curDigitIndex + 1) % Number::SIZE;
        res.push_back(nb.digits.at(curDigitIndex));
    }

    require (res.size() == 6);

    return Number(res);
}

int main()
{
    Number nb(142857);

    std::cout << (nb << 0) << std::endl;
    std::cout << (nb << 2) << std::endl;
    std::cout << (nb << 4) << std::endl;
    std::cout << (nb << 3) << std::endl;
}

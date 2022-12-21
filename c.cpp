

#include <iostream>
#include <vector>

using integral = unsigned long long int;
template <typename T> using List = std::vector<T>;

struct Digit {
    int val;
    Digit(int i) : val(i){}
    Digit(char c) : val(c - '0'){}
    // operator int() const { return this->val; }

    Digit operator~ () {
        return 9 - this->val;
    }
};

std::ostream& operator<<(std::ostream& os, Digit digit) {
    return os << digit.val;
}


struct Quantifier {
    int val;
    Quantifier(int i) : val(i){}
    // operator int() const { return this->val; }
};

Quantifier operator "" _(integral i) {
    return Quantifier(i);
}

struct Number {
    List<Digit> digits;
    Number(List<Digit> digits) : digits(digits){}
    Number(const char* str) {
        char c;
        while ((c = *str) != '\0') {
            if (c != ' ') {
                this->digits.push_back(c);
            }
            ++str;
        }
    }
    Number operator~ () {
        for (auto& d : this->digits) {
            d = ~d;
        }
        return *this;
    }

    Digit operator[](int i) {
        return this->digits.at(i);
    }

    List<Number> operator[](Quantifier quantifier) {
        // List<Number> res = {};
        // List<Digit> digits = {};

        // for (int i = 0; i < quantifier.val; ++i) {
        //     for (int j = 0; j < len(this->digits) / quantifier.val; ++j) {
        //         digits.push_back(this->digits[i*quantifier.val+j]);
        //     }
        //     res.push_back(Number(digits));
        //     digits.empty();
        // }

        // return res;
    }

};

size_t len(Number nb) {
    return nb.digits.size();
}

std::ostream& operator<<(std::ostream& os, Number nb) {
    for (auto c : nb.digits) {
        os << c;
    }
    return os;
}

Number operator<<(Number nb, int shiftOffset) {

    List<Digit> res = {};

    int curDigitIndex = shiftOffset % len(nb);
    Digit firstDigit = nb[curDigitIndex];
    res.push_back(firstDigit);

    for (int _ = 1; _ < len(nb); ++_) {
        curDigitIndex = (curDigitIndex + 1) % len(nb);
        res.push_back(nb[curDigitIndex]);
    }

    return Number(res);
}

Number operator "" nb(const char* str, size_t _) {
    return Number(str);
}

Number operator*(Quantifier quantifier, Digit digit) {
    return Number(List<Digit>(quantifier.val, digit));
}

int main()
{
    std::cout << 6_ * '9' << std::endl;
    // prints 999999

    std::cout << ~"010 989"nb << std::endl;
    // prints 989010

    Number nb = "010 989";
    {
        std::cout << (nb << 0) << std::endl;
        // prints 010 989

        std::cout << (nb << 2) << std::endl;
        // prints 098 901

        std::cout << "len: " << len(nb) << std::endl;
        // prints len: 6_

        // std::cout << nb[3_] << std::endl;
        // // prints { 01, 09, 89 }

        // std::cout << sum(nb[3_]) << std::endl;
        // // prints 99

        // std::cout << sum(nb[2_]) << std::endl;
        // // prints 999

        // auto res = (nb) + (nb << 2) + (nb << 2 << 2);
        // std::cout << res << std::endl;
        // // prints 999 999
    }

}

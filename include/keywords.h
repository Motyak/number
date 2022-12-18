#ifndef UTILS_KEYWORDS_H
#define UTILS_KEYWORDS_H

#include <iostream> // std::cerr
#include <vector> // std::vector

#define require assert

#define assert(condition) \
    if (!(condition)) { \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << std::endl; \
        std::terminate(); \
    }

std::vector<int> range(int from, int to) {
    std::vector<int> res;
    for (int i = from; i <= to; ++i) {
        res.push_back(i);
    }
    return res;
}

#endif

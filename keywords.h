
#include <iostream> // std::cerr

#define require(condition) \
    if (!(condition)) { \
        std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << std::endl; \
        throw std::runtime_error("requirement not met"); \
    }

#ifndef RANDOMUTILS_H_
#define RANDOMUTILS_H_

#include <random>

class RandomUtils {
private:
    std::mt19937 generator;
public:
    RandomUtils();

    double generate_uniform_number();
    double generate_normal_number(double mean, double stddev);
};

#endif
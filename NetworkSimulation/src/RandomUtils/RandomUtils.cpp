#include "RandomUtils.h"

RandomUtils::RandomUtils() {
    std::random_device rd;
    this->generator.seed(rd());
}

double RandomUtils::generate_uniform_number() {
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    return unif(generator);
}

double RandomUtils::generate_normal_number(int mean, int stddev) {
    std::normal_distribution<double> norm(mean, stddev);
    return norm(generator);
}
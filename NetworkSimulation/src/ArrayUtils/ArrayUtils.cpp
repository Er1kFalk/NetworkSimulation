#include "ArrayUtils.h"

std::vector<unsigned char> ArrayUtils::get_random_vector(int size) {
	std::vector<unsigned char> random_vec;
	random_vec.reserve(size);
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		random_vec.push_back(rand() % ((2 << __CHAR_BIT__)-1));
	}

	return random_vec;
}

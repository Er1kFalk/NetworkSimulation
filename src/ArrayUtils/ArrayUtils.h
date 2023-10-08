/*
 * ArrayUtils.h
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

#include <vector>
#include <array>
#include <cstdlib>

#ifndef ARRAYUTILS_H_
#define ARRAYUTILS_H_

template<typename T, std::size_t N>
class ArrayUtils {
public:
	std::vector<T> to_vector(std::array<T, N> a);
};

#include "ArrayUtils.tpp"


#endif /* ARRAYUTILS_H_ */

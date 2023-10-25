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


namespace ArrayUtils {
	template<typename T, std::size_t N>
	extern std::vector<T> to_vector(std::array<T, N> a);
}

template<typename T, std::size_t N>
std::vector<T> ArrayUtils::to_vector(std::array<T, N> a) {
	std::vector<T> v(a.begin(), a.end());
	return v;
}



#endif /* ARRAYUTILS_H_ */

/*
 * ArrayUtils.cpp
 *
 *  Created on: 8 Oct 2023
 *      Author: erik
 */

template<typename T, std::size_t N>
std::vector<T> ArrayUtils<T, N>::to_vector(std::array<T, N> a) {
	std::vector<T> v(a.begin(), a.end());
	return v;
}

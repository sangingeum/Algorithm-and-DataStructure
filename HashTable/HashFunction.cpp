#include "HashFunction.hpp"
size_t HashFunction::hash(long long key, size_t m) const {
	return key % m;
}

size_t MultiplicationHashFunction::hash(long long key, size_t m) const {
	float integral;
	return static_cast<size_t>(std::floorf(static_cast<float>(m) * std::abs(std::modf(key * A, &integral))));
}
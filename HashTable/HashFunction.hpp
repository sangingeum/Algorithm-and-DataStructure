#pragma once
#include <cmath>
// Base class
class HashFunction
{
public:
	//DivisionHashFunction
	// It is desirable for m to be a prime number
	// Maps long long key to {0, 1, ..., m-1}
	virtual size_t hash(long long key, size_t m) const {
		return key % m;
	}
	virtual ~HashFunction() = default;
};

class MultiplicationHashFunction : public HashFunction
{
	float A{ (sqrtf(5) - 1) / 2.f };
public:
	virtual size_t hash(long long key, size_t m) const override{
		float integral;
		return static_cast<size_t>(std::floorf(static_cast<float>(m) * std::abs(std::modf(key*A, &integral))));
	}
};

#pragma once
#include <functional>
#include <limits>

template<class T>
class Merger
{
public:
	using ValueType = typename T;
	virtual ~Merger() = default;
	virtual std::function<T(T, T)> getMerger() = 0;
	virtual T getInitialValue() = 0;
};

template<class T>
class SumMerger : public Merger<T>
{
public:
	std::function<T(T, T)> getMerger() override {
		return [](T a, T b) {return a + b; };
	}
	T getInitialValue() override {
		return 0;
	}
};

template<class T>
class MaxMerger : public Merger<T>
{
public:
	std::function<T(T, T)> getMerger() override {
		return [](T a, T b) {return std::max(a, b); };
	}
	T getInitialValue() override {
		return std::numeric_limits<T>::lowest();
	}
};

template<class T>
class MinMerger : public Merger<T>
{
public:
	std::function<T(T, T)> getMerger() override {
		return [](T a, T b) {return std::min(a, b); };
	}
	T getInitialValue() override {
		return std::numeric_limits<T>::max();
	}
};
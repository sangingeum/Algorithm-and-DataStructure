#pragma once
#include <vector>

// Partition Startegies

class Partition
{
public:
	virtual size_t partition(std::vector<int>& arr, size_t p, size_t r);
};

class RandomizedPartition : public Partition {
public:
	virtual size_t partition(std::vector<int>& arr, size_t p, size_t r) override;
};

class RandomMedianOfThreePartition : public Partition {
public:
	virtual size_t partition(std::vector<int>& arr, size_t p, size_t r) override;
};

class MedianOfThreePartition : public Partition {
public:
	virtual size_t partition(std::vector<int>& arr, size_t p, size_t r) override;
};
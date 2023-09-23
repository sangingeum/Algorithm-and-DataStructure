#include "FibonacciHeap.hpp"
#include <iostream>
#include <queue>
#include <format>
#include <vector>
#include <random>


struct Student {
	int id{ 0 };
	int grade{ 0 };
};

bool operator<(const Student& lhs, const Student& rhs) {
	return lhs.id > rhs.id;
}


int main() {
	// Compare my FibonacciHeap and the standard priority queue to check if my heap operates correctly
	FibonacciHeap<Student> heap;
	std::priority_queue<Student> priorityQ;
	std::vector<int> fromHeap; fromHeap.reserve(30000);
	std::vector<int> fromPQ; fromPQ.reserve(30000);

	// Make a random vector of length 20000.
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-10000, 10000); // Change the range as needed
	std::vector<int> randomVector(20000);
	std::generate(randomVector.begin(), randomVector.end(), [&gen, &dist]() { return dist(gen);});
	// Push 20000 items into each queue.
	for (int i = 0; i < 20000; ++i) {
		auto random = randomVector[i];
		heap.push(random, { random, random });
		priorityQ.push({ random, random });
		
		// Store the result of the top() function
		fromHeap.push_back(heap.top().id);
		fromPQ.push_back(priorityQ.top().id);
	}

	// Pop 10000 items from each queue
	for (size_t i = 0; i < 10000; ++i) {

		// Store the result of the top() function
		fromHeap.push_back(heap.top().id);
		fromPQ.push_back(priorityQ.top().id);

		// Pop an item
		heap.pop();
		priorityQ.pop();
	}

	// Check if both vectors are the same
	std::cout << ((fromHeap == fromPQ) ? "Same" : "Different") << "\n";

	// Reseult:
	// Same
	return 0;
}
#include "FibonacciHeap.hpp"
#include <iostream>
#include <queue>
#include <format>
#include <vector>
#include <random>
#include <cassert>

struct Student {
	int id{ 0 };
	int grade{ 0 };
};

bool operator<(const Student& lhs, const Student& rhs) {
	return lhs.id > rhs.id;
}

void test1() {
	///////////////////////////TEST1: push and pop ///////////////////////////

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
	std::generate(randomVector.begin(), randomVector.end(), [&gen, &dist]() { return dist(gen); });
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
	std::cout << "TEST1: " << ((fromHeap == fromPQ) ? "Pass" : "Fail") << "\n";
}

void test2() {
    ///////////////////////////TEST2: decreaseKey, remove, and merge ///////////////////////////

    // Create fibonacci heaps
    FibonacciHeap<Student> heap1;
    FibonacciHeap<Student> heap2;
	
    std::vector<FibonacciHeap<Student>::Handle> handles1;
    handles1.reserve(1000);
    std::vector<int> results1; 
	results1.reserve(3500);

    // Push 1000 items into the heaps
    for (int i = 0; i < 1000; ++i) {
        auto key1 = 2000 - i;
        auto key2 = 5000 + i;
        handles1.push_back(heap1.push(key1, { key1, key1 }));
		heap2.push(key2, { key2, key2 });
        results1.push_back(heap1.top().id); // 2000 ~ 1001
    }
    // Verify the size of the heaps
    assert(heap1.size() == 1000);
    assert(heap2.size() == 1000);

    // Set the key of the node with the highest key value to the minimum
    for (int i = 0; i < 1000; ++i) {
        heap1.decreaseKey(handles1[i], 1000 - i);
		results1.push_back(heap1.top().id); // 2000 ~ 1001 + 2000 ~ 1001
    }

    // Remove some nodes from heap1
	for (int i = 0; i < 500; ++i) {
        heap1.remove(handles1[i]);
    }

    // Verify the remove method
    assert(heap1.size() == 500);

    // Merge heap2 into heap1
    heap1.merge(heap2);  

    // Verify the merge method
    assert(heap1.size() == 1500);

	// Extract all the elements in the heap
	while (!heap1.empty()) {
		results1.push_back(heap1.top().id);
		heap1.pop();
	}
	
	// Prediction:
	// results1 = [2000~1001, 2000~1001, 1001~1500, 5000~5999]

	// Check if the prediction is correct
	std::vector<int> results2; 
	results2.reserve(3500);
	for (size_t i = 0; i < 1000; ++i)
		results2.push_back(2000 - i);
	for (size_t i = 0; i < 1000; ++i)
		results2.push_back(2000 - i);
	for (size_t i = 0; i < 500; ++i)
		results2.push_back(1001 + i);
	for (size_t i = 0; i < 1000; ++i)
		results2.push_back(5000 + i);

	std::cout << "TEST2: " << ((results1 == results2) ? "Pass" : "Fail") << "\n";
}


int main() {
	test1();
	test2();
	// Reseult:
	// TEST1: Pass
    // TEST2: Pass
	return 0;
}
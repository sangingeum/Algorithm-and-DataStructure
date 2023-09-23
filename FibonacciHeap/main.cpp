#include "FibonacciHeap.hpp"
#include <iostream>
#include <format>
struct Student {
	size_t id{ 0 };
	float grade{ 0 };
};


int main() {
	FibonacciHeap<Student> heap;
	for (size_t i = 0; i < 200; ++i) {
		heap.push(100 - 5 * i, { 100-5*i, 100.0f - 5 * i });
		auto front = heap.front();
		std::cout << std::format("id: {}, grade: {}\n", front.id, front.grade);
	}
	
	for (size_t i = 0; i < 100; ++i) {
		auto front = heap.front();
		std::cout << std::format("id: {}, grade: {}\n", front.id, front.grade);
		//std::cout << "----------------------------\n";
		//heap.print();
		//std::cout << "----------------------------\n";
		heap.pop();
	}


	return 0;
}
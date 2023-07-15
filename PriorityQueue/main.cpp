#include "PriorityQueue.hpp"
#include <iostream>
#include <format>
struct Data {
	size_t id;
	float grade;
};

int main() {
	// Create a priority queue and push elements
	PriorityQueue<Data> q;
	q.push(3, { 0, 10 });
	q.push(7, { 1, 9 });
	q.push(3, { 2, 4 });
	q.push(0, { 3, 7 });
	q.push(4, { 4, 3 });
	q.push(2, { 5, 7 });
	// Pop and print all the elements in the queue
	while (!q.empty()) {
		auto [key, data] = q.pop();
		std::cout << std::format("Priority: {}, Data:[id{}, grade{}]\n", key, data.id, data.grade);
	}
	/*
	Priority: 7, Data:[id1, grade9]
	Priority: 4, Data:[id4, grade3]
	Priority: 3, Data:[id0, grade10]
	Priority: 3, Data:[id2, grade4]
	Priority: 2, Data:[id5, grade7]
	Priority: 0, Data:[id3, grade7]
	*/
	return 0;
}
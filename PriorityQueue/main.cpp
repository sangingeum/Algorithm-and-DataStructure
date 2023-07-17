#include "PriorityQueue.hpp"
#include <iostream>
#include <format>
struct Data {
	size_t id;
	float grade;
};

int main() {
	// Create a priority queue and push elements to it
	PriorityQueue<Data> q;
	q.push(3, { 0, 10 });
	q.push(7, { 1, 9 });
	q.push(3, { 2, 4 });
	q.push(0, { 3, 7 });
	q.push(4, { 4, 3 });
	q.push(2, { 5, 7 });

	// Pop and print all the elements in the queue
	while (!q.empty()) {
		auto [key, data] = q.front(); q.pop();
		std::cout << std::format("Priority: {}, Data:[id:{}, grade:{}]\n", key, data.id, data.grade);
	}
	/*
	Priority: 7, Data:[id:1, grade:9]
	Priority: 4, Data:[id:4, grade:3]
	Priority: 3, Data:[id:0, grade:10]
	Priority: 3, Data:[id:2, grade:4]
	Priority: 2, Data:[id:5, grade:7]
	Priority: 0, Data:[id:3, grade:7]
	*/
	return 0;
}
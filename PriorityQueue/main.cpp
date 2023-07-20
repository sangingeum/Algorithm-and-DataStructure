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
	q.push(3.4f, { 0, 10 });
	q.push(7.f, { 1, 96 });
	q.push(3.f, { 2, 42});
	q.push(0.f, { 3, 75 });
	q.push(4.3f, { 4, 32 });
	q.push(-7.7f, { 5, 40 });
	q.push(-3, { 6, 32 });
	q.push(2.9f, { 7, 76 });

	// Pop and print all the elements in the queue
	while (!q.empty()) {
		auto [key, data] = q.front(); q.pop();
		std::cout << std::format("Priority: {:.1f}, Data:[id:{}, grade:{}]\n", key, data.id, data.grade);
	}
	/*
	Priority: 7.0, Data:[id:1, grade:96]
	Priority: 4.3, Data:[id:4, grade:32]
	Priority: 3.4, Data:[id:0, grade:10]
	Priority: 3.0, Data:[id:2, grade:42]
	Priority: 2.9, Data:[id:7, grade:76]
	Priority: 0.0, Data:[id:3, grade:75]
	Priority: -3.0, Data:[id:6, grade:32]
	Priority: -7.7, Data:[id:5, grade:40]
	*/
	return 0;
}
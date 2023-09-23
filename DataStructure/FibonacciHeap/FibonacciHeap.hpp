#pragma once
#include <memory>
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <format>
#include <string>


// FibonacciHeap Implemented in C++ 
template <class D>
class FibonacciHeap
{
private:
	struct Node {
		uint32_t degree{ 0 };
		float key;
		D data;
		bool mark{ false };
		Node* parent{ nullptr };
		Node* left{ this };
		Node* right{ this };
		Node* child{ nullptr };
		Node(float key_, D data_) : key(key_), data(std::move(data_)){}
	};
	Node* m_top;
	size_t m_size{ 0 };
public:
	FibonacciHeap() = default;
	~FibonacciHeap() { 
		if(m_top) recursiveFree(m_top);
	}
	void push(float key, D data) {
		Node* node = new Node(key, std::move(data));
		if (m_top) { // heap is not empty
			appendToRootList(node);
			if (node->key < m_top->key) {
				m_top = node;
			}
		}
		else { // heap is empty
			m_top = node;
		}
		++m_size;
	}
	D top() {
		return m_top->data;
	}
	// Extract-Min
	void pop() {
		auto oldTop = m_top;
		if (oldTop) {
			// Append children of the top node to the root list
			auto directChild = oldTop->child;
			auto child = directChild;
			if (child) {
				while (true) {
					auto left = child->left;
					appendToRootList(child);
					child = left;
					if (child == directChild)
						break;
				}
			}
			// Remove oldTop from the root list
			removeFromRootList(oldTop);
			// If oldTop is the last node
			if (oldTop == oldTop->right) {
				m_top = nullptr;
			}
			// If not
			else {
				m_top = oldTop->right;
				consolidate();
			}
			--m_size;

			delete oldTop;
		}
	}
	//bool empty();
	//bool remove(D item);
	//bool decreaseKey(D item, float newKey);
	void merge(FibonacciHeap<D>& other) {
		if (other.m_top) {
			if (m_top) {
				appendToList(m_top, other.m_top);
				if (other.m_top->key < m_top->key) {
					m_top = std::move(other.m_top);
				}
			}
			else {
				m_top = std::move(other.m_top);
			}
			m_size += other.m_size;
			other.m_size = 0;
		}
	}

	void print(Node* cur = nullptr, int depth=0) {
		if (!cur)
			cur = m_top;

		if (cur) {
			auto original = cur;
			while (true) {
				auto curDegree = cur->degree;
				for (int i = 0; i < depth; ++i) {
					std::cout << "@";
				}
				std::cout << std::format("id:{}, grade:{}", cur->data.id, cur->data.grade);
				if(cur->parent)
					std::cout << std::format(", parent:{}", cur->parent->data.id);
				else
					std::cout << std::format(", parent:N/A");
				if (cur->child) {
					std::cout << "\n";
					for (int i = 0; i < depth; ++i) {
						std::cout << "@";
					}
					std::cout << "children\n";
					print(cur->child, depth + 1);
				}
				else {
					std::cout << "\n";
				}
				
				cur = cur->left;
				if (cur == original)
					break;
			}
		}

	}

private:
	// This function assumes that top is not null
	void appendToRootList(Node* node) {
		node->parent = nullptr;
		node->left = m_top->left;
		node->right = m_top;
		m_top->left->right = node;
		m_top->left = node;
	}

	static void appendToList(Node* root, Node* node) {
		node->left = root->left;
		node->right = root;
		root->left->right = node;
		root->left = node;
	}

	//
	void removeFromRootList(Node* node) {
		node->right->left = node->left;
		node->left->right = node->right;
	}
	//
	void consolidate() {
		auto degree = static_cast<uint32_t>(std::floor(std::log10(m_size) / std::log10(1.618)));
		std::vector<Node*> degreeNodeArray(degree + 1);
		// prevent loop invalidation
		auto cur = m_top;
		std::vector<Node*> loop;
		if (cur) {
			while (true) {
				loop.push_back(cur);
				cur = cur->left;
				if (cur == m_top)
					break;
			}
		}
		// Fill in degreeNodeArray
		for (auto& cur : loop) {
			auto curDegree = cur->degree;
			if (curDegree > degree)
				std::cout << "degree out\n";
			while (degreeNodeArray[curDegree]) {
				auto sameDegreeNode = degreeNodeArray[curDegree];
				if (sameDegreeNode->key < cur->key) {
					std::swap(sameDegreeNode, cur);
				}
				// Attach sameDegreeNode to cur as a child
				heapLink(cur, sameDegreeNode);
				degreeNodeArray[curDegree] = nullptr;
				++curDegree;
			}
			degreeNodeArray[curDegree] = cur;
		}
		//
		m_top = nullptr;
		for (auto& node : degreeNodeArray) {
			if (node) {
				node->left = node->right = node;
				if (m_top) {
					appendToRootList(node);
					if (node->key < m_top->key) {
						m_top = node;
					}
				}
				else {
					m_top = node;
				}
			}
		}
	}

	void childification(Node* parent, Node* toBeChild) {
		toBeChild->left = toBeChild->right = toBeChild;
		if (parent->child)
			appendToList(parent->child, toBeChild);
		else
			parent->child = toBeChild;
		toBeChild->parent = parent;
		toBeChild->mark = false;
		++(parent->degree);
	}

	void heapLink(Node* parent, Node* toBeChild) {
		removeFromRootList(toBeChild);
		childification(parent, toBeChild);
	}

	void recursiveFree(Node* node) {
		node->right->left = nullptr;
		while (node) {
			if (node->child)
				recursiveFree(node->child);
			auto left = node->left;
			delete node;
			node = left;
		}
	}

};


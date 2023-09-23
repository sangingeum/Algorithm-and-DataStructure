#pragma once
#include <memory>
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>
#include <format>
#include <string>
#include <limits>

// FibonacciHeap Implemented in C++ 
template <class D>
class FibonacciHeap
{
private:
	struct Node {
		uint32_t degree{ 0 };
		float key;
		D data;
		bool marked{ false };
		Node* parent{ nullptr };
		Node* left{ this };
		Node* right{ this };
		Node* child{ nullptr };
		Node(float key_, D data_) : key(key_), data(std::move(data_)){}
	};

	Node* m_top;
	size_t m_size{ 0 };
public:
	class Handle {
	private:
		Node* ptr;
		friend FibonacciHeap;
	public:
		Handle(Node* ptr_) : ptr(ptr_) {}
	};
	FibonacciHeap() = default;
	~FibonacciHeap() { 
		if(m_top) recursiveFree(m_top);
	}

	// The returned handle can be used for the decrease key and the remove methods
	Handle push(float key, D data) {
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
		return Handle(node);
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
			removeFromList(oldTop);
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
	bool empty() {
		return m_top == nullptr;
	}
	size_t size() {
		return m_size;
	}
	void clear() {
		if (m_top) {
			recursiveFree(m_top);
			m_top = nullptr;
		}
	}
	void remove(Handle handle){
		decreaseKey(handle, std::numeric_limits<float>::lowest());
		pop();
	}
	bool decreaseKey(Handle handle, float newKey) {
		Node* node = handle.ptr;
		if (node->key > newKey) {
			node->key = newKey;
			auto parent = node->parent;
			if (parent && parent->key > newKey) {
				cut(parent, node);
				cascadingCut(parent);
			}
			if (newKey < m_top->key) {
				m_top = node;
			}

			return true;
		}
		return false;
	}

	
	void merge(FibonacciHeap<D>& other) {
		if (other.m_top) {
			if (m_top) {
				std::vector<Node*> rootList;
				auto cur = other.m_top;
				if (cur) {
					while (true) {
						rootList.push_back(cur);
						cur = cur->left;
						if (cur == other.m_top)
							break;
					}
				}
				for(auto& node : rootList)
					appendToRootList(node);

				if (other.m_top->key < m_top->key) {
					m_top = other.m_top;
				}
			}
			else {
				m_top = other.m_top;
			}
			m_size += other.m_size;
			other.m_top = nullptr;
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
		node->marked = false;
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
	void removeFromList(Node* node) {
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
		toBeChild->marked = false;
		++(parent->degree);
	}

	void heapLink(Node* parent, Node* toBeChild) {
		removeFromList(toBeChild);
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

	void cut(Node* parent, Node* child) {
		if (parent->child == child) {
			if (child->right == child)
				parent->child = nullptr;
			else
				parent->child = child->right;
		}
		removeFromList(child);
		--(parent->degree);
		appendToRootList(child);
	}
	void cascadingCut(Node* node) {
		auto parent = node->parent;
		if (parent) {
			if (node->marked) {
				cut(parent, node);
				cascadingCut(parent);
			}
			else {
				node->marked = true;
			}
		}
	}

};


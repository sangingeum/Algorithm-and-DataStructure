#pragma once
#include <memory>
#include <stdexcept> 
template <class D>
class RedBlackTree
{
	struct Node
	{
		D data;
		long long key;
		std::shared_ptr<Node> parent;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		bool isRed;
	};
public:
	RedBlackTree() { m_null->isRed = false; }

	D& get(long long key) {
		auto matchingNode = getNode(key);
		if (matchingNode == m_null)
			throw std::out_of_range("out of range");
		return matchingNode->data;
	}

	bool find(long long key) {
		if (getNode(key) == m_null)
			return false;
		return true;
	}

	void insert(long long key, const D& data) {
		auto nodeToCheck = m_root;
		decltype(nodeToCheck) curNode = m_null;
		decltype(nodeToCheck) newNode = std::make_shared<Node>(data, key, nullptr, m_null, m_null, true);
		while (nodeToCheck != m_null) {
 			curNode = nodeToCheck;
			if (key < nodeToCheck->key)
				nodeToCheck = nodeToCheck->left;
			else
				nodeToCheck = nodeToCheck->right;
		}
		newNode->parent = curNode;
		if (curNode == m_null)
			m_root = newNode;
		else if (curNode->key > key)
			curNode->left = newNode;
		else
			curNode->right = newNode;
		InsertFixup(newNode);
	}

	void remove(long long key) {
		auto node = getNode(key);
		decltype(node) x;
		auto y = node;
		bool yOriginalIsRed = y->isRed;
		if (node->left == m_null) {
			x = node->right;
			transplant(node, node->right);
		}
		else if (node->right == m_null) {
			x = node->left;
			transplant(node, node->left);
		}
		else {
			y = getMinNode(node->right);
			yOriginalIsRed = y->isRed;
			x = y->right;
			if (y->parent == node)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = node->right;
				y->right->parent = y;
			}
			transplant(node, y);
			y->left = node->left;
			y->left->parent = y;
			y->isRed = node->isRed;
		}
		if (!yOriginalIsRed) {
			removeFixup(x);
		}

	}



private:
	std::shared_ptr<Node> m_null{ new Node() };
	std::shared_ptr<Node> m_root { m_null };
	
	// Assumes that node->right is not null
	// and m_root->parent is null
	void leftRotate(std::shared_ptr<Node> node){
		auto y = node->right;
		node->right = y->left;
		if (y->left != m_null)
			y->left->parent = node;
		y->parent = node->parent;
		if (node->parent == m_null)
			m_root = y;
		else if (node == node->parent->left)
			node->parent->left = y;
		else
			node->parent->right = y;
		y->left = node;
		node->parent = y;
	}
	// Assumes that node->left is not null
	// and m_root->parent is null
	void rightRotate(std::shared_ptr<Node> node) {
		auto y = node->left;
		node->left = y->right;
		if (y->right != m_null)
			y->right->parent = node;
		y->parent = node->parent;
		if (node->parent == m_null)
			m_root = y;
		else if (node == node->parent->left)
			node->parent->left = y;
		else
			node->parent->right = y;
		y->right = node;
		node->parent = y;
	}

	void InsertFixup(std::shared_ptr<Node> node) {
		while (node->parent->isRed) {
			if (node->parent == node->parent->parent->left) {
				auto y = node->parent->parent->right;
				if (y->isRed) {
					node->parent->isRed = false;
					y->isRed = false;
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					rightRotate(node->parent->parent);
				}
				
			}
			else {
				auto y = node->parent->parent->left;
				if (y->isRed) {
					node->parent->isRed = false;
					y->isRed = false;
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					leftRotate(node->parent->parent);
				}
				
			}
		}
		m_root->isRed = false;
	}

	void removeFixup(std::shared_ptr<Node> node) {
		while (node != m_root && !node->isRed) {
			if (node == node->parent->left) {
				decltype(node) w = node->parent->right;
				if (w->isRed) {
					w->isRed = false;
					node->parent->isRed = true;
					leftRotate(node->parent);
					w = node->parent->right;
				}
				if (!w->left->isRed && !w->right->isRed) {
					w->isRed = true;
					node = node->parent;
				}
				else{
					if (!w->right->isRed) {
						w->left->isRed = false;
						w->isRed = true;
						rightRotate(w);
						w = node->parent->right;
					}
					w->isRed = node->parent->isRed;
					node->parent->isRed = false;
					w->right->isRed = false;
					leftRotate(node->parent);
					node = m_root;

				}
			}
			else {
				decltype(node) w = node->parent->left;
				if (w->isRed) {
					w->isRed = false;
					node->parent->isRed = true;
					rightRotate(node->parent);
					w = node->parent->left;
				}
				if (!w->left->isRed && !w->right->isRed) {
					w->isRed = true;
					node = node->parent;
				}
				else {
					if (!w->left->isRed) {
						w->right->isRed = false;
						w->isRed = true;
						leftRotate(w);
						w = node->parent->left;
					}
					w->isRed = node->parent->isRed;
					node->parent->isRed = false;
					w->left->isRed = false;
					rightRotate(node->parent);
					node = m_root;

				}
			}
		}
		node->isRed = false;
	}

	// Replace u with v. v is allowed to be null
	// This function does not update v's left and right children.
	// So, the responsibility of correctly setting them is on the caller's side 
	void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v) {
		if (u->parent == m_null)
			m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	std::shared_ptr<Node> getMinNode(std::shared_ptr<Node> node) {
		auto curNode = node;
		while (curNode->left != m_null) {
			curNode = curNode->left;
		}
		return curNode;
	}

	// Find a node matching the given key
	// If not found, return m_null
	std::shared_ptr<Node> getNode(long long key) {
		auto curNode = m_root;
		while (curNode != m_null) {
			if (curNode->key == key)
				break;
			else if (curNode->key > key)
				curNode = curNode->left;
			else
				curNode = curNode->right;
		}
		return curNode;
	}

};


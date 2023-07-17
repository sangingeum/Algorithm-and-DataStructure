#pragma once
#include <memory>
#include <iostream>
template <class D>
class BinarySearchTree
{
	// Custum Node structure
	struct Node {
		D data;
		long long key;
		std::shared_ptr<Node> parent;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
	};
public:
	void insert(long long key, const D& data);
	void remove(long long key);
	bool find(long long key);
	D& get(long long key);
	D& min();
	D& max();
	void inOrderTreeWalk();
private:
	std::shared_ptr<Node> m_root;
	void inOrderTreeWalk(std::shared_ptr<Node> node);
	std::shared_ptr<Node> minNode(std::shared_ptr<Node> node);
	void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
	std::shared_ptr<Node> getNode(long long key);
};

template <class D>
void BinarySearchTree<D>::insert(long long key, const D& data) {
	if (!m_root) {
		m_root = std::make_shared<Node>(data, key, nullptr, nullptr, nullptr);
	}
	else {
		auto curNode = m_root;
		decltype(curNode) prevNode;
		while (curNode) {
			prevNode = curNode;
			if (curNode->key > key)
				curNode = curNode->left;
			else
				curNode = curNode->right;
		}
		if (prevNode->key > key)
			prevNode->left = std::make_shared<Node>(data, key, prevNode, nullptr, nullptr);
		else
			prevNode->right = std::make_shared<Node>(data, key, prevNode, nullptr, nullptr);
	}
}
template <class D>
void BinarySearchTree<D>::remove(long long key) {
	auto targetNode = getNode(key);
	if (!targetNode)
		return;
	if (!targetNode->left)
		transplant(targetNode, targetNode->right);
	else if (!targetNode->right)
		transplant(targetNode, targetNode->left);
	else {
		auto successor = minNode(targetNode->right);
		if (successor->parent != targetNode) {
			transplant(successor, successor->right);
			successor->right = targetNode->right;
			successor->right->parent = successor;
		}
		transplant(targetNode, successor);
		successor->left = targetNode->left;
		successor->left->parent = successor;
	}
}
template <class D>
bool BinarySearchTree<D>::find(long long key) {
	if (getNode(key))
		return true;
	else
		return false;
}
template <class D>
D& BinarySearchTree<D>::get(long long key) {
	auto curNode = getNode(key);
	if (curNode)
		return curNode->data;
	else
		throw std::out_of_range("Incorrect index");
}
template <class D>
D& BinarySearchTree<D>::min() {
	auto curNode = m_root;
	while (curNode->left) {
		curNode = curNode->left;
	}
	return curNode->data;
}
template <class D>
D& BinarySearchTree<D>::max() {
	auto curNode = m_root;
	while (curNode->right) {
		curNode = curNode->right;
	}
	return curNode->data;
}
template <class D>
void BinarySearchTree<D>::inOrderTreeWalk() {
	if (m_root) {
		inOrderTreeWalk(m_root->left);
		std::cout << m_root->key << " ";
		inOrderTreeWalk(m_root->right);
	}
	std::cout << "\n";
}
template <class D>
void BinarySearchTree<D>::inOrderTreeWalk(std::shared_ptr<Node> node) {
	if (node) {
		inOrderTreeWalk(node->left);
		std::cout << node->key << " ";
		inOrderTreeWalk(node->right);
	}
}

template <class D>
std::shared_ptr<typename BinarySearchTree<D>::Node> BinarySearchTree<D>::minNode(std::shared_ptr<Node> node) {
	auto curNode = node;
	while (curNode->left) {
		curNode = curNode->left;
	}
	return curNode;
}

// Replace u with v, v is allowed to be null
// This functions does not update v's left and right children.
// So, the responsibility is on the caller's side
template <class D>
void BinarySearchTree<D>::transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v) {
	if (!u->parent)
		m_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v)
		v->parent = u->parent;
}

template <class D>
std::shared_ptr<typename BinarySearchTree<D>::Node> BinarySearchTree<D>::getNode(long long key) {
	auto curNode = m_root;
	while (curNode) {
		if (curNode->key == key)
			break;
		else if (curNode->key > key)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}
	return curNode;
}
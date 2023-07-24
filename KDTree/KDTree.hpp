#pragma once
#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <format>

// TODO
// Remove, Min, Max, RangeSearch operations

template <size_t K, class T = float>
class KDTree
{
private:
	struct Node {
		std::array<T, K> point;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		Node(const std::array<T, K>& point_) : point(point_) {}
	};
	std::shared_ptr<Node> m_root;
public:
	KDTree() = default;
	KDTree(std::vector<std::array<T, K>>& points) { m_root = buildTree(points, 0, 0, points.size()); }
	void insert(const std::array<T, K>& point) {
		if (!m_root) {
			m_root.reset(new Node(point));
		}
		else {
			size_t curDepth = 0;
			std::shared_ptr<Node> curNode = m_root;
			std::shared_ptr<Node> nextNode = m_root;
			while (true) {
				const T& curValue = curNode->point[curDepth];
				if (curValue < point[curDepth]) {
					nextNode = curNode->right;
					if (!nextNode) {
						curNode->right.reset(new Node(point));
						break;
					}
				}
				else {
					nextNode = curNode->left;
					if (!nextNode) {
						curNode->left.reset(new Node(point));
						break;
					}
				}
				curNode = nextNode;
				curDepth = (curDepth + 1) % K;
			}
		}
	}

	std::array<T, K> findNearest(const std::array<T, K>& target) {
		if (!m_root)
			throw std::runtime_error("Tree is empty");
		return findNearest(m_root, target, 0);
	}

private:

	std::shared_ptr<Node> buildTree(std::vector<std::array<T, K>>& points, size_t depth, size_t from, size_t to) {
		size_t kIndex = depth % K;
		size_t nthIndex = (from + to) / 2;
		auto nth = nthIndex + points.begin();
		// Split the tree at the median
		std::nth_element(points.begin() + from, nth, points.begin() + to,
			[kIndex](const std::array<T, K>& a, const std::array<T, K>& b) {
				return a[kIndex] < b[kIndex];
			});
		auto curNode = std::make_shared<Node>(*nth);
		// Extend children
		if (nthIndex - from > 0)
			curNode->left = buildTree(points, depth + 1, from, nthIndex);
		if (to - nthIndex > 1)
			curNode->right = buildTree(points, depth + 1, nthIndex + 1, to);
		return curNode;
	}

	std::array<T, K> findNearest(std::shared_ptr<Node> root, const std::array<T, K>& target, size_t depth) {
		size_t curDepth = depth % K;
		std::shared_ptr<Node> nextBranch;
		std::shared_ptr<Node> otherBranch;
		if (target[curDepth] < root->point[curDepth]) {
			nextBranch = root->left;
			otherBranch = root->right;
		}
		else {
			nextBranch = root->right;
			otherBranch = root->left;
		}

		T bestDist;
		std::array<T, K> bestPoint;
		std::array<T, K> tempPoint;
		if (nextBranch) {
			tempPoint = findNearest(nextBranch, target, depth + 1);
			T distToRoot = getSquaredDistance(target, root->point);
			T distToTemp = getSquaredDistance(target, tempPoint);
			if (distToRoot > distToTemp) {
				bestDist = distToTemp;
				bestPoint = tempPoint;
			}
			else {
				bestDist = distToRoot;
				bestPoint = root->point;
			}
		}
		else {
			bestPoint = root->point;
			bestDist = getSquaredDistance(target, root->point);
		}
		
		if (otherBranch) {
			T diff = target[curDepth] - root->point[curDepth];
			T distToOtherBranch = diff * diff;
			if (bestDist >= distToOtherBranch) {
				tempPoint = findNearest(otherBranch, target, depth + 1);
				if (bestDist > getSquaredDistance(target, tempPoint))
					bestPoint = tempPoint;
			}
		}

		
		return bestPoint;
	}

	T getSquaredDistance(const std::array<T, K>& p1, const std::array<T, K>& p2) {
		T distance = 0;
		for (size_t i = 0; i < K; ++i) {
			T diff = p1[i] - p2[i];
			distance += diff * diff;
		}
		return distance;
	}

};


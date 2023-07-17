#pragma once
#include <vector>
#include <algorithm>
#include <utility>

template <class T, class H>
class HashTable
{
protected:
	struct Node
	{
		long long key;
		T element;
		Node(long long k, T elem) : key(k), element(elem) {}
	};
	size_t m_tableSize{};
	H m_hashFunction{};
public:
	virtual ~HashTable() = default;
	HashTable(size_t tableSize) : m_tableSize(tableSize) {}
	virtual bool find(long long key) const = 0;
	virtual void insert(long long key, T element) = 0;
	virtual void remove(long long key) = 0;
	virtual T& get(long long key) = 0;
};

template <class T, class H>
class ChainedHashTable : public HashTable<T, H>
{	
	using Node = HashTable<T, H>::Node;
	using Table = std::vector<std::vector<Node>>;
	Table m_table;
public:
	ChainedHashTable(size_t tableSize) : HashTable<T, H>(tableSize), m_table(tableSize){}
	bool find(long long key) const override;
	void insert(long long key, T element) override;
	void remove(long long key) override;
	T& get(long long key) override;
};

template <class T, class H>
bool ChainedHashTable<T, H>::find(long long key) const {
	auto& targetTable = m_table[this->m_hashFunction.hash(key, this->m_tableSize)];
	auto it = std::find_if(targetTable.begin(), targetTable.end(), [key](const Node& node)
		{
			return node.key == key;
		});
	return (it != targetTable.end());
}
template <class T, class H>
void ChainedHashTable<T, H>::insert(long long key, T element) {
	auto& targetTable = m_table[this->m_hashFunction.hash(key, this->m_tableSize)];
	auto it = std::find_if(targetTable.begin(), targetTable.end(), [key](const Node& node)
		{
			return node.key == key;
		});
	if (it != targetTable.end()) {
		*it = Node(key, element);
	}
	else {
		targetTable.emplace_back(key, element);
	}
}
template <class T, class H>
void ChainedHashTable<T, H>::remove(long long key) {
	auto& targetTable = m_table[this->m_hashFunction.hash(key, this->m_tableSize)];
	auto it = std::find_if(targetTable.begin(), targetTable.end(), [key](const Node& node)
		{
			return node.key == key;
		});
	if (it != targetTable.end()) {
		targetTable.erase(it);
	}
}
template <class T, class H>
T& ChainedHashTable<T, H>::get(long long key) {
	auto& targetTable = m_table[this->m_hashFunction.hash(key, this->m_tableSize)];
	auto it = std::find_if(targetTable.begin(), targetTable.end(), [key](const Node& node)
		{
			return node.key == key;
		});
	if (it != targetTable.end()) {
		return it->element;
	}
	throw std::exception();
}
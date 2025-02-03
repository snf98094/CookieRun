#pragma once
#include <vector>
#include <string>
#include "Pair.h"

using Entry = Pair<std::string, std::string>;
using string = std::string;

class HashTable
{
public:
	HashTable() = default;
	~HashTable() = default;

	void Add(string key, string value);
	void Delete(string key);
	bool Find(string key, Entry& outValue);
	void Print();

private:
	static const int bucketCount = 19;
	std::vector<Entry> table[bucketCount];
};
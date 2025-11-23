#pragma once
#include <string.h>
#include <functional>
#include <optional>

struct CDefCaselessStringLess {
	bool operator()(const char* a, const char* b) const {

		return _stricmp(a, b) < 0;
	}
};

template <typename Key, typename Value, typename Index = int, typename KL = std::less<Key>>
class CUtlMap {
private:
	struct Node {
		Index left;
		Index right;
		Index parent;
		Index type;
		Key key;
		Value value;
	};

	Node* memory;
	Index root;
	Index numElements;

	Value FindByKey(const Key& key) const
	{
		int current = root;
		KL less;

		while (current != -1)
		{
			auto& element = memory[current];
			if (element.key == nullptr)
				break;
			if (less(element.key, key))
				current = element.right;
			else if (less(key, element.key))
				current = element.left;
			else
				return element.value;
		}

		return nullptr;
	}

public:
	Value operator[](const Key& key) {
		return FindByKey(key);
	}
};
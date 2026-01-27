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
		Index m_Left;
		Index m_Right;
		Index m_Parent;
		Index m_Type;
		Key m_Key;
		Value m_Value;
	};

	Node* m_Memory;
	Index m_Root;
	Index m_numElements;

	Value FindByKey(const Key& key) const
	{
		int current = m_Root;
		KL less;

		while (current != -1)
		{
			auto& element = m_Memory[current];
			if (element.m_Key == nullptr)
				break;
			if (less(element.m_Key, key))
				current = element.m_Right;
			else if (less(key, element.m_Key))
				current = element.m_Left;
			else
				return element.m_Value;
		}

		return nullptr;
	}

public:
	Value operator[](const Key& key) {
		return FindByKey(key);
	}
};
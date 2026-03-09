#pragma once
#include <string.h>
#include <functional>
#include <optional>

#include "CUtlRBTree.hpp"

struct CDefCaselessStringLess {
	char pad[8];
	bool operator()(const char* a, const char* b) const {
		//if (!a || !b)
		//	return false;

		return _stricmp(a, b) < 0;
	}
};

template <typename K, typename T, typename I = uint16_t, typename LF = bool (*)(const K&, const K&)>
class CUtlMap {
public:
    using KeyType_t     = K;
    using ElemType_t    = T;
    using IndexType_t   = I;
	using LessFunc_t	= LF;

public:
    struct Node_t {
        Node_t() = default;

        Node_t(const Node_t& from) : key(from.key), elem(from.elem) {}

        KeyType_t key;
        ElemType_t elem;
    };

	class CKeyLess
	{
	public:
		CKeyLess(LessFunc_t lessFunc) : m_LessFunc(lessFunc) {}

		bool operator!() const
		{
			if constexpr (std::is_pointer_v<LessFunc_t>)
				return !m_LessFunc;
			else
				return false;
		}

		bool operator()(const Node_t& left, const Node_t& right) const
		{
			return m_LessFunc(left.key, right.key);
		}

		LessFunc_t m_LessFunc;
	};

    using CTree = CUtlRBTree<Node_t, IndexType_t, CKeyLess>;

public:
    CTree m_Tree;

	ElemType_t& operator[](const KeyType_t& key) {
		Node_t dummyNode;
		dummyNode.key = key;
		IndexType_t index = m_Tree.Find(dummyNode);
        return m_Tree.Element(index).elem;
    }

public:
	IndexType_t  FirstInorder() const { return m_Tree.FirstInorder(); }
	IndexType_t  NextInorder(IndexType_t i) const { return m_Tree.NextInorder(i); }
	IndexType_t  PrevInorder(IndexType_t i) const { return m_Tree.PrevInorder(i); }
	IndexType_t  LastInorder() const { return m_Tree.LastInorder(); }
	static IndexType_t InvalidIndex() { return CTree::InvalidIndex(); }

};

//template <typename Key, typename Value, typename Index = int, typename KL = std::less<Key>>
//class CUtlMap {
//private:
//	struct Node {
//		Index m_Left;
//		Index m_Right;
//		Index m_Parent;
//		Index m_Type;
//		Key m_Key;
//		Value m_Value;
//	};
//
//	Node* m_Memory;
//	Index m_Root;
//	Index m_numElements;
//
//	Value FindByKey(const Key& key) const
//	{
//		int current = m_Root;
//		KL less;
//
//		while (current != -1)
//		{
//			auto& element = m_Memory[current];
//			if (element.m_Key == nullptr)
//				break;
//			if (less(element.m_Key, key))
//				current = element.m_Right;
//			else if (less(key, element.m_Key))
//				current = element.m_Left;
//			else
//				return element.m_Value;
//		}
//
//		return nullptr;
//	}
//
//public:
//	Value operator[](const Key& key) {
//		return FindByKey(key);
//	}
//};